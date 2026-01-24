/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:07:41 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:31:15 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	**create_new_envp_array(char **envp, int count)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[count] = NULL;
	new_envp[count + 1] = NULL;
	return (new_envp);
}

void	free_envp_array(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	*create_env_entry(char *key, char *value)
{
	char	*entry;
	int		key_len;
	int		value_len;

	if (!key)
		return (NULL);
	key_len = ft_strlen(key);
	if (!value)
		return (ft_strdup(key));
	value_len = ft_strlen(value);
	entry = malloc(key_len + value_len + 2);
	if (!entry)
		return (NULL);
	ft_strcpy(entry, key);
	ft_strcat(entry, "=");
	ft_strcat(entry, value);
	return (entry);
}

char	*append_to_existing_value(char *existing_entry, char *key,
		char *append_value)
{
	t_apnd_to_exst_vlu	vars;

	if (!existing_entry || !key || !append_value)
		return (NULL);
	vars.equals_pos = ft_strchr(existing_entry, '=');
	if (!vars.equals_pos)
		return (create_env_entry(key, append_value));
	vars.old_value = vars.equals_pos + 1;
	vars.old_len = ft_strlen(vars.old_value);
	vars.append_len = ft_strlen(append_value);
	vars.new_value = malloc(vars.old_len + vars.append_len + 1);
	if (!vars.new_value)
		return (NULL);
	ft_strcpy(vars.new_value, vars.old_value);
	ft_strcat(vars.new_value, append_value);
	vars.new_entry = create_env_entry(key, vars.new_value);
	free(vars.new_value);
	return (vars.new_entry);
}

char	**add_env_var(char **envp, char *key, char *value)
{
	char	*key_copy;
	int		is_append;
	char	**result;
	int		key_len;

	if (!envp || !key)
		return (NULL);
	key_copy = ft_strdup(key);
	if (!key_copy)
		return (NULL);
	is_append = 0;
	key_len = ft_strlen(key_copy);
	if (key_len > 0 && key_copy[key_len - 1] == '+')
	{
		is_append = 1;
		key_copy[key_len - 1] = '\0';
	}
	result = add_or_update_env_var(envp, key_copy, value, is_append);
	free(key_copy);
	return (result);
}
