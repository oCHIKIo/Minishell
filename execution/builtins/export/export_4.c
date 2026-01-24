/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:07:51 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:28:58 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	bubble_sort_envp(char **envp, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				temp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static char	**create_sorted_envp_copy(char **envp, int count)
{
	char	**sorted_envp;
	int		i;

	sorted_envp = malloc(sizeof(char *) * (count + 1));
	if (!sorted_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		sorted_envp[i] = envp[i];
		i++;
	}
	sorted_envp[count] = NULL;
	bubble_sort_envp(sorted_envp, count);
	return (sorted_envp);
}

static void	print_single_env_var(char *env_entry)
{
	char	*key;
	char	*value;

	key = get_key_from_env_entry(env_entry);
	if (key)
	{
		value = ft_strchr(env_entry, '=');
		write(1, "declare -x ", 11);
		write(1, key, ft_strlen(key));
		if (value)
		{
			write(1, "=\"", 2);
			write(1, value + 1, ft_strlen(value + 1));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		free(key);
	}
}

void	print_exported_vars(char **envp)
{
	int		count;
	char	**sorted_envp;
	int		i;

	if (!envp)
		return ;
	count = 0;
	while (envp[count])
		count++;
	if (count == 0)
		return ;
	sorted_envp = create_sorted_envp_copy(envp, count);
	if (!sorted_envp)
		return ;
	i = 0;
	while (sorted_envp[i])
	{
		print_single_env_var(sorted_envp[i]);
		i++;
	}
	free(sorted_envp);
}

char	*get_key_from_env_entry(char *entry)
{
	char	*equals_pos;

	if (!entry)
		return (NULL);
	equals_pos = ft_strchr(entry, '=');
	if (equals_pos)
		return (ft_substr(entry, 0, equals_pos - entry));
	return (ft_strdup(entry));
}
