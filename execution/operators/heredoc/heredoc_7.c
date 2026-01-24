/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:09:30 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:09:32 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	create_temp_heredoc_file(char **temp_file, int *write_fd)
{
	char		temp_name[256];
	static int	counter = 0;
	pid_t		pid;

	pid = getpid();
	counter++;
	if (build_temp_filename(temp_name, pid, counter) == -1)
		return (-1);
	*write_fd = open(temp_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*write_fd == -1)
	{
		perror("xero: temp file");
		return (-1);
	}
	*temp_file = ft_strdup(temp_name);
	if (!*temp_file)
	{
		close(*write_fd);
		unlink(temp_name);
		return (-1);
	}
	return (0);
}

int	handle_heredoc_child(int write_fd, char *clean_delimiter, int should_expand,
		char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	read_heredoc_child(write_fd, clean_delimiter, should_expand, envp);
	if (write_fd != -1)
		close(write_fd);
	free(clean_delimiter);
	exit(0);
}

int	handle_heredoc_parent(pid_t pid, int write_fd, char *temp_file,
		char *clean_delimiter)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		if (write_fd != -1)
		{
			close(write_fd);
			unlink(temp_file);
			free(temp_file);
		}
		write(STDOUT_FILENO, "\n", 1);
		exit_status(130, 1);
		set_signal(0);
		free(clean_delimiter);
		return (-1);
	}
	free(clean_delimiter);
	return (0);
}

static int	build_base_path(char *temp_name, char *tmp_dir, char *prefix)
{
	int	len;

	len = 0;
	while (tmp_dir[len] && len < 200)
	{
		temp_name[len] = tmp_dir[len];
		len++;
	}
	while (*prefix && len < 240)
	{
		temp_name[len] = *prefix;
		len++;
		prefix++;
	}
	return (len);
}

int	build_temp_filename(char *temp_name, pid_t pid, int counter)
{
	char	*tmp_dir;
	char	*prefix;
	int		len;

	tmp_dir = getenv("TMPDIR");
	if (!tmp_dir)
		tmp_dir = "/tmp";
	prefix = "/minishell_heredoc_";
	len = build_base_path(temp_name, tmp_dir, prefix);
	len = append_pid_to_name(temp_name, len, pid);
	if (len < 251)
		temp_name[len++] = '_';
	len = append_counter_to_name(temp_name, len, counter);
	temp_name[len] = '\0';
	if (len >= 255)
		return (-1);
	return (0);
}
