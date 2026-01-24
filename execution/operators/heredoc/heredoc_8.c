/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:44:38 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 12:17:25 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	setup_heredoc_processing(t_heredoc_setup_params *params)
{
	*(params->clean_delimiter)
		= strip_quotes_from_delimiter(params->current->delimiter);
	if (!*(params->clean_delimiter))
		return (-1);
	*(params->should_expand)
		= should_expand_heredoc(params->current->delimiter);
	*(params->write_fd) = -1;
	*(params->temp_file) = NULL;
	if (params->current == params->last_heredoc)
	{
		if (create_temp_heredoc_file(params->temp_file, params->write_fd) == -1)
		{
			free(*(params->clean_delimiter));
			return (-1);
		}
	}
	return (0);
}

int	execute_heredoc_fork(t_heredoc_fork_params *params)
{
	pid_t	pid;

	pid = fork();
	return (handle_fork_result_v2(pid, params));
}
