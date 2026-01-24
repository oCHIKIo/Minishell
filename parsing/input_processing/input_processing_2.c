/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:03:07 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/25 16:03:07 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*parse_and_expand_input(char *input, char **my_envp)
{
	t_token	*tokens;

	tokens = tokenize(input);
	if (!tokens)
		return (NULL);
	expand_tokens(tokens, my_envp);
	return (tokens);
}

t_cmd	*create_and_validate_commands(t_token *tokens, int *current_exit_status)
{
	t_cmd	*commands;

	commands = create_cmd(tokens);
	if (!commands)
	{
		free_tokens(tokens);
		return (NULL);
	}
	if (!validate_cmd(commands))
	{
		free_cmd(commands);
		free_tokens(tokens);
		exit_status(2, 1);
		*current_exit_status = 2;
		return (NULL);
	}
	return (commands);
}

int	execute_validated_commands(t_cmd *commands, t_execution_params *params)
{
	if (process_all_heredocs(commands, *(params->my_envp)) == -1)
	{
		free_cmd(commands);
		free_tokens(params->tokens);
		*(params->current_exit_status) = exit_status(0, 0);
		return (1);
	}
	*(params->current_exit_status) = execute_commands(commands, params->my_envp,
			*(params->current_exit_status));
	if (get_signal() == SIGINT)
		*(params->current_exit_status) = 130;
	else if (get_signal() == SIGQUIT)
		*(params->current_exit_status) = 131;
	set_signal(0);
	free_cmd(commands);
	free_tokens(params->tokens);
	return (0);
}
