/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:09:42 by aben-dri          #+#    #+#             */
/*   Updated: 2025/07/31 11:09:44 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*check_single_path(const char *path, const char *cmd)
{
	char		*full_path;
	struct stat	st;

	full_path = build_full_path(path, cmd);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK) == 0)
	{
		if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode))
		{
			free(full_path);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
			return (full_path);
	}
	free(full_path);
	return (NULL);
}

static char	*search_in_path_dirs(char **paths, char *cmd)
{
	char	*result;
	int		i;

	i = 0;
	while (paths[i])
	{
		result = check_single_path(paths[i], cmd);
		if (result)
		{
			ft_free_array(paths);
			return (result);
		}
		++i;
	}
	ft_free_array(paths);
	return (NULL);
}

char	*find_command_in_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;

	if (!cmd || !envp)
		return (NULL);
	if (is_absolute_or_relative_path(cmd))
		return (handle_absolute_path(cmd));
	path_env = get_env_value_from_envp(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_path_dirs(paths, cmd));
}
