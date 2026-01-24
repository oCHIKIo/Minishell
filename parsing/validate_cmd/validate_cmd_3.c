/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:48:52 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/31 11:14:46 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_check	validate_redirection(t_token *curr, t_token_type last_oper)
{
	if (its_redirection(last_oper) || !curr->next || curr->next->type != WORD)
		return (FAIL);
	return (SUCCESS);
}

t_check	validate_command_start(t_token *current, t_token **cmd_start)
{
	if (current->type == WORD)
	{
		if (!*cmd_start)
			*cmd_start = current;
		return (SUCCESS);
	}
	return (SUCCESS);
}

t_check	validate_pipe(t_token *current, t_token **cmd_start,
		t_token_type *last_oper)
{
	if (current->type == PIPE)
	{
		if (!*cmd_start || !current->next || current->next->type != WORD)
			return (FAIL);
		if (word_is_builtin((*cmd_start)->content)
			&& !its_valid_builtin((*cmd_start)->content, (*cmd_start)->next,
				current))
			return (FAIL);
		*cmd_start = NULL;
		*last_oper = PIPE;
	}
	return (SUCCESS);
}

t_check	validate_redirection_sequence(t_token *current, t_token_type *last_oper)
{
	if (its_redirection(current->type))
	{
		if (validate_redirection(current, *last_oper) == FAIL)
			return (FAIL);
		current = current->next;
		if (!current)
			return (FAIL);
		*last_oper = current->type;
	}
	return (SUCCESS);
}
