/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:05:49 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:05:50 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_input_redirection(t_redir *input_redirs)
{
	if (input_redirs)
		return (setup_input_redir(input_redirs));
	return (0);
}

static int	handle_output_redirections(t_redir *output_redirs)
{
	if (output_redirs)
		return (setup_output_redir(output_redirs));
	return (0);
}

int	handle_redirections(t_cmd *cmd)
{
	int	output_result;
	int	input_result;

	output_result = 0;
	input_result = 0;
	if (cmd->input_redirs)
	{
		input_result = handle_input_redirection(cmd->input_redirs);
		if (input_result == -1)
			return (-1);
	}
	if (cmd->output_redirs)
	{
		output_result = handle_output_redirections(cmd->output_redirs);
		if (output_result == -1)
			return (-1);
	}
	return (0);
}

char	**copy_envp(char **envp)
{
	char	**new_envp;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}
