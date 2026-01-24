/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:10:13 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:10:14 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_empty_args(char **args, int redir_result, char **envp,
		t_cmd *cmd)
{
	ft_free_array(args);
	if (redir_result == -1)
		exit(1);
	else if (cmd->heredocs || cmd->input_redirs)
	{
		args = malloc(sizeof(char *) * 2);
		if (!args)
			exit(1);
		args[0] = ft_strdup("cat");
		if (!args[0])
		{
			free(args);
			exit(1);
		}
		args[1] = NULL;
		execve_external(args, envp);
		ft_free_array(args);
		exit(127);
	}
	else
		exit(0);
}

static void	execute_command_with_args(char **args, char **envp)
{
	if (is_builtin(args[0]))
		exit(execute_builtin(args, &envp));
	else
		execve_external(args, envp);
	ft_free_array(args);
	exit(127);
}

void	validate_and_execute(char **args, int redir_result, char **envp,
		t_cmd *cmd)
{
	if (!args || !args[0])
	{
		handle_empty_args(args, redir_result, envp, cmd);
		return ;
	}
	if (redir_result == -1)
	{
		ft_free_array(args);
		exit(1);
	}
	execute_command_with_args(args, envp);
}
