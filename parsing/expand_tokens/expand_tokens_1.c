/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:46:11 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/25 19:03:32 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*process_token_content(char *content, char **envp)
{
	char	*tilde_expanded;
	char	*result;

	tilde_expanded = expand_tilde_in_token(content, envp);
	result = ft_strdup("");
	if (!tilde_expanded || !result)
	{
		free(tilde_expanded);
		free(result);
		return (NULL);
	}
	result = process_characters(tilde_expanded, envp, result);
	free(tilde_expanded);
	return (result);
}

int	should_expand_token(char *content)
{
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	while (content[i])
	{
		if ((content[i] == '\'' || content[i] == '"') && quote == 0)
			quote = content[i];
		else if (content[i] == quote)
			quote = 0;
		else if (content[i] == '$' && quote != '\'')
			return (1);
		i++;
	}
	return (0);
}

void	expand_tokens(t_token *tokens, char **envp)
{
	t_token	*current;
	char	*processed;

	current = tokens;
	while (current)
	{
		if (current->type == WORD && should_expand_token(current->content))
		{
			processed = process_token_content(current->content, envp);
			if (processed)
			{
				free(current->content);
				current->content = processed;
			}
		}
		current = current->next;
	}
}
