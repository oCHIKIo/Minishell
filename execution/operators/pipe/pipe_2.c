/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:10:09 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:33:51 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	wait_all(pid_t last_pid)
{
	int		status;
	int		code;
	pid_t	waited_pid;

	code = 0;
	waited_pid = waitpid(-1, &status, 0);
	while (waited_pid > 0)
	{
		if (waited_pid == last_pid)
			code = handle_exit_status(status);
		waited_pid = waitpid(-1, &status, 0);
	}
	return (code);
}

int	handle_exit_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			return (130);
		}
		else if (sig == SIGQUIT)
		{
			write(STDOUT_FILENO, "Quit: 3\n", 8);
			return (131);
		}
		else
			return (128 + sig);
	}
	return (0);
}

void	setup_parent(t_exec_state *st)
{
	if (st->in_fd != STDIN_FILENO)
		close(st->in_fd);
	if (st->current->next)
	{
		close(st->fd[1]);
		st->in_fd = st->fd[0];
	}
	if (!st->current->next)
		st->last_pid = st->pid;
	st->current = st->current->next;
}

void	setup_input_redirection(t_exec_state *st)
{
	if (st->in_fd != STDIN_FILENO)
	{
		dup2(st->in_fd, STDIN_FILENO);
		close(st->in_fd);
	}
}
