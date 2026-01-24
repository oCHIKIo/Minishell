/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:11:32 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/07 12:11:33 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin_with_newline(char *s1, char *s2)
{
	t_join_vars	v;

	if (!s1 || !s2)
		return (NULL);
	v.len1 = ft_strlen(s1);
	v.len2 = ft_strlen(s2);
	v.i = 0;
	v.result = malloc(v.len1 + v.len2 + 2);
	if (!v.result)
		return (NULL);
	while (v.i < v.len1)
	{
		v.result[v.i] = s1[v.i];
		v.i++;
	}
	v.result[v.i++] = '\n';
	while (v.i - v.len1 - 1 < v.len2)
	{
		v.result[v.i] = s2[v.i - v.len1 - 1];
		v.i++;
	}
	v.result[v.i] = '\0';
	free(s1);
	return (v.result);
}

int	validate_quote_syntax(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		i++;
	}
	if (quote != 0)
		return (0);
	return (1);
}

char	unclosed_quotes(char *str)
{
	return (validate_quote_syntax(str));
}

char	*trim_trailing_whitespace(char *str)
{
	char	*end;
	int		len;
	char	*result;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len == 0)
		return (ft_strdup(str));
	end = str + len - 1;
	while (end >= str && (*end == ' ' || *end == '\t' || *end == '\n'
			|| *end == '\r'))
		end--;
	len = end - str + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strncpy(result, str, len);
	result[len] = '\0';
	return (result);
}
