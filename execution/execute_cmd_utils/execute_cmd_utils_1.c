/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:08:37 by aben-dri          #+#    #+#             */
/*   Updated: 2025/08/01 11:47:18 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	restore_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

int	handle_child_process_exit(int status)
{
	int	exit_code;

	exit_code = 0;
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			exit_code = 130;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			write(STDOUT_FILENO, "Quit: 3\n", 8);
			exit_code = 131;
		}
		else
			exit_code = 128 + WTERMSIG(status);
	}
	return (exit_code);
}

static int	handle_setup_failure(int setup_result, t_exec_context *ctx)
{
	restore_fds(ctx->saved_stdin, ctx->saved_stdout);
	ft_free_array(ctx->args);
	return (setup_result);
}

int	execute_single_command(t_cmd *cmd, char ***envp, int current_exit_status)
{
	t_exec_context	ctx;
	int				setup_result;

	ctx.args = convert_args_to_array(cmd->args);
	ctx.exit_code = current_exit_status;
	if (!ctx.args || !ctx.args[0] || (ctx.args[0]
			&& ft_strlen(ctx.args[0]) == 0))
	{
		if (ctx.args && ctx.args[0] && ft_strlen(ctx.args[0]) == 0)
		{
			write(2, "xero: : command not found\n", 26);
			ft_free_array(ctx.args);
			exit_status(127, 1);
			return (127);
		}
		return (handle_empty_command(cmd, ctx.args, *envp, ctx.exit_code));
	}
	setup_result = setup_command_execution(cmd, &ctx, *envp);
	if (setup_result != 0)
		return (handle_setup_failure(setup_result, &ctx));
	ctx.exit_code = execute_command_type(cmd, &ctx, envp);
	restore_fds(ctx.saved_stdin, ctx.saved_stdout);
	ft_free_array(ctx.args);
	return (ctx.exit_code);
}

int	execute_commands(t_cmd *commands, char ***envp, int current_exit_status)
{
	t_exec_cmd_vars	v;

	v.exit_code = current_exit_status;
	if (!commands)
		return (v.exit_code);
	v.current = commands;
	v.has_pipe = 0;
	while (v.current)
	{
		if (v.current->next)
		{
			v.has_pipe = 1;
			break ;
		}
		v.current = v.current->next;
	}
	if (v.has_pipe)
		v.exit_code = execute_pipeline(commands, *envp, v.exit_code);
	else
		v.exit_code = execute_single_command(commands, envp, v.exit_code);
	if (get_signal())
		v.exit_code = get_exit_status_from_signal(get_signal());
	exit_status(v.exit_code, 1);
	return (v.exit_code);
}
