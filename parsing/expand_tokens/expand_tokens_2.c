/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:46:19 by bchiki            #+#    #+#             */
/*   Updated: 2025/08/01 20:14:40 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_tilde_in_token(char *content, char **envp)
{
	(void)envp;
	return (ft_strdup(content));
}

static int	handle_special_escapes(char *content, t_remove_quotes *x)
{
	if (content[x->i + 1] == 'n')
	{
		x->result[x->j++] = '\n';
		x->i += 2;
		return (1);
	}
	else if (content[x->i + 1] == 't')
	{
		x->result[x->j++] = '\t';
		x->i += 2;
		return (1);
	}
	else if (content[x->i + 1] == 'r')
	{
		x->result[x->j++] = '\r';
		x->i += 2;
		return (1);
	}
	else if (content[x->i + 1] == '\\')
	{
		x->result[x->j++] = '\\';
		x->i += 2;
		return (1);
	}
	return (0);
}

int	process_escape_sequence(char *content, t_remove_quotes *x)
{
	if (content[x->i] == '\\' && x->quote == 0)
	{
		if (handle_special_escapes(content, x))
			return (1);
		else
		{
			x->result[x->j++] = content[x->i++];
			return (1);
		}
	}
	return (0);
}

static void	process_quote_character(char *content, t_remove_quotes *x)
{
	if ((content[x->i] == '\'' || content[x->i] == '"') && x->quote == 0)
	{
		x->quote = content[x->i];
		x->i++;
	}
	else if (content[x->i] == x->quote)
	{
		x->quote = 0;
		x->i++;
	}
	else if (process_escape_sequence(content, x))
		return ;
	else
		x->result[x->j++] = content[x->i++];
}

char	*remove_quotes(char *content)
{
	t_remove_quotes	x;

	x.i = 0;
	x.j = 0;
	x.quote = 0;
	x.len = ft_strlen(content);
	x.result = malloc(x.len + 1);
	if (!x.result)
		return (NULL);
	while (content[x.i])
	{
		process_quote_character(content, &x);
	}
	x.result[x.j] = '\0';
	return (x.result);
}
