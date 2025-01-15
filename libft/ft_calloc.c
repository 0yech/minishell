/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <marvin@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:16:12 by nrey              #+#    #+#             */
/*   Updated: 2024/10/03 18:03:34 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*e;
	size_t	n;

	n = count * size;
	e = malloc(n);
	if (!e)
		return (0);
	ft_bzero(e, n);
	return (e);
}
