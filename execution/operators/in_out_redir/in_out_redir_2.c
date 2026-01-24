/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_redir_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:09:38 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:09:40 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_input_error(char *filename)
{
	ft_putstr_fd("xero: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else if (errno == ENOENT)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else
		perror("");
}

void	print_output_error(char *filename)
{
	ft_putstr_fd("xero: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else
		perror("");
}

int	open_output_file(t_redir *redir)
{
	int	fd;

	if (redir->append_mode)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		print_output_error(redir->file);
	return (fd);
}

int	open_and_validate_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_input_error(filename);
		return (-1);
	}
	return (fd);
}
