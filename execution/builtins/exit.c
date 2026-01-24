/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:08:27 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:08:28 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cleanup_and_exit(int exit_code, char ***envp)
{
	if (envp && *envp)
		free_envp(*envp);
	exit(exit_code);
}

int	is_numeric(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	print_exit_numeric_error(const char *arg, char ***envp)
{
	write(2, "xero: exit: ", 12);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
	cleanup_and_exit(2, envp);
}

static int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	exit_builtin(char **args, char ***envp)
{
	int	arg_count;
	int	exit_code;

	printf("exit\n");
	arg_count = count_args(args);
	if (arg_count == 1)
		cleanup_and_exit(0, envp);
	else if (arg_count == 2)
	{
		if (!is_numeric(args[1]))
			print_exit_numeric_error(args[1], envp);
		exit_code = ft_atoi(args[1]);
		cleanup_and_exit((unsigned char)exit_code, envp);
	}
	else
	{
		if (!is_numeric(args[1]))
			print_exit_numeric_error(args[1], envp);
		write(2, "xero: exit: too many arguments\n", 31);
		return (1);
	}
	return (0);
}
