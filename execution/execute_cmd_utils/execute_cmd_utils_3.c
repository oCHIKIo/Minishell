/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:08:46 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:24:30 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_child_process(t_external_context *ctx)
{
	setup_child_signals();
	if (handle_redirections(ctx->cmd) == -1)
	{
		restore_fds(ctx->saved_stdin, ctx->saved_stdout);
		exit(1);
	}
	if (ctx->saved_stdin != -1)
		close(ctx->saved_stdin);
	if (ctx->saved_stdout != -1)
		close(ctx->saved_stdout);
	if (ctx->args && ctx->args[0] && (is_builtin(ctx->args[0])
			|| is_special_xero_command(ctx->args)))
		execute_builtin_in_pipe(ctx->args, ctx->envp);
	else
		execve_external(ctx->args, ctx->envp);
	exit(127);
}

int	handle_parent_process(pid_t pid)
{
	int	status;
	int	exit_code;

	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		exit_code = handle_child_process_exit(status);
	}
	else
	{
		perror("xero: fork");
		exit_code = 1;
	}
	return (exit_code);
}

int	execute_external_command(t_external_context *ctx)
{
	pid_t	pid;
	int		exit_code;

	setup_parent_execution_signals();
	pid = fork();
	if (pid == 0)
		execute_child_process(ctx);
	exit_code = handle_parent_process(pid);
	setup_signals();
	return (exit_code);
}

int	execute_command_type(t_cmd *cmd, t_exec_context *ctx, char ***envp)
{
	t_builtin_context	builtin_ctx;
	t_external_context	external_ctx;

	if (ctx->args && ctx->args[0] && (is_builtin(ctx->args[0])
			|| is_special_xero_command(ctx->args))
		&& !is_builtin_pipeable(ctx->args[0]))
	{
		builtin_ctx.cmd = cmd;
		builtin_ctx.args = ctx->args;
		builtin_ctx.envp = envp;
		builtin_ctx.saved_stdin = ctx->saved_stdin;
		builtin_ctx.saved_stdout = ctx->saved_stdout;
		return (execute_builtin_command(&builtin_ctx));
	}
	else
	{
		external_ctx.cmd = cmd;
		external_ctx.args = ctx->args;
		external_ctx.envp = *envp;
		external_ctx.saved_stdin = ctx->saved_stdin;
		external_ctx.saved_stdout = ctx->saved_stdout;
		return (execute_external_command(&external_ctx));
	}
}
