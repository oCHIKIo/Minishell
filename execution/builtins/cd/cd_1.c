/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:07:18 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:07:20 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cd_builtin(char **args, char ***envp)
{
	if (validate_cd_args(args) != 0)
		return (1);
	return (execute_cd_change(args, envp));
}
