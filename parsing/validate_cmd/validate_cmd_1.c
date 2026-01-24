/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:48:36 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/25 10:07:53 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validate_cmd(t_cmd *commands)
{
	t_cmd	*current;

	if (!commands || (commands->args == NULL && commands->input_redirs == NULL
			&& commands->output_redirs == NULL && commands->heredocs == NULL))
		return (1);
	current = commands;
	while (current)
	{
		if (!current->args && current->input_redirs)
		{
			write(2, "xero: syntax error: input redirection without command\n",
				54);
			return (0);
		}
		if (current->input_redirs && (!current->input_redirs->file
				|| !current->input_redirs->file[0]))
		{
			write(2, "xero: syntax error: invalid input redirection\n", 47);
			return (0);
		}
		current = current->next;
	}
	return (1);
}
