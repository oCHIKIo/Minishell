/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:09:27 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:09:28 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_heredoc	*find_last_heredoc_node(t_heredoc *heredocs)
{
	t_heredoc	*last_heredoc;

	last_heredoc = heredocs;
	while (last_heredoc->next)
		last_heredoc = last_heredoc->next;
	return (last_heredoc);
}

int	append_pid_to_name(char *temp_name, int len, pid_t pid)
{
	char	pid_str[20];
	int		pid_len;
	int		i;

	pid_len = convert_pid_to_string(pid_str, pid);
	i = 0;
	while (i < pid_len && len < 250)
	{
		temp_name[len] = pid_str[i];
		len++;
		i++;
	}
	return (len);
}

int	append_counter_to_name(char *temp_name, int len, int counter)
{
	char	counter_str[20];
	int		counter_len;
	int		i;

	counter_len = convert_counter_to_string(counter_str, counter);
	i = 0;
	while (i < counter_len && len < 255)
	{
		temp_name[len] = counter_str[i];
		len++;
		i++;
	}
	return (len);
}

int	convert_pid_to_string(char *pid_str, pid_t pid)
{
	int		pid_len;
	pid_t	temp_pid;
	char	temp_digits[20];
	int		temp_len;

	pid_len = 0;
	temp_pid = pid;
	if (temp_pid == 0)
		pid_str[pid_len++] = '0';
	else
	{
		temp_len = 0;
		while (temp_pid > 0)
		{
			temp_digits[temp_len++] = '0' + (temp_pid % 10);
			temp_pid /= 10;
		}
		while (temp_len > 0)
			pid_str[pid_len++] = temp_digits[--temp_len];
	}
	return (pid_len);
}

int	convert_counter_to_string(char *counter_str, int counter)
{
	int		counter_len;
	int		temp_counter;
	char	temp_digits[20];
	int		temp_len;

	counter_len = 0;
	temp_counter = counter;
	if (temp_counter == 0)
		counter_str[counter_len++] = '0';
	else
	{
		temp_len = 0;
		while (temp_counter > 0)
		{
			temp_digits[temp_len++] = '0' + (temp_counter % 10);
			temp_counter /= 10;
		}
		while (temp_len > 0)
			counter_str[counter_len++] = temp_digits[--temp_len];
	}
	return (counter_len);
}
