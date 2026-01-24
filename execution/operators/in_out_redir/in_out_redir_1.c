/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_redir_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:09:35 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:09:36 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	setup_final_input_redir(int fd, int target_fd)
{
	if (dup2(fd, target_fd) < 0)
	{
		perror("xero: dup2");
		close(fd);
		return (-1);
	}
	return (0);
}

int	setup_input_redir(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		fd = open_and_validate_input(redir->file);
		if (fd < 0)
			return (-1);
		if (!redir->next)
		{
			if (setup_final_input_redir(fd, STDIN_FILENO) < 0)
				return (-1);
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}

static int	process_output_files(t_redir *redir)
{
	int	fd;
	int	last_valid_fd;

	last_valid_fd = -1;
	while (redir)
	{
		fd = open_output_file(redir);
		if (fd < 0)
		{
			if (last_valid_fd != -1)
				close(last_valid_fd);
			return (-1);
		}
		if (last_valid_fd != -1)
			close(last_valid_fd);
		last_valid_fd = fd;
		redir = redir->next;
	}
	return (last_valid_fd);
}

static int	setup_final_output_redir(int last_valid_fd, int target_fd)
{
	if (last_valid_fd != -1)
	{
		if (dup2(last_valid_fd, target_fd) < 0)
		{
			perror("xero: dup2");
			close(last_valid_fd);
			return (-1);
		}
		close(last_valid_fd);
	}
	return (0);
}

int	setup_output_redir(t_redir *redir)
{
	int	last_valid_fd;

	last_valid_fd = process_output_files(redir);
	if (last_valid_fd < 0)
		return (-1);
	return (setup_final_output_redir(last_valid_fd, STDOUT_FILENO));
}
