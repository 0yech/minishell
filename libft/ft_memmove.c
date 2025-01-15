/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <marvin@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:35:19 by nrey              #+#    #+#             */
/*   Updated: 2024/10/10 20:40:25 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*srdst;
	const unsigned char	*srccpy;

	if (n == 0 || dst == src)
		return (dst);
	srdst = (unsigned char *)dst;
	srccpy = (unsigned char *)src;
	if (srccpy < srdst && srdst < srccpy + n)
	{
		srdst += n;
		srccpy += n;
		while (n--)
			*(--srdst) = *(--srccpy);
	}
	else
	{
		while (n--)
			*srdst++ = *srccpy++;
	}
	return (dst);
}
