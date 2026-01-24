/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:48:05 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/24 04:48:07 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_numbered_redirect_op(char *content)
{
	int	i;

	i = 0;
	if (!ft_isdigit(content[i]))
		return (0);
	while (ft_isdigit(content[i]))
		i++;
	if (content[i] == '>' || content[i] == '<')
		return (1);
	return (0);
}

t_token_type	get_token_type(char *content)
{
	if (ft_strcmp(content, "|") == 0)
		return (PIPE);
	if (ft_strcmp(content, ">") == 0)
		return (REDIR_OUT);
	if (ft_strcmp(content, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(content, ">>") == 0)
		return (REDIR_APPEND);
	if (ft_strcmp(content, "<<") == 0)
		return (HEREDOC);
	if (is_numbered_redirect_op(content))
	{
		if (ft_strstr(content, ">>"))
			return (REDIR_APPEND);
		else if (ft_strstr(content, "<<"))
			return (HEREDOC);
		else if (ft_strstr(content, ">"))
			return (REDIR_OUT);
		else if (ft_strstr(content, "<"))
			return (REDIR_IN);
	}
	return (WORD);
}

t_token	*create_token(char *content, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = content;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

char	*trim_whitespace(char *str)
{
	char	*end;
	char	*start;
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	start = str;
	while (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r')
		start++;
	if (*start == 0)
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'
			|| *end == '\r'))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strncpy(result, start, len);
	result[len] = '\0';
	return (result);
}
