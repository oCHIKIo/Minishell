/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:48:11 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/01 20:23:31 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	validate_operator_syntax(char *input)
{
	char	*trimmed;

	trimmed = trim_whitespace(input);
	if (!trimmed)
		return (1);
	if (ft_strcmp(trimmed, ">>") == 0 || ft_strcmp(trimmed, ">") == 0
		|| ft_strcmp(trimmed, "<") == 0 || ft_strcmp(trimmed, "<<") == 0
		|| ft_strcmp(trimmed, "<<<") == 0 || ft_strcmp(trimmed, ">>>>") == 0)
	{
		ft_putstr_fd("xero: syntax error near unexpected token `", 2);
		ft_putstr_fd(trimmed, 2);
		ft_putstr_fd("'\n", 2);
		free(trimmed);
		exit_status(2, 1);
		return (0);
	}
	free(trimmed);
	return (1);
}

int	validate_quotes(char *input)
{
	t_validate_quotes	x;

	x.single_quotes = 0;
	x.double_quotes = 0;
	x.j = 0;
	while (input[x.j])
	{
		if (input[x.j] == '\\' && input[x.j + 1])
		{
			x.j += 2;
			continue ;
		}
		if (input[x.j] == '\'' && x.double_quotes % 2 == 0)
			x.single_quotes++;
		else if (input[x.j] == '"' && x.single_quotes % 2 == 0)
			x.double_quotes++;
		x.j++;
	}
	if (x.single_quotes % 2 != 0 || x.double_quotes % 2 != 0)
	{
		ft_putstr_fd("xero: syntax error\n", 2);
		return (0);
	}
	return (1);
}

int	handle_redirect_error(char c, int count)
{
	char	*op;

	if (count > 2)
	{
		if (c == '<')
			op = ft_strdup("<<<");
		else
			op = ft_strdup(">>>");
		ft_putstr_fd("xero: syntax error near unexpected token `", 2);
		ft_putstr_fd(op, 2);
		ft_putstr_fd("'\n", 2);
		free(op);
		exit_status(2, 1);
		return (0);
	}
	return (1);
}

t_token	*process_redirect_token(char *input, int *i, t_token **tokens)
{
	char	c;
	int		count;
	char	*op;
	t_token	*new_token;

	c = input[*i];
	count = 0;
	while (input[*i + count] == c)
		count++;
	if (!handle_redirect_error(c, count))
	{
		free_tokens(*tokens);
		return (NULL);
	}
	op = ft_substr(input, *i, count);
	new_token = create_token(op, get_token_type(op));
	token_add_back(tokens, new_token);
	*i += count;
	return (new_token);
}

t_token	*process_pipe_token(char *input, int *i, t_token **tokens)
{
	char	*op;
	t_token	*new_token;

	op = ft_substr(input, *i, 1);
	new_token = create_token(op, get_token_type(op));
	*i += 1;
	token_add_back(tokens, new_token);
	return (new_token);
}
