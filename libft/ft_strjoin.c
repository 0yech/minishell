/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 03:36:09 by nrey              #+#    #+#             */
/*   Updated: 2024/10/05 03:55:07 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	p = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, lens1 + 1);
	ft_strlcat(p, s2, lens1 + lens2 + 1);
	return (p);
}
