/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:08:22 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:08:24 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_env_entry(char *entry)
{
	if (!entry || !entry[0])
		return (0);
	if (entry[0] == '=')
		return (0);
	if (!ft_isalpha(entry[0]) && entry[0] != '_')
		return (0);
	return (1);
}

int	env_builtin(char **args, char ***envp)
{
	int	i;

	if (args[1])
	{
		write(2, "xero: env: with no options or arguments\n", 40);
		return (1);
	}
	i = 0;
	while ((*envp)[i])
	{
		if (is_valid_env_entry((*envp)[i]))
		{
			write(1, (*envp)[i], ft_strlen((*envp)[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
