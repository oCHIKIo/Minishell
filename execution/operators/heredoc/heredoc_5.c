/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:09:23 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:09:24 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	initialize_heredoc_context(t_heredoc_exec_context *ctx,
		t_heredoc *heredocs, char **envp)
{
	ctx->last_heredoc = find_last_heredoc(heredocs);
	ctx->current = heredocs;
	ctx->envp = envp;
}

int	prepare_heredoc_delimiter(t_heredoc_exec_context *ctx)
{
	ctx->clean_delimiter = strip_quotes_from_delimiter(ctx->current->delimiter);
	if (!ctx->clean_delimiter)
		return (-1);
	ctx->should_expand = should_expand_heredoc(ctx->current->delimiter);
	return (0);
}

int	handle_fork_error(t_heredoc_exec_context *ctx)
{
	free(ctx->clean_delimiter);
	if (ctx->current == ctx->last_heredoc)
	{
		close(ctx->pipe_fd[0]);
		close(ctx->pipe_fd[1]);
	}
	return (-1);
}
