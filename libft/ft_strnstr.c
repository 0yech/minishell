/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 01:07:14 by nrey              #+#    #+#             */
/*   Updated: 2024/10/11 17:32:18 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i < len && *haystack)
	{
		j = 0;
		while (haystack[j] && haystack[j] == needle[j] && (i + j) < len)
			j++;
		if (!needle[j])
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (0);
}
