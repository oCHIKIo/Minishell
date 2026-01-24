/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:49:30 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/31 23:16:39 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_empty_command_input(char *cmd_input,
		int *current_exit_status)
{
	(void)current_exit_status;
	if (!cmd_input || !cmd_input[0])
		return (1);
	return (0);
}

static int	process_single_command(char *cmd_input, char ***my_envp,
		int *current_exit_status)
{
	t_prcs_single_cmd	x;

	if (handle_empty_command_input(cmd_input, current_exit_status))
		return (1);
	x.trimmed = cmd_input;
	x.tokens = parse_and_expand_input(x.trimmed, *my_envp);
	if (!x.tokens)
		return (1);
	x.commands = create_and_validate_commands(x.tokens, current_exit_status);
	if (!x.commands)
		return (1);
	x.params.my_envp = my_envp;
	x.params.tokens = x.tokens;
	x.params.input = x.trimmed;
	x.params.current_exit_status = current_exit_status;
	return (execute_validated_commands(x.commands, &x.params));
}

static int	has_unquoted_semicolon(char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && quote == 0)
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		else if (input[i] == ';' && quote == 0)
			return (1);
		i++;
	}
	return (0);
}

int	process_input_line(char *input, char ***my_envp, int *current_exit_status)
{
	int	result;

	if (has_unquoted_semicolon(input))
	{
		ft_putstr_fd("xero: semicolons are not handled\n", 2);
		*current_exit_status = 2;
		exit_status(2, 1);
		set_signal(0);
		free(input);
		return (1);
	}
	result = process_single_command(input, my_envp, current_exit_status);
	free(input);
	return (result);
}
