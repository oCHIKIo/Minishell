/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:07:45 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:29:02 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static char	*create_new_entry_for_update(char *key, char *value, int is_append,
		char *existing_entry)
{
	char	*new_entry;

	if (value)
	{
		if (is_append)
			new_entry = append_to_existing_value(existing_entry, key, value);
		else
			new_entry = create_env_entry(key, value);
	}
	else
	{
		if (existing_entry && ft_strchr(existing_entry, '='))
			new_entry = ft_strdup(existing_entry);
		else
			new_entry = ft_strdup(key);
	}
	return (new_entry);
}

static char	**update_existing_var(t_update_existing_var *update_data)
{
	char	*new_entry;

	new_entry = create_new_entry_for_update(update_data->key,
			update_data->value, update_data->is_append,
			update_data->envp[update_data->index]);
	if (!new_entry)
		return (NULL);
	free(update_data->envp[update_data->index]);
	update_data->envp[update_data->index] = new_entry;
	return (update_data->envp);
}

static char	**add_new_var(char **envp, char *key, char *value, int count)
{
	char	**new_envp;
	char	*new_entry;

	new_envp = create_new_envp_array(envp, count);
	if (!new_envp)
		return (NULL);
	if (value)
		new_entry = create_env_entry(key, value);
	else
		new_entry = ft_strdup(key);
	if (!new_entry)
	{
		free_envp_array(new_envp);
		return (NULL);
	}
	new_envp[count] = new_entry;
	free_envp_array(envp);
	return (new_envp);
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

char	**add_or_update_env_var(char **envp, char *key, char *value,
		int is_append)
{
	int						count;
	int						index;
	t_update_existing_var	update_data;

	if (!envp || !key)
		return (NULL);
	count = 0;
	while (envp[count])
		count++;
	index = find_env_var_index(envp, key, count);
	if (index != -1)
	{
		update_data.envp = envp;
		update_data.key = key;
		update_data.value = value;
		update_data.is_append = is_append;
		update_data.index = index;
		return (update_existing_var(&update_data));
	}
	return (add_new_var(envp, key, value, count));
}
