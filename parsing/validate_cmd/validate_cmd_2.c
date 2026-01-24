/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:48:44 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/26 22:15:48 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_check	check_arithmetic_evaluation(char *input)
{
	int	i;
	int	paren_count;

	i = 0;
	paren_count = 0;
	while (input[i])
	{
		if (input[i] == '(')
			paren_count++;
		else if (input[i] == ')')
			paren_count--;
		if (paren_count > 1)
		{
			write(2,
				"xero: unsupported syntax: arithmetic evaluation not handled\n",
				61);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

int	how_many_args(t_token *start, t_token *end)
{
	if (!start || start == end || start->type != WORD)
		return (0);
	return (1 + how_many_args(start->next, end));
}

t_check	word_is_builtin(char *word)
{
	if (!word)
		return (FAIL);
	if (!ft_strcmp(word, "cd") || !ft_strcmp(word, "pwd") || !ft_strcmp(word,
			"echo") || !ft_strcmp(word, "export") || !ft_strcmp(word, "unset")
		|| !ft_strcmp(word, "env") || !ft_strcmp(word, "exit"))
		return (SUCCESS);
	return (FAIL);
}

int	its_valid_builtin(char *cmnd, t_token *start, t_token *end)
{
	int	args_num;

	args_num = how_many_args(start, end);
	if (!ft_strcmp(cmnd, "cd"))
		return (args_num <= 1);
	if (!ft_strcmp(cmnd, "exit"))
		return (1);
	if (!ft_strcmp(cmnd, "pwd") || !ft_strcmp(cmnd, "env"))
		return (args_num == 0);
	if (!ft_strcmp(cmnd, "echo") || !ft_strcmp(cmnd, "export")
		|| !ft_strcmp(cmnd, "unset"))
		return (1);
	return (0);
}

t_check	its_redirection(t_token_type type)
{
	if (type == HEREDOC || type == REDIR_APPEND || type == REDIR_OUT
		|| type == REDIR_IN)
		return (SUCCESS);
	return (FAIL);
}
