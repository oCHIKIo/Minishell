/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:46:41 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/28 16:30:02 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	find_brace_end(char *tilde_expanded, t_brace_parser *parser,
		int start_pos)
{
	parser->start = start_pos + 2;
	parser->end = parser->start;
	while (tilde_expanded[parser->end] && tilde_expanded[parser->end] != '}')
		parser->end++;
}

static int	extract_and_expand_braced_var(char *tilde_expanded, char **result,
		t_brace_parser *parser, char **envp)
{
	parser->var_name = ft_substr(tilde_expanded, parser->start, parser->end
			- parser->start);
	if (!parser->var_name)
		return (-1);
	parser->var_value = get_env_value_from_envp(envp, parser->var_name);
	if (parser->var_value)
	{
		parser->temp = *result;
		*result = ft_strjoin(*result, parser->var_value);
		if (!*result)
			*result = parser->temp;
		else
			free(parser->temp);
	}
	free(parser->var_name);
	return (0);
}

char	*handle_braced_variable(char *tilde_expanded, char **result, int *i,
		char **envp)
{
	t_brace_parser	parser;

	find_brace_end(tilde_expanded, &parser, *i);
	if (tilde_expanded[parser.end] == '}')
	{
		if (extract_and_expand_braced_var(tilde_expanded, result, &parser,
				envp) == -1)
		{
			*i = parser.end + 1;
			return (*result);
		}
		*i = parser.end + 1;
	}
	else
	{
		append_single_char(result, tilde_expanded[*i]);
		(*i)++;
	}
	return (*result);
}

char	*handle_regular_variable(char *tilde_expanded, char **result, int *i,
		char **envp)
{
	t_hndl_rglr_vrible	x;

	x.start = *i + 1;
	while (tilde_expanded[x.start] && (ft_isalnum(tilde_expanded[x.start])
			|| tilde_expanded[x.start] == '_'))
		x.start++;
	x.var_name = ft_substr(tilde_expanded, *i + 1, x.start - *i - 1);
	if (!x.var_name)
	{
		*i = x.start;
		return (*result);
	}
	x.var_value = get_env_value_from_envp(envp, x.var_name);
	if (x.var_value)
	{
		x.temp = *result;
		*result = ft_strjoin(*result, x.var_value);
		if (!*result)
			*result = x.temp;
		else
			free(x.temp);
	}
	*i = x.start;
	free(x.var_name);
	return (*result);
}

void	append_single_char(char **result, char c)
{
	char	tmp[2];
	char	*temp;

	tmp[0] = c;
	tmp[1] = 0;
	temp = *result;
	*result = ft_strjoin(*result, tmp);
	if (!*result)
		*result = temp;
	else
		free(temp);
}
