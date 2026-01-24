/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:07:23 by aben-dri          #+#    #+#             */
/*   Updated: 2025/08/04 10:30:39 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_cd_target_directory(char **args, char **envp)
{
	char	*home;

	if (!args[1])
	{
		home = get_env_value_from_envp(envp, "HOME");
		if (!home)
		{
			write(2, "xero: cd: HOME not set\n", 23);
			return (NULL);
		}
		return (home);
	}
	return (args[1]);
}

void	update_oldpwd(char ***envp, char *old_pwd)
{
	*envp = add_env_var(*envp, "OLDPWD", old_pwd);
}

void	update_pwd(char ***envp)
{
	char	buffer[1024];
	char	*current_pwd;

	current_pwd = getcwd(buffer, sizeof(buffer));
	if (!current_pwd)
		return ;
	*envp = add_env_var(*envp, "PWD", current_pwd);
}

int	validate_cd_args(char **args)
{
	int	arg_count;
	int	i;

	i = 1;
	arg_count = 0;
	while (args[i])
	{
		arg_count++;
		i++;
	}
	if (arg_count > 1)
	{
		write(2, "xero: cd: too many arguments\n", 29);
		return (1);
	}
	return (0);
}

int	execute_cd_change(char **args, char ***envp)
{
	char	buffer[1024];
	char	*current_pwd;
	char	*target_dir;

	current_pwd = getcwd(buffer, sizeof(buffer));
	target_dir = get_cd_target_directory(args, *envp);
	if (!target_dir)
		return (1);
	if (chdir(target_dir) != 0)
	{
		write(2, "xero: cd: ", 10);
		write(2, target_dir, ft_strlen(target_dir));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	if (current_pwd)
		update_oldpwd(envp, current_pwd);
	update_pwd(envp);
	return (0);
}
