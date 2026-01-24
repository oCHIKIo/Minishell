/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:11:00 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/07 12:11:02 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_dollar_expansion(char *tilde_expanded, char **result, int *i,
		char **envp)
{
	if (tilde_expanded[*i + 1] == '?')
		return (handle_exit_status_expansion(result, i));
	else if (tilde_expanded[*i + 1] == '{' && tilde_expanded[*i + 2] == '}')
		return (handle_empty_braces(result, i));
	else if (tilde_expanded[*i + 1] == '{')
		return (handle_braced_variable(tilde_expanded, result, i, envp));
	else if (!tilde_expanded[*i + 1] || (!ft_isalnum(tilde_expanded[*i + 1])
			&& tilde_expanded[*i + 1] != '_'))
	{
		append_single_char(result, tilde_expanded[*i]);
		(*i)++;
	}
	else
		return (handle_regular_variable(tilde_expanded, result, i, envp));
	return (*result);
}

void	handle_quotes(char c, char *quote)
{
	if ((c == '\'' || c == '"') && *quote == 0)
		*quote = c;
	else if (c == *quote)
		*quote = 0;
}

char	*handle_quotes_and_escapes(char *tilde_expanded, char **result,
		t_char_processor *proc)
{
	if ((tilde_expanded[proc->i] == '\'' || tilde_expanded[proc->i] == '"')
		&& proc->quote == 0)
	{
		handle_quotes(tilde_expanded[proc->i], &proc->quote);
		proc->i++;
	}
	else if (tilde_expanded[proc->i] == proc->quote)
	{
		handle_quotes(tilde_expanded[proc->i], &proc->quote);
		proc->i++;
	}
	else if (tilde_expanded[proc->i] == '\\' && proc->quote == '"'
		&& (tilde_expanded[proc->i + 1] == '"'
			|| tilde_expanded[proc->i + 1] == '\\'
			|| tilde_expanded[proc->i + 1] == '$'))
	{
		proc->i++;
		append_single_char(result, tilde_expanded[proc->i]);
		proc->i++;
	}
	else
		return (NULL);
	return (*result);
}

char	*handle_exit_status_expansion(char **result, int *i)
{
	char	*exit_status_str;
	char	*temp;

	exit_status_str = ft_itoa(exit_status(0, 0));
	if (!exit_status_str)
		return (*result);
	temp = *result;
	*result = ft_strjoin(*result, exit_status_str);
	if (!*result)
		*result = temp;
	else
		free(temp);
	free(exit_status_str);
	*i += 2;
	return (*result);
}

char	*handle_empty_braces(char **result, int *i)
{
	char	*temp;

	temp = *result;
	*result = ft_strjoin(*result, "{}");
	if (!*result)
		*result = temp;
	else
		free(temp);
	*i += 3;
	return (*result);
}
