/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:09:18 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:09:19 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_heredoc	*find_last_heredoc(t_heredoc *heredocs)
{
	t_heredoc	*last_heredoc;

	last_heredoc = heredocs;
	while (last_heredoc->next)
		last_heredoc = last_heredoc->next;
	return (last_heredoc);
}

int	setup_pipe_for_last(t_heredoc_exec_context *ctx)
{
	if (ctx->current == ctx->last_heredoc)
	{
		if (pipe(ctx->pipe_fd) == -1)
		{
			free(ctx->clean_delimiter);
			return (-1);
		}
	}
	return (0);
}

void	handle_child_process(t_heredoc_exec_context *ctx)
{
	if (ctx->current == ctx->last_heredoc)
	{
		close(ctx->pipe_fd[0]);
		read_heredoc_child(ctx->pipe_fd[1], ctx->clean_delimiter,
			ctx->should_expand, ctx->envp);
		close(ctx->pipe_fd[1]);
	}
	else
		read_heredoc_child(-1, ctx->clean_delimiter, ctx->should_expand,
			ctx->envp);
	free(ctx->clean_delimiter);
	exit(0);
}

int	handle_heredoc_parent_process(t_hrdoc_prnt_cntx *ctx)
{
	waitpid(-1, &ctx->status, 0);
	signal(SIGINT, ctx->old_handler);
	if (WIFSIGNALED(ctx->status) && WTERMSIG(ctx->status) == SIGINT)
	{
		if (ctx->current == ctx->last_heredoc)
		{
			close(ctx->pipe_fd[0]);
			close(ctx->pipe_fd[1]);
		}
		write(STDOUT_FILENO, "\n", 1);
		exit_status(130, 1);
		set_signal(0);
		return (-1);
	}
	return (0);
}

int	finalize_pipe_setup(int pipe_fd[2])
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}
