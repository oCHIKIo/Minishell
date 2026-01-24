/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:45:49 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/28 16:19:40 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_input_redirect(t_cmd *cmd, t_token **current)
{
	char	*clean_filename;

	if (!(*current)->next)
		return (-1);
	clean_filename = remove_quotes_from_arg((*current)->next->content);
	add_input_redir(cmd, clean_filename);
	free(clean_filename);
	return (0);
}

int	handle_output_redirect(t_cmd *cmd, t_token **current, int append_mode)
{
	char	*clean_filename;

	if (!(*current)->next)
		return (-1);
	clean_filename = remove_quotes_from_arg((*current)->next->content);
	add_output_redir(cmd, clean_filename, append_mode);
	free(clean_filename);
	return (0);
}

int	handle_heredoc_redirect(t_cmd *cmd, t_token **current)
{
	if (!(*current)->next)
		return (-1);
	add_heredoc(cmd, (*current)->next->content);
	return (0);
}
