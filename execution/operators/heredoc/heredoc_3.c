/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:09:10 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 12:17:35 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	cleanup_and_return_error(t_heredoc_fork_params *params)
{
	if (params->write_fd != -1)
	{
		close(params->write_fd);
		unlink(params->temp_file);
		free(params->temp_file);
	}
	free(params->clean_delimiter);
	return (-1);
}

int	handle_fork_result_v2(pid_t pid, t_heredoc_fork_params *params)
{
	if (pid == 0)
		handle_heredoc_child(params->write_fd, params->clean_delimiter,
			params->should_expand, params->envp);
	else if (pid > 0)
	{
		if (handle_heredoc_parent(pid, params->write_fd, params->temp_file,
				params->clean_delimiter) == -1)
			return (-1);
		if (params->write_fd != -1)
		{
			close(params->write_fd);
			params->cmd->heredoc_file = params->temp_file;
		}
	}
	else
		return (cleanup_and_return_error(params));
	return (0);
}

static int	process_single_heredoc_node(t_heredoc *current,
		t_heredoc *last_heredoc, t_cmd *cmd, char **envp)
{
	t_prcs_sgl_hrdc_node	node;

	node.setup_params.current = current;
	node.setup_params.last_heredoc = last_heredoc;
	node.setup_params.clean_delimiter = &node.clean_delimiter;
	node.setup_params.should_expand = &node.should_expand;
	node.setup_params.write_fd = &node.write_fd;
	node.setup_params.temp_file = &node.temp_file;
	if (setup_heredoc_processing(&node.setup_params) == -1)
		return (-1);
	node.fork_params.clean_delimiter = node.clean_delimiter;
	node.fork_params.should_expand = node.should_expand;
	node.fork_params.write_fd = node.write_fd;
	node.fork_params.temp_file = node.temp_file;
	node.fork_params.cmd = cmd;
	node.fork_params.envp = envp;
	return (execute_heredoc_fork(&node.fork_params));
}

static void	setup_heredoc_vars(t_cmd *cmd, t_heredoc **current,
		t_heredoc **last_heredoc, void (**old_handler)(int))
{
	*current = cmd->heredocs;
	*last_heredoc = find_last_heredoc_node(*current);
	*current = cmd->heredocs;
	*old_handler = signal(SIGINT, SIG_IGN);
}

int	process_all_heredocs(t_cmd *commands, char **envp)
{
	t_heredoc_all_vars	vars;

	vars.cmd = commands;
	while (vars.cmd)
	{
		if (vars.cmd->heredocs)
		{
			setup_heredoc_vars(vars.cmd, &vars.current, &vars.last_heredoc,
				&vars.old_handler);
			while (vars.current)
			{
				if (process_single_heredoc_node(vars.current, vars.last_heredoc,
						vars.cmd, envp) == -1)
				{
					signal(SIGINT, vars.old_handler);
					return (-1);
				}
				vars.current = vars.current->next;
			}
			signal(SIGINT, vars.old_handler);
		}
		vars.cmd = vars.cmd->next;
	}
	return (0);
}
