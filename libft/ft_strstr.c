/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:45:21 by bchiki            #+#    #+#             */
/*   Updated: 2025/07/07 17:45:22 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	hay_len;
	size_t	needle_len;
	size_t	i;

	if (!needle || !*needle)
		return ((char *)haystack);
	if (!haystack)
		return (NULL);
	hay_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	if (needle_len > hay_len)
		return (NULL);
	while (*haystack)
	{
		i = 0;
		while (haystack[i] == needle[i] && i < needle_len)
			i++;
		if (i == needle_len)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
