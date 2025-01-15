/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:19:52 by nrey              #+#    #+#             */
/*   Updated: 2024/10/15 15:45:26 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

size_t	unlen(unsigned int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

size_t	nlen(int n)
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

int	ft_vartype(va_list args, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_printfchar(va_arg(args, int));
	else if (c == 's')
		count += ft_printfstr(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		count += ft_printfnbr(va_arg(args, int));
	else if (c == '%')
		count += ft_printfchar(37);
	else if (c == 'u')
		count += ft_printfuint(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		count += ft_printfhex(va_arg(args, unsigned int), c);
	else if (c == 'p')
		count += ft_printfptr(va_arg(args, void *));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += ft_vartype(args, str[i + 1]);
			i++;
		}
		else
			count += ft_printfchar(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
