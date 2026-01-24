/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:49:24 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/24 16:05:43 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_redir_list(t_redir *redir)
{
	t_redir	*redir_next;

	while (redir)
	{
		redir_next = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = redir_next;
	}
}

static void	free_heredoc_list(t_heredoc *heredoc)
{
	t_heredoc	*heredoc_next;

	while (heredoc)
	{
		heredoc_next = heredoc->next;
		if (heredoc->delimiter)
			free(heredoc->delimiter);
		free(heredoc);
		heredoc = heredoc_next;
	}
}

static void	free_heredoc_file(char *heredoc_file)
{
	if (heredoc_file)
	{
		unlink(heredoc_file);
		free(heredoc_file);
	}
}

void	free_redirs_and_heredocs(t_cmd *cmd)
{
	free_redir_list(cmd->input_redirs);
	free_redir_list(cmd->output_redirs);
	free_heredoc_list(cmd->heredocs);
	free_heredoc_file(cmd->heredoc_file);
}

void	free_cmd(t_cmd *commands)
{
	t_cmd	*current;
	t_cmd	*next;

	current = commands;
	while (current)
	{
		next = current->next;
		free_arg_list(current->args);
		free_redirs_and_heredocs(current);
		free(current);
		current = next;
	}
}
