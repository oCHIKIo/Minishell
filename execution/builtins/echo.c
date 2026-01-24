/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:08:17 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:08:19 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_builtin(char **args, char ***envp)
{
	int	i;
	int	newline;
	int	first_arg;

	(void)envp;
	i = 1;
	newline = 1;
	first_arg = 1;
	while (args[i] && is_n_option(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		if (!first_arg)
			write(1, " ", 1);
		write(1, args[i], ft_strlen(args[i]));
		first_arg = 0;
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
