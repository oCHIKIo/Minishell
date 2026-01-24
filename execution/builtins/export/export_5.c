/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:48:37 by aben-dri          #+#    #+#             */
/*   Updated: 2025/08/02 15:51:57 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	print_export_error(char *arg)
{
	write(2, "xero: export: `", 15);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	parse_export_arg(char *arg, char **key, char **value)
{
	char	*equals_pos;

	equals_pos = ft_strchr(arg, '=');
	if (equals_pos)
	{
		*key = ft_substr(arg, 0, equals_pos - arg);
		*value = equals_pos + 1;
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
	if (*key)
		return (0);
	else
		return (1);
}

static bool	handle_quote_delim(const char *s, int *i, char *quote)
{
	if ((s[*i] == '\'' || s[*i] == '\"') && *quote == 0)
	{
		*quote = s[*i];
		(*i)++;
		return (true);
	}
	if (s[*i] == *quote)
	{
		*quote = 0;
		(*i)++;
		return (true);
	}
	return (false);
}

static bool	handle_backslash_escape(const char *s, int *i, int *j, char *buf)
{
	if (s[*i] == '\\' && (s[*i + 1] == '\"' || s[*i + 1] == '\\'
			|| s[*i + 1] == '$'))
	{
		buf[(*j)++] = s[*i + 1];
		*i += 2;
		return (true);
	}
	return (false);
}

char	*remove_export_quotes(char *str)
{
	int		len;
	char	*res;
	int		i;
	int		j;
	char	quote;

	len = strlen(str);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (handle_quote_delim(str, &i, &quote))
			continue ;
		if (quote == '\"' && handle_backslash_escape(str, &i, &j, res))
			continue ;
		res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}
