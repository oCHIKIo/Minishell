/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:45:59 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/28 17:37:24 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_escape_in_double_quotes(char *content, int i, char *result, int *j)
{
	if (content[i] == '\\' && (content[i + 1] == '"' || content[i + 1] == '\\'
			|| content[i + 1] == '$'))
	{
		result[(*j)++] = content[i + 1];
		return (2);
	}
	return (0);
}

int	handle_escape_outside_quotes(char *content, int i, char *result, int *j)
{
	if (content[i] == '\\')
	{
		if (content[i + 1] == 'n')
		{
			result[(*j)++] = '\n';
			return (2);
		}
		else if (content[i + 1] == 't')
		{
			result[(*j)++] = '\t';
			return (2);
		}
		else if (content[i + 1] == 'r')
		{
			result[(*j)++] = '\r';
			return (2);
		}
		else if (content[i + 1] == '\\')
		{
			result[(*j)++] = '\\';
			return (2);
		}
	}
	return (0);
}

int	handle_escape_sequence(t_escape_handler *params)
{
	if (params->quote == '"')
		return (handle_escape_in_double_quotes(params->content, params->i,
				params->result, params->j));
	else if (params->quote == 0)
		return (handle_escape_outside_quotes(params->content, params->i,
				params->result, params->j));
	return (0);
}

void	add_output_redir(t_cmd *cmd, char *file, int append_mode)
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
	new_redir->append_mode = append_mode;
	new_redir->fd = STDOUT_FILENO;
	new_redir->next = NULL;
	if (!cmd->output_redirs)
		cmd->output_redirs = new_redir;
	else
	{
		current = cmd->output_redirs;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}
