/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:05:14 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/31 11:05:16 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_builtin_commands(char **args, char ***envp)
{
	if (ft_strcmp(args[0], "cd") == 0)
		return (cd_builtin(args, envp));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd_builtin(args, envp));
	if (ft_strcmp(args[0], "echo") == 0)
		return (echo_builtin(args, envp));
	if (ft_strcmp(args[0], "export") == 0)
		return (export_builtin(args, envp));
	if (ft_strcmp(args[0], "unset") == 0)
		return (unset_builtin(args, envp));
	if (ft_strcmp(args[0], "env") == 0)
		return (env_builtin(args, envp));
	if (ft_strcmp(args[0], "exit") == 0)
		return (exit_builtin(args, envp));
	return (1);
}

int	execute_builtin(char **args, char ***envp)
{
	if (!args || !args[0])
		return (1);
	if (run_builtin_commands(args, envp) == 0)
		return (0);
	if (ft_strcmp(args[0], "xero") == 0 && args[1] && !args[2])
	{
		if (ft_strcmp(args[1], "--version") == 0)
		{
			print_xero_version();
			return (0);
		}
		if (ft_strcmp(args[1], "--devs") == 0)
		{
			print_xero_developers();
			return (0);
		}
	}
	return (1);
}

static int	wait_for_child(pid_t pid)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	return (exit_code);
}

int	execute_external(char **args, char **envp)
{
	t_exec_external_state	st;

	st.exit_code = 0;
	setup_parent_execution_signals();
	st.pid = fork();
	if (st.pid == 0)
	{
		setup_child_signals();
		execve_external(args, envp);
		exit(127);
	}
	else if (st.pid > 0)
		st.exit_code = wait_for_child(st.pid);
	else
	{
		perror("xero: fork");
		st.exit_code = 1;
	}
	setup_signals();
	return (st.exit_code);
}

char	**initialize_environment(char **envp)
{
	char	**my_envp;
	char	buffer[PATH_MAX];
	char	*current_pwd;

	my_envp = copy_envp(envp);
	if (!my_envp)
		return (NULL);
	if (!get_env_value_from_envp(my_envp, "PWD"))
	{
		current_pwd = getcwd(buffer, sizeof(buffer));
		if (current_pwd)
			my_envp = add_env_var(my_envp, "PWD", current_pwd);
	}
	if (!get_env_value_from_envp(my_envp, "OLDPWD"))
		my_envp = add_env_var(my_envp, "OLDPWD", "");
	return (my_envp);
}
