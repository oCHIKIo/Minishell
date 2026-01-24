/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:08:31 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:08:33 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_pwd_options(char **args)
{
	if (args[1] && args[1][0] == '-')
	{
		write(2, "xero: pwd: ", 11);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": options are forbiden\n", 23);
		write(2, "pwd: usage: pwd\n", 16);
		return (2);
	}
	return (0);
}

static int	execute_pwd_command(char ***envp)
{
	t_pwd_ctx	vars;
	char		*pwd_env;

	vars.current_dir = getcwd(vars.buffer, sizeof(vars.buffer));
	if (!vars.current_dir)
	{
		pwd_env = get_env_value_from_envp(*envp, "PWD");
		if (pwd_env)
		{
			write(1, pwd_env, ft_strlen(pwd_env));
			write(1, "\n", 1);
			return (0);
		}
		write(2, "xero: pwd: error retrieving current directory\n", 45);
		return (1);
	}
	write(1, vars.current_dir, ft_strlen(vars.current_dir));
	write(1, "\n", 1);
	return (0);
}

int	pwd_builtin(char **args, char ***envp)
{
	int	option_result;

	option_result = check_pwd_options(args);
	if (option_result != 0)
		return (option_result);
	return (execute_pwd_command(envp));
}
