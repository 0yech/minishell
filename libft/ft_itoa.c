/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 06:03:26 by nrey              #+#    #+#             */
/*   Updated: 2024/10/13 13:16:30 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	appnbr(char *p, int n, int c)
{
	if (n >= 10)
	{
		appnbr(p, n / 10, c - 1);
		n = n % 10;
	}
	p[c] = n + 48;
}

char	*ft_itoa(int n)
{
	char			*s;
	size_t			len;
	int				nb;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = nlen(n);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	s[len] = '\0';
	nb = n;
	if (n < 0)
	{
		s[0] = '-';
		nb = -n;
	}
	appnbr(s, nb, len - 1);
	return (s);
}
/*
int	main(void)
{
	ft_itoa(-2147483648);
	return (0);
}
*/
