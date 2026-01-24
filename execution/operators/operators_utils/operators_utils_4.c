/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:09:54 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:09:56 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_args(t_arg *args)
{
	int		count;
	t_arg	*current;

	count = 0;
	current = args;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	free_partial_array(char **array, int up_to_index)
{
	while (up_to_index > 0)
	{
		up_to_index--;
		free(array[up_to_index]);
	}
	free(array);
}

static char	**allocate_args_array(int count)
{
	return (malloc(sizeof(char *) * (count + 1)));
}

static int	fill_args_array(char **array, t_arg *args)
{
	t_arg	*current;
	int		i;

	current = args;
	i = 0;
	while (current)
	{
		array[i] = ft_strdup(current->content);
		if (!array[i])
		{
			free_partial_array(array, i);
			return (0);
		}
		i++;
		current = current->next;
	}
	array[i] = NULL;
	return (1);
}

char	**convert_args_to_array(t_arg *args)
{
	int		count;
	char	**array;

	count = count_args(args);
	array = allocate_args_array(count);
	if (!array)
		return (NULL);
	if (!fill_args_array(array, args))
		return (NULL);
	return (array);
}
