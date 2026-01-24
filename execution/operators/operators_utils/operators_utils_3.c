/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:09:50 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:09:51 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exit_with_error(char *path, char *cmd, char *msg, int code)
{
	write(2, "xero: ", 6);
	write(2, cmd, ft_strlen(cmd));
	write(2, msg, ft_strlen(msg));
	if (path)
		free(path);
	exit(code);
}

static void	handle_command_not_found(char **args)
{
	struct stat	st;
	char		*cmd;

	if (!args || !args[0])
		exit(127);
	cmd = args[0];
	if (is_absolute_or_relative_path(cmd))
	{
		if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
			exit_with_error(NULL, cmd, ": Is a directory\n", 126);
		else if (access(cmd, F_OK) == 0)
			exit_with_error(NULL, cmd, ": Permission denied\n", 126);
		else
			exit_with_error(NULL, cmd, ": No such file or directory\n", 127);
	}
	else
		exit_with_error(NULL, cmd, ": command not found\n", 127);
}

static void	validate_executable_path(char *path, char **args)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		exit_with_error(path, args[0], ": Is a directory\n", 126);
}

void	execve_external(char **args, char **envp)
{
	char	*path;

	if (!args || !args[0] || !envp)
		exit(127);
	path = find_command_in_path(args[0], envp);
	if (!path)
		handle_command_not_found(args);
	validate_executable_path(path, args);
	execve(path, args, envp);
	if (errno == EACCES)
		exit_with_error(path, args[0], ": Permission denied\n", 126);
	else if (errno == ENOEXEC)
		exit_with_error(path, args[0], ": Exec format error\n", 0);
	else
	{
		write(2, "xero: ", 6);
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": ", 2);
		perror("");
		free(path);
		exit(126);
	}
}
