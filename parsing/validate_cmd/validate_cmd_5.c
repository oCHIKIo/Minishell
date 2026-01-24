/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:49:07 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/31 11:15:40 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_check	validate_consecutive_pipes(char *trimmed, int len)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (trimmed[i] == '|' && trimmed[i + 1] == '|')
		{
			write(2, "xero: syntax error near unexpected token `|'\n", 46);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

t_check	validate_operator_positions(char *input)
{
	char	*trimmed;
	int		len;

	trimmed = trim_input_spaces(input, &len);
	if (len == 0)
		return (SUCCESS);
	if (validate_pipe_at_start(trimmed) == FAIL)
		return (FAIL);
	if (validate_redirect_count(trimmed, len) == FAIL)
		return (FAIL);
	if (validate_operators_at_end(trimmed, len) == FAIL)
		return (FAIL);
	if (validate_consecutive_pipes(trimmed, len) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

t_check	validate_syntax_loop(t_token *current, t_token **cmd_start,
		t_token_type *last_oper)
{
	while (current)
	{
		if (validate_command_start(current, cmd_start) == FAIL
			|| validate_pipe(current, cmd_start, last_oper) == FAIL
			|| validate_redirection_sequence(current, last_oper) == FAIL)
			return (FAIL);
		current = current->next;
	}
	return (SUCCESS);
}

t_check	validate_syntax(t_token *tokens)
{
	t_token			*cmd_start;
	t_token_type	last_oper;

	if (!tokens)
		return (FAIL);
	if (tokens->type == WORD && !tokens->next)
		return (SUCCESS);
	if (tokens->type == PIPE)
	{
		write(2, "xero: syntax error near unexpected token `|'\n", 46);
		return (FAIL);
	}
	cmd_start = NULL;
	last_oper = WORD;
	if (validate_syntax_loop(tokens, &cmd_start, &last_oper) == FAIL)
		return (FAIL);
	if (last_oper == PIPE || its_redirection(last_oper))
	{
		write(2, "xero: syntax error near unexpected token `newline'\n", 52);
		return (FAIL);
	}
	return (validate_final_command(cmd_start, NULL));
}

t_check	validate_final_command(t_token *cmd_start, t_token *current)
{
	t_token	*end;

	if (!cmd_start)
		return (FAIL);
	if (word_is_builtin(cmd_start->content))
	{
		end = current;
		if (!its_valid_builtin(cmd_start->content, cmd_start->next, end))
			return (FAIL);
	}
	return (SUCCESS);
}
