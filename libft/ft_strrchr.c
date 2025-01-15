/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:09:07 by nrey              #+#    #+#             */
/*   Updated: 2024/10/06 16:26:22 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	uc;
	int				l;

	l = ft_strlen(s);
	uc = (unsigned char)c;
	while (l >= 0)
	{
		if (s[l] == uc)
			return ((char *)s + l);
		l--;
	}
	return (0);
}
