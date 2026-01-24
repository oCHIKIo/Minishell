/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:12:29 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/07 12:12:31 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*trim_input_spaces(char *input, int *len)
{
	char	*trimmed;

	trimmed = input;
	while (trimmed[0] == ' ')
		trimmed++;
	*len = ft_strlen(trimmed);
	while (*len > 0 && trimmed[*len - 1] == ' ')
		(*len)--;
	return (trimmed);
}

t_check	validate_pipe_at_start(char *trimmed)
{
	if (trimmed[0] == '|')
	{
		write(2, "xero: syntax error near unexpected token `|'\n", 46);
		return (FAIL);
	}
	return (SUCCESS);
}

static t_check	check_redirect_count_and_report(char c, int count)
{
	if (count > 2)
	{
		if (c == '<')
			write(2, "xero: syntax error near unexpected token `<<<'\n", 48);
		else
			write(2, "xero: syntax error near unexpected token `>>'\n", 47);
		return (FAIL);
	}
	return (SUCCESS);
}

t_check	validate_redirect_count(char *trimmed, int len)
{
	t_redirect_check	vars;

	vars.i = 0;
	while (vars.i < len)
	{
		if (trimmed[vars.i] == '>' || trimmed[vars.i] == '<')
		{
			vars.c = trimmed[vars.i];
			vars.count = 0;
			while (vars.i + vars.count < len
				&& trimmed[vars.i + vars.count] == vars.c)
				vars.count++;
			if (check_redirect_count_and_report(vars.c, vars.count) == FAIL)
				return (FAIL);
			vars.i += vars.count;
		}
		else
			vars.i++;
	}
	return (SUCCESS);
}

t_check	validate_operators_at_end(char *trimmed, int len)
{
	if (len > 0 && (trimmed[len - 1] == '|' || trimmed[len - 1] == '>'
			|| trimmed[len - 1] == '<'))
	{
		write(2, "xero: syntax error near unexpected token `newline'\n", 52);
		return (FAIL);
	}
	return (SUCCESS);
}
