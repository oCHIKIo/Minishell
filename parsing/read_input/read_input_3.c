/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:47:25 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/27 16:53:07 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*create_prompt(void)
{
	char	*prompt;
	char	*username;

	username = getenv("USER");
	if (!username)
		username = "shadow";
	prompt = malloc(ft_strlen(username) + ft_strlen(XERO_SUFFIX) + 1);
	if (!prompt)
		return (NULL);
	ft_strcpy(prompt, username);
	ft_strcat(prompt, "@xero⚔ ");
	return (prompt);
}

char	*get_user_input(void)
{
	char	*input;
	char	*prompt;

	prompt = create_prompt();
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	free(prompt);
	if (!input)
		return (NULL);
	add_history(input);
	return (input);
}

int	validate_input_syntax(char *input)
{
	if (validate_quote_syntax(input) == 0)
	{
		write(2, "xero: syntax error: unclosed quotes\n", 37);
		exit_status(2, 1);
		return (0);
	}
	return (1);
}

int	skip_quoted_section(char *input, int *i)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i])
		(*i)++;
	return (1);
}

int	check_parentheses(char *input, int i)
{
	if (input[i] == '(' && input[i + 1] == '(')
	{
		write(2,
			"xero: unsupported syntax: arithmetic evaluation not handled\n",
			61);
		exit_status(2, 1);
		return (0);
	}
	else if (input[i] == '(' || input[i] == ')')
	{
		write(2, "xero: syntax error: subshell not handled\n", 42);
		exit_status(2, 1);
		return (0);
	}
	return (1);
}
