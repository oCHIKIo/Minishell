/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:29:20 by aben-dri          #+#    #+#             */
/*   Updated: 2025/08/07 20:29:22 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	setup_pipe_output(t_exec_state *st)
{
	if (st->current->next)
	{
		close(st->fd[0]);
		dup2(st->fd[1], STDOUT_FILENO);
		close(st->fd[1]);
	}
}

static void	setup_heredoc(t_exec_state *st)
{
	int	fd;

	if (st->current->heredoc_file)
	{
		fd = open(st->current->heredoc_file, O_RDONLY);
		if (fd == -1)
		{
			perror("xero: heredoc");
			exit(1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("xero: dup2");
			exit(1);
		}
		close(fd);
	}
}

static void	setup_child(t_exec_state *st, char **envp)
{
	int		redir_result;
	char	**args;

	setup_input_redirection(st);
	setup_pipe_output(st);
	setup_heredoc(st);
	redir_result = handle_redirections(st->current);
	args = convert_args_to_array(st->current->args);
	validate_and_execute(args, redir_result, envp, st->current);
}

int	execute_pipeline(t_cmd *commands, char **envp, int current_exit_status)
{
	t_exec_state	st;

	st.in_fd = STDIN_FILENO;
	st.current = commands;
	st.exit_code = current_exit_status;
	st.last_pid = -1;
	while (st.current)
	{
		if (st.current->next && pipe(st.fd) == -1)
			return (1);
		st.pid = fork();
		if (st.pid == 0)
			setup_child(&st, envp);
		else
			setup_parent(&st);
	}
	st.exit_code = wait_all(st.last_pid);
	return (st.exit_code);
}
