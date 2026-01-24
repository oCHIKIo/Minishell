/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:09:00 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 12:16:33 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	setup_heredoc_preparation(t_heredoc_exec_context *ctx)
{
	if (prepare_heredoc_delimiter(ctx) == -1)
		return (-1);
	if (setup_pipe_for_last(ctx) == -1)
		return (-1);
	return (0);
}

static void	setup_parent_context(t_heredoc_exec_context *ctx,
		t_hrdoc_prnt_cntx *parent_ctx)
{
	free(ctx->clean_delimiter);
	parent_ctx->current = ctx->current;
	parent_ctx->last_heredoc = ctx->last_heredoc;
	parent_ctx->pipe_fd[0] = ctx->pipe_fd[0];
	parent_ctx->pipe_fd[1] = ctx->pipe_fd[1];
}

static int	handle_fork_result(pid_t pid, t_heredoc_exec_context *ctx,
		t_hrdoc_prnt_cntx *parent_ctx)
{
	if (pid == 0)
		handle_child_process(ctx);
	else if (pid > 0)
	{
		setup_parent_context(ctx, parent_ctx);
		if (handle_heredoc_parent_process(parent_ctx) == -1)
			return (-1);
	}
	else
		return (handle_fork_error(ctx));
	return (0);
}

static int	process_single_heredoc(t_heredoc_exec_context *ctx,
		t_hrdoc_prnt_cntx *parent_ctx)
{
	pid_t	pid;

	if (setup_heredoc_preparation(ctx) == -1)
		return (-1);
	parent_ctx->old_handler = signal(SIGINT, SIG_IGN);
	pid = fork();
	return (handle_fork_result(pid, ctx, parent_ctx));
}

int	setup_heredocs(t_heredoc *heredocs, char **envp)
{
	t_heredoc_exec_context	ctx;
	t_hrdoc_prnt_cntx		parent_ctx;

	if (!heredocs)
		return (0);
	initialize_heredoc_context(&ctx, heredocs, envp);
	while (ctx.current)
	{
		if (process_single_heredoc(&ctx, &parent_ctx) == -1)
			return (-1);
		ctx.current = ctx.current->next;
	}
	return (finalize_pipe_setup(ctx.pipe_fd));
}
