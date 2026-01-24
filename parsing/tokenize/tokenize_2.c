/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:48:00 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/28 13:24:32 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_quoted_part(char *input, int *i)
{
	char	*quoted_part;
	int		start;
	char	quote;

	quote = input[*i];
	start = *i;
	*i += 1;
	while (input[*i] && input[*i] != quote)
	{
		if (input[*i] == '\\' && input[*i + 1] == quote)
			*i += 2;
		else
			*i += 1;
	}
	if (input[*i])
		*i += 1;
	quoted_part = ft_substr(input, start, *i - start);
	return (quoted_part);
}

static char	*extract_main_word_parts(char *input, int *i)
{
	t_extract	e;

	e.word = ft_strdup("");
	while (input[*i] && input[*i] != ' ' && input[*i] != '>' && input[*i] != '<'
		&& input[*i] != '|')
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			e.part = extract_quoted_part(input, i);
		}
		else
		{
			e.start = *i;
			while (input[*i] && input[*i] != ' ' && input[*i] != '\''
				&& input[*i] != '"' && input[*i] != '>' && input[*i] != '<'
				&& input[*i] != '|')
				*i += 1;
			e.part = ft_substr(input, e.start, *i - e.start);
		}
		e.temp = e.word;
		e.word = ft_strjoin(e.word, e.part);
		free(e.temp);
		free(e.part);
	}
	return (e.word);
}

static char	*handle_redirection_operators(char *input, int *i, char *word)
{
	(void)input;
	(void)i;
	return (word);
}

char	*extract_word(char *input, int *i)
{
	t_extract	e;

	e.word = extract_main_word_parts(input, i);
	e.word = handle_redirection_operators(input, i, e.word);
	return (e.word);
}
