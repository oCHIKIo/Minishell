/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:47:51 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/29 09:35:32 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*process_word_token(char *input, int *i, t_token **tokens)
{
	char	*word;
	t_token	*new_token;

	word = extract_word(input, i);
	if (word)
	{
		new_token = create_token(word, WORD);
		token_add_back(tokens, new_token);
		return (new_token);
	}
	return (NULL);
}

static char	*prepare_input(char *input)
{
	if (!input || ft_strlen(input) == 0)
		return (NULL);
	return (input);
}

static int	validate_input_all(char *trimmed_input)
{
	if (!validate_operator_syntax(trimmed_input))
		return (0);
	if (!validate_input_syntax(trimmed_input))
		return (0);
	if (!validate_quotes(trimmed_input))
		return (0);
	return (1);
}

static t_token	*process_tokens(char *trimmed_input)
{
	t_token	*tokens;

	tokens = NULL;
	tokens = tokenize_loop(trimmed_input, &tokens);
	if (tokens && !validate_token_sequence(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	char	*prepared_input;

	prepared_input = prepare_input(input);
	if (!prepared_input)
		return (NULL);
	if (!validate_input_all(prepared_input))
		return (NULL);
	tokens = process_tokens(prepared_input);
	if (!tokens)
		return (NULL);
	return (tokens);
}
