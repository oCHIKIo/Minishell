/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:48:05 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/31 10:49:38 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal = 0;

int	get_signal(void)
{
	return (g_signal);
}

void	set_signal(int sig)
{
	g_signal = sig;
}

static int	handle_empty_input(char *input, int *current_exit_status)
{
	if (ft_strlen(input) == 0)
	{
		if (get_signal() == SIGINT)
		{
			*current_exit_status = exit_status(0, 0);
			set_signal(0);
		}
		free(input);
		return (1);
	}
	return (0);
}

static void	main_shell_loop(char **my_envp, int *current_exit_status)
{
	char	*input;

	setup_signals();
	while (1)
	{
		input = read_input();
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			rl_clear_history();
			rl_cleanup_after_signal();
			cleanup_and_exit(exit_status(0, 0), &my_envp);
		}
		if (handle_empty_input(input, current_exit_status))
			continue ;
		if (process_input_line(input, &my_envp, current_exit_status) == 1)
			continue ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**my_envp;
	int		current_exit_status;

	current_exit_status = 0;
	(void)argc;
	(void)argv;
	my_envp = initialize_environment(envp);
	if (!my_envp)
		return (1);
	main_shell_loop(my_envp, &current_exit_status);
	free_envp(my_envp);
	return (current_exit_status);
}
