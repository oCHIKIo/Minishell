/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:59:57 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/25 15:59:57 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*handle_expansion_and_regular_chars(char *tilde_expanded,
		char **result, t_char_processor *proc, char **envp)
{
	if (tilde_expanded[proc->i] == '$' && proc->quote != '\'')
		handle_dollar_expansion(tilde_expanded, result, &proc->i, envp);
	else
	{
		append_single_char(result, tilde_expanded[proc->i]);
		proc->i++;
	}
	return (*result);
}

char	*process_characters(char *tilde_expanded, char **envp, char *result)
{
	t_char_processor	proc;

	proc.quote = 0;
	proc.i = 0;
	while (tilde_expanded[proc.i])
	{
		if (handle_quotes_and_escapes(tilde_expanded, &result, &proc) == NULL)
			handle_expansion_and_regular_chars(tilde_expanded, &result, &proc,
				envp);
	}
	return (result);
}

char	*get_env_value_from_envp(char **envp, char *key)
{
	int	i;
	int	key_len;

	if (!envp || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (envp[i] + key_len + 1);
		i++;
	}
	return (NULL);
}
