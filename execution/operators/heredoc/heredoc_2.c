/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:09:05 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:43:02 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*strip_quotes_from_delimiter(char *delimiter)
{
	char	*result;
	int		len;
	int		start;
	int		end;

	start = 0;
	if (!delimiter)
		return (NULL);
	len = ft_strlen(delimiter);
	end = len - 1;
	if ((delimiter[0] == '"' && delimiter[end] == '"') || (delimiter[0] == '\''
			&& delimiter[end] == '\''))
	{
		start = 1;
		end = len - 2;
	}
	result = ft_substr(delimiter, start, end - start + 1);
	return (result);
}

int	should_expand_heredoc(char *original_delimiter)
{
	int	len;

	if (!original_delimiter)
		return (1);
	len = ft_strlen(original_delimiter);
	if (len < 2)
		return (1);
	if ((original_delimiter[0] == '"' && original_delimiter[len - 1] == '"')
		|| (original_delimiter[0] == '\''
			&& original_delimiter[len - 1] == '\''))
		return (0);
	return (1);
}

static void	process_and_write_heredoc_line(char *line, int write_fd,
		int should_expand, char **envp)
{
	char	*processed_line;

	if (write_fd == -1)
		return ;
	if (should_expand)
	{
		processed_line = process_token_content(line, envp);
		if (processed_line)
		{
			write(write_fd, processed_line, ft_strlen(processed_line));
			free(processed_line);
		}
		else
			write(write_fd, line, ft_strlen(line));
	}
	else
		write(write_fd, line, ft_strlen(line));
	write(write_fd, "\n", 1);
}

int	read_heredoc_child(int write_fd, char *clean_delimiter, int should_expand,
		char **envp)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf(
				"xero: warning: here-document delimited by end-of-file "
				"(wanted `%s')\n",
				clean_delimiter
				);
			break ;
		}
		if (!ft_strcmp(line, clean_delimiter))
		{
			free(line);
			break ;
		}
		process_and_write_heredoc_line(line, write_fd, should_expand, envp);
		free(line);
	}
	return (0);
}
