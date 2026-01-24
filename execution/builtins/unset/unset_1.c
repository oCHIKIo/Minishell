/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:08:06 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:08:07 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	is_valid_unset_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	print_unset_error(char *arg)
{
	write(2, "xero: unset: `", 14);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 27);
	return (1);
}

static int	process_single_unset_arg(char *arg, char ***envp)
{
	char	**new_envp;

	if (!is_valid_unset_identifier(arg))
		return (print_unset_error(arg));
	new_envp = remove_env_var(*envp, arg);
	if (new_envp)
		*envp = new_envp;
	return (0);
}

int	unset_builtin(char **args, char ***envp)
{
	int	i;
	int	status;

	if (!args || !envp || !*envp)
		return (1);
	if (!args[1])
		return (0);
	status = 0;
	i = 1;
	while (args[i])
	{
		if (process_single_unset_arg(args[i], envp) == 1)
			status = 1;
		i++;
	}
	return (status);
}
