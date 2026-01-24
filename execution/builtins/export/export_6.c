/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:31:19 by aben-dri          #+#    #+#             */
/*   Updated: 2025/08/02 15:53:11 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	is_valid_identifier(char *str)
{
	int		i;
	char	*equals_pos;
	char	*plus_pos;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	equals_pos = ft_strchr(str, '=');
	i = 1;
	while (str[i] && (!equals_pos || &str[i] < equals_pos))
	{
		if (str[i] == '+' && equals_pos && &str[i + 1] == equals_pos)
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] == '+' && equals_pos && &str[i + 1] == equals_pos)
	{
		plus_pos = &str[i];
		if (plus_pos + 1 != equals_pos)
			return (0);
	}
	return (1);
}

static int	parse_export_pair(char *arg, char **out_key, char **out_value)
{
	char	*key;
	char	*value;

	if (!arg)
		return (1);
	if (!is_valid_identifier(arg))
		return (print_export_error(arg));
	if (parse_export_arg(arg, &key, &value) == 1)
	{
		write(2, "xero: export: memory allocation failed\n", 39);
		return (1);
	}
	*out_key = key;
	*out_value = value;
	return (0);
}

static int	insert_env_var(char ***envp, char *key, char *raw_value)
{
	char	*clean_value;
	char	**new_env;

	clean_value = NULL;
	if (raw_value)
	{
		clean_value = remove_export_quotes(raw_value);
		if (!clean_value)
		{
			write(2, "xero: export: memory allocation failed\n", 39);
			free(key);
			return (1);
		}
		raw_value = clean_value;
	}
	new_env = add_env_var(*envp, key, raw_value);
	free(key);
	free(clean_value);
	if (!new_env)
	{
		write(2, "xero: export: memory allocation failed\n", 39);
		return (1);
	}
	*envp = new_env;
	return (0);
}

int	handle_single_export_arg(char *arg, char ***envp)
{
	char	*key;
	char	*value;

	if (!arg || !envp || !*envp)
		return (1);
	if (parse_export_pair(arg, &key, &value) != 0)
		return (1);
	return (insert_env_var(envp, key, value));
}
