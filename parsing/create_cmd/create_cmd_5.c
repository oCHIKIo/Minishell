/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:12:55 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/31 11:12:57 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_heredoc(t_cmd *cmd, char *delimiter)
{
	t_heredoc	*new_heredoc;
	t_heredoc	*current;

	new_heredoc = malloc(sizeof(t_heredoc));
	if (!new_heredoc)
		return ;
	new_heredoc->delimiter = ft_strdup(delimiter);
	if (!new_heredoc->delimiter)
	{
		free(new_heredoc);
		return ;
	}
	new_heredoc->next = NULL;
	if (!cmd->heredocs)
		cmd->heredocs = new_heredoc;
	else
	{
		current = cmd->heredocs;
		while (current->next)
			current = current->next;
		current->next = new_heredoc;
	}
}

int	handle_quote_start(char c, char *quote)
{
	if ((c == '\'' || c == '"') && *quote == 0)
	{
		*quote = c;
		return (1);
	}
	return (0);
}

int	handle_quote_end(char c, char *quote)
{
	if (c == *quote)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

t_arg	*create_arg(char *content)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->content = ft_strdup(content);
	if (!arg->content)
	{
		free(arg);
		return (NULL);
	}
	arg->next = NULL;
	return (arg);
}
