/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:12:47 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/31 11:12:49 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	process_quotes_loop(t_rmv_qot_from_arg *r, char *content)
{
	t_escape_handler	e;

	while (content[r->i])
	{
		if (handle_quote_start(content[r->i], &r->quote))
			r->i++;
		else if (handle_quote_end(content[r->i], &r->quote))
			r->i++;
		else
		{
			e.content = content;
			e.i = r->i;
			e.quote = r->quote;
			e.result = r->result;
			e.j = &r->j;
			r->skip = handle_escape_sequence(&e);
			if (r->skip > 0)
				r->i += r->skip;
			else
				r->result[r->j++] = content[r->i++];
		}
	}
}

char	*remove_quotes_from_arg(char *content)
{
	t_rmv_qot_from_arg	r;

	r.i = 0;
	r.j = 0;
	r.skip = 0;
	r.quote = 0;
	r.len = ft_strlen(content);
	r.result = malloc(r.len + 1);
	if (!r.result)
		return (NULL);
	process_quotes_loop(&r, content);
	r.result[r.j] = '\0';
	return (r.result);
}

void	add_arg(t_cmd *cmd, char *content)
{
	t_arg	*new_arg;
	t_arg	*current;
	char	*clean_content;

	clean_content = remove_quotes_from_arg(content);
	if (!clean_content)
		return ;
	if (ft_strlen(clean_content) == 0)
	{
		free(clean_content);
		return ;
	}
	new_arg = create_arg(clean_content);
	free(clean_content);
	if (!new_arg)
		return ;
	if (!cmd->args)
		cmd->args = new_arg;
	else
	{
		current = cmd->args;
		while (current->next)
			current = current->next;
		current->next = new_arg;
	}
}

void	add_input_redir(t_cmd *cmd, char *file)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
	{
		free(new_redir);
		return ;
	}
	new_redir->append_mode = 0;
	new_redir->fd = STDIN_FILENO;
	new_redir->next = NULL;
	if (!cmd->input_redirs)
		cmd->input_redirs = new_redir;
	else
	{
		current = cmd->input_redirs;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

int	handle_redirect(t_cmd *cmd, t_token *token, t_token **current)
{
	int	result;

	if (token->type == REDIR_IN)
		result = handle_input_redirect(cmd, current);
	else if (token->type == REDIR_OUT)
		result = handle_output_redirect(cmd, current, 0);
	else if (token->type == REDIR_APPEND)
		result = handle_output_redirect(cmd, current, 1);
	else if (token->type == HEREDOC)
		result = handle_heredoc_redirect(cmd, current);
	else
		return (-1);
	if (result == 0)
		*current = (*current)->next;
	return (result);
}
