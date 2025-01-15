/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 00:11:31 by nrey              #+#    #+#             */
/*   Updated: 2024/10/05 01:11:22 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	slen;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (start + len > slen)
		len = slen - start;
	p = malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s + start, len + 1);
	return (p);
}
/*
int	main(void)
{
	char const s[] = "salademalikoum";
	char	*f;

	f = ft_substr(s, 4, 3);
	return (0);
}



ft_substr("salademalikoum",4,3) = dem


*/
