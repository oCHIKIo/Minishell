/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 04:47:07 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/25 15:34:30 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_special_chars(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			skip_quoted_section(input, &i);
		else if (input[i] == '(' || input[i] == ')')
		{
			if (!check_parentheses(input, i))
				return (0);
			i++;
		}
		else
			i++;
	}
	return (1);
}

char	*read_input(void)
{
	char	*trimmed;
	char	*input;

	input = get_user_input();
	if (!input)
		return (NULL);
	if (!validate_input_syntax(input))
	{
		free(input);
		return (ft_strdup(""));
	}
	if (!check_special_chars(input))
	{
		free(input);
		return (ft_strdup(""));
	}
	trimmed = trim_whitespace(input);
	free(input);
	return (trimmed);
}
