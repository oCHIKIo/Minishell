/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:08:11 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:08:13 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static char	**create_reduced_envp(char **envp, int count, int skip_index)
{
	t_crt_reduced_env	x;

	x.new_envp = malloc(sizeof(char *) * count);
	if (!x.new_envp)
		return (NULL);
	x.new_i = 0;
	x.i = 0;
	while (envp[x.i])
	{
		if (x.i != skip_index)
		{
			x.new_envp[x.new_i] = ft_strdup(envp[x.i]);
			if (!x.new_envp[x.new_i])
			{
				while (--x.new_i >= 0)
					free(x.new_envp[x.new_i]);
				free(x.new_envp);
				return (NULL);
			}
			x.new_i++;
		}
		x.i++;
	}
	x.new_envp[x.new_i] = NULL;
	return (x.new_envp);
}

static int	find_env_var_index(char **envp, char *key, int count)
{
	int		i;
	char	*current_key;

	i = 0;
	while (i < count)
	{
		current_key = get_key_from_env_entry(envp[i]);
		if (current_key && ft_strcmp(current_key, key) == 0)
		{
			free(current_key);
			return (i);
		}
		if (current_key)
			free(current_key);
		i++;
	}
	return (-1);
}

char	**remove_env_var(char **envp, char *key)
{
	int		count;
	int		target_index;
	char	**new_envp;

	if (!envp || !key)
		return (envp);
	count = 0;
	while (envp[count])
		count++;
	if (count == 0)
		return (envp);
	target_index = find_env_var_index(envp, key, count);
	if (target_index == -1)
		return (envp);
	new_envp = create_reduced_envp(envp, count, target_index);
	if (!new_envp)
		return (envp);
	free_envp_array(envp);
	return (new_envp);
}
