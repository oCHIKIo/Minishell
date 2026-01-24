/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:48:27 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/24 04:48:27 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	validate_initial_token(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (tokens->type != WORD && !tokens->next)
	{
		ft_putstr_fd("xero: syntax error near unexpected token `", 2);
		ft_putstr_fd(tokens->content, 2);
		ft_putstr_fd("'\n", 2);
		exit_status(2, 1);
		return (0);
	}
	return (1);
}

static int	validate_pipe_and_check_redirection(t_token *current, t_token *prev,
		t_token_type *type)
{
	if (current->type == PIPE)
	{
		if (prev && prev->type == PIPE)
		{
			exit_status(2, 1);
			return (0);
		}
		if (!prev)
		{
			exit_status(2, 1);
			return (0);
		}
		if (!current->next)
		{
			exit_status(2, 1);
			return (0);
		}
		return (1);
	}
	if (type && (*type == REDIR_IN || *type == REDIR_OUT || *type == HEREDOC
			|| *type == REDIR_APPEND))
		return (2);
	return (1);
}

static int	validate_token_redirection_sequence(t_token *current, t_token *prev)
{
	int	current_is_redir;
	int	prev_is_redir;

	current_is_redir = validate_pipe_and_check_redirection(current, NULL,
			&current->type);
	prev_is_redir = 0;
	if (prev)
		prev_is_redir = validate_pipe_and_check_redirection(prev, NULL,
				&prev->type);
	if (current_is_redir == 2 && prev && prev_is_redir == 2)
	{
		if (current->type == prev->type)
		{
			ft_putstr_fd("xero: syntax error near unexpected token `", 2);
			ft_putstr_fd(current->content, 2);
			ft_putstr_fd("'\n", 2);
			exit_status(2, 1);
			return (0);
		}
	}
	return (1);
}

static int	validate_redirection_target(t_token *current)
{
	int	is_redir;

	is_redir = validate_pipe_and_check_redirection(current, NULL,
			&current->type);
	if (is_redir == 2)
	{
		if (!current->next)
		{
			ft_putstr_fd("xero: syntax error near unexpected token `newline'\n",
				2);
			exit_status(2, 1);
			return (0);
		}
		else if (current->next->type != WORD)
		{
			ft_putstr_fd("xero: syntax error near unexpected token `", 2);
			ft_putstr_fd(current->next->content, 2);
			ft_putstr_fd("'\n", 2);
			exit_status(2, 1);
			return (0);
		}
	}
	return (1);
}

int	validate_token_sequence(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	current = tokens;
	prev = NULL;
	if (!validate_initial_token(tokens))
		return (0);
	while (current)
	{
		if (validate_pipe_and_check_redirection(current, prev, NULL) == 0)
		{
			ft_putstr_fd("xero: syntax error near unexpected token `|'\n", 2);
			return (0);
		}
		if (!validate_token_redirection_sequence(current, prev))
			return (0);
		if (!validate_redirection_target(current))
			return (0);
		prev = current;
		current = current->next;
	}
	return (1);
}
