/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:07:29 by aben-dri          #+#    #+#             */
/*   Updated: 2025/08/02 15:31:46 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	export_builtin(char **args, char ***envp)
{
	int	i;
	int	overall_status;

	if (!args || !envp || !*envp)
		return (1);
	if (!args[1])
	{
		print_exported_vars(*envp);
		return (0);
	}
	overall_status = 0;
	i = 1;
	while (args[i])
	{
		if (handle_single_export_arg(args[i], envp) == 1)
			overall_status = 1;
		i++;
	}
	return (overall_status);
}
