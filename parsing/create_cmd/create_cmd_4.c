/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:10:06 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/07 12:10:07 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_cmd	*init_cmd_struct(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->input_redirs = NULL;
	cmd->output_redirs = NULL;
	cmd->heredocs = NULL;
	cmd->heredoc_file = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	process_token(t_cmd *cmd, t_token **current)
{
	if ((*current)->type == WORD)
	{
		add_arg(cmd, (*current)->content);
		return (0);
	}
	else if ((*current)->type == REDIR_IN || (*current)->type == REDIR_OUT
		|| (*current)->type == REDIR_APPEND || (*current)->type == HEREDOC)
	{
		if ((*current)->next)
		{
			if (handle_redirect(cmd, *current, current) == -1)
				return (-1);
		}
		return (0);
	}
	return (0);
}

t_cmd	*create_single_cmd(t_token *start, t_token *end)
{
	t_cmd	*cmd;
	t_token	*current;

	cmd = init_cmd_struct();
	if (!cmd)
		return (NULL);
	current = start;
	while (current && current != end)
	{
		if (process_token(cmd, &current) == -1)
		{
			free_cmd(cmd);
			return (NULL);
		}
		current = current->next;
	}
	return (cmd);
}

t_cmd	*process_pipe_commands(t_token *tokens, t_cmd **commands,
		t_token **last_start)
{
	t_process_pipe_cmd	p;
	t_cmd				*new_cmd;

	p.current_cmd = NULL;
	p.start = tokens;
	p.current = tokens;
	*last_start = tokens;
	while (p.current)
	{
		if (p.current->type == PIPE)
		{
			new_cmd = create_single_cmd(p.start, p.current);
			if (!new_cmd)
				return (NULL);
			if (!*commands)
				*commands = new_cmd;
			else
				p.current_cmd->next = new_cmd;
			p.current_cmd = new_cmd;
			p.start = p.current->next;
			*last_start = p.start;
		}
		p.current = p.current->next;
	}
	return (p.current_cmd);
}

t_cmd	*create_cmd(t_token *tokens)
{
	t_cmd	*commands;
	t_cmd	*current_cmd;
	t_token	*start;
	t_cmd	*new_cmd;

	current_cmd = NULL;
	commands = NULL;
	if (!tokens)
		return (NULL);
	current_cmd = process_pipe_commands(tokens, &commands, &start);
	new_cmd = create_single_cmd(start, NULL);
	if (!new_cmd)
	{
		free_cmd(commands);
		return (NULL);
	}
	if (!commands)
		commands = new_cmd;
	else
		current_cmd->next = new_cmd;
	return (commands);
}
