/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:09:46 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:09:48 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (!ft_strcmp(cmd_name, "cd") || !ft_strcmp(cmd_name, "pwd")
		|| !ft_strcmp(cmd_name, "echo") || !ft_strcmp(cmd_name, "export")
		|| !ft_strcmp(cmd_name, "unset") || !ft_strcmp(cmd_name, "env")
		|| !ft_strcmp(cmd_name, "exit"))
		return (1);
	return (0);
}

int	is_builtin_pipeable(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"env"))
		return (1);
	return (0);
}

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	execute_command(t_cmd *cmd, char **envp)
{
	char	**args;

	args = convert_args_to_array(cmd->args);
	if (!args || !args[0])
	{
		ft_free_array(args);
		exit(1);
	}
	if (handle_redirections(cmd) == -1)
	{
		ft_free_array(args);
		exit(1);
	}
	if (is_builtin(args[0]))
	{
		if (is_builtin_pipeable(args[0]))
			execute_builtin_in_pipe(args, envp);
		else
			exit(execute_builtin(args, &envp));
	}
	else
		execve_external(args, envp);
	ft_free_array(args);
	exit(127);
}

void	execute_builtin_in_pipe(char **args, char **envp)
{
	int	status;

	status = execute_builtin(args, &envp);
	exit(status);
}
