/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:48:19 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/01 20:25:10 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	skip_whitespace(char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
}

t_token	*process_single_token(char *input, int *i, t_token **tokens)
{
	t_token	*result;

	if (input[*i] == '>' || input[*i] == '<')
	{
		result = process_redirect_token(input, i, tokens);
		if (!result)
			return (NULL);
	}
	else if (input[*i] == '|')
		result = process_pipe_token(input, i, tokens);
	else
		result = process_word_token(input, i, tokens);
	return (result);
}

t_token	*tokenize_loop(char *input, t_token **tokens)
{
	int		i;
	t_token	*result;

	i = 0;
	while (input[i])
	{
		skip_whitespace(input, &i);
		if (!input[i])
			break ;
		result = process_single_token(input, &i, tokens);
		if (!result)
			return (NULL);
	}
	return (*tokens);
}
