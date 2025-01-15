/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:13:24 by nrey              #+#    #+#             */
/*   Updated: 2024/10/16 16:48:08 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_printfchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printfstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

char	*ft_unsigneditoa(unsigned int n)
{
	char	*s;
	size_t	len;

	len = unlen(n);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len] = '\0';
	if (n == 0)
		s[0] = '0';
	while (n != 0)
	{
		s[--len] = n % 10 + 48;
		n = n / 10;
	}
	return (s);
}

int	ft_printfuint(unsigned int n)
{
	char	*p;
	int		count;

	p = ft_unsigneditoa(n);
	count = ft_printfstr(p);
	free(p);
	p = NULL;
	return (count);
}

int	ft_printfnbr(int n)
{
	char	*p;
	int		count;

	p = ft_itoa(n);
	count = ft_printfstr(p);
	free(p);
	p = NULL;
	return (count);
}
