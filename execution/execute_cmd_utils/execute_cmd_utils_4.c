/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:24:15 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:25:21 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_heredoc_setup_failure(t_cmd *cmd, t_exec_context *ctx)
{
	if (setup_heredoc_input(cmd, ctx->saved_stdin, ctx->saved_stdout,
			ctx->args) == -1)
	{
		if (ctx->saved_stdin != -1)
			close(ctx->saved_stdin);
		if (ctx->saved_stdout != -1)
			close(ctx->saved_stdout);
		return (1);
	}
	return (0);
}

int	setup_command_execution(t_cmd *cmd, t_exec_context *ctx, char **envp)
{
	(void)envp;
	ctx->saved_stdin = -1;
	ctx->saved_stdout = -1;
	if (cmd->heredocs || cmd->input_redirs || cmd->output_redirs)
	{
		ctx->saved_stdin = dup(STDIN_FILENO);
		ctx->saved_stdout = dup(STDOUT_FILENO);
		if (ctx->saved_stdin == -1 || ctx->saved_stdout == -1)
		{
			if (ctx->saved_stdin != -1)
				close(ctx->saved_stdin);
			if (ctx->saved_stdout != -1)
				close(ctx->saved_stdout);
			return (1);
		}
	}
	if (handle_heredoc_setup_failure(cmd, ctx))
		return (1);
	return (0);
}
