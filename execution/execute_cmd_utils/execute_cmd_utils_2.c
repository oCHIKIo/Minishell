/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:08:42 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:08:43 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_heredocs_and_redirections(t_cmd *cmd, char **envp,
		t_saved_fds *fds, char **args)
{
	if (cmd->heredocs)
	{
		if (setup_heredocs(cmd->heredocs, envp) == -1)
		{
			restore_fds(fds->saved_stdin, fds->saved_stdout);
			ft_free_array(args);
			return (130);
		}
	}
	if (handle_redirections(cmd) == -1)
	{
		restore_fds(fds->saved_stdin, fds->saved_stdout);
		ft_free_array(args);
		return (1);
	}
	return (0);
}

int	handle_empty_command(t_cmd *cmd, char **args, char **envp, int exit_code)
{
	t_saved_fds	fds;
	int			result;

	if (cmd->output_redirs || cmd->heredocs || cmd->input_redirs)
	{
		fds.saved_stdin = dup(STDIN_FILENO);
		fds.saved_stdout = dup(STDOUT_FILENO);
		if (fds.saved_stdin == -1 || fds.saved_stdout == -1)
		{
			if (fds.saved_stdin != -1)
				close(fds.saved_stdin);
			if (fds.saved_stdout != -1)
				close(fds.saved_stdout);
			ft_free_array(args);
			return (1);
		}
		result = handle_heredocs_and_redirections(cmd, envp, &fds, args);
		if (result != 0)
			return (result);
		restore_fds(fds.saved_stdin, fds.saved_stdout);
	}
	ft_free_array(args);
	return (exit_code);
}

int	setup_heredoc_input(t_cmd *cmd, int saved_stdin, int saved_stdout,
		char **args)
{
	int	fd;

	if (!cmd->heredoc_file)
		return (0);
	fd = open(cmd->heredoc_file, O_RDONLY);
	if (fd == -1)
	{
		perror("xero: heredoc");
		if (saved_stdin != -1 || saved_stdout != -1)
			restore_fds(saved_stdin, saved_stdout);
		ft_free_array(args);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("xero: dup2");
		close(fd);
		if (saved_stdin != -1 || saved_stdout != -1)
			restore_fds(saved_stdin, saved_stdout);
		ft_free_array(args);
		return (-1);
	}
	close(fd);
	return (0);
}

int	execute_builtin_command(t_builtin_context *ctx)
{
	int	exit_code;

	if (handle_redirections(ctx->cmd) == -1)
	{
		restore_fds(ctx->saved_stdin, ctx->saved_stdout);
		ft_free_array(ctx->args);
		return (1);
	}
	exit_code = execute_builtin(ctx->args, ctx->envp);
	return (exit_code);
}
