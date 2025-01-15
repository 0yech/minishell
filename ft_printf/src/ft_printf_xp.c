/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:06:16 by nrey              #+#    #+#             */
/*   Updated: 2024/10/15 15:30:15 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_putnbr_base(unsigned long n, char *base)
{
	unsigned long	baselen;
	int				count;

	count = 0;
	baselen = 0;
	while (base[baselen])
		baselen++;
	if (n >= baselen)
	{
		count += ft_putnbr_base(n / baselen, base);
		count += ft_putnbr_base(n % baselen, base);
	}
	else
	{
		ft_printfchar(base[n]);
		count++;
	}
	return (count);
}

int	ft_printfhex(unsigned int n, char c)
{
	char	*base;
	int		count;

	count = 0;
	base = "0";
	if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	count += ft_putnbr_base((unsigned long)n, base);
	return (count);
}

int	ft_printfptr(void *ptr)
{
	int	count;

	count = ft_printfstr("0x");
	count += ft_putnbr_base((unsigned long)ptr, "0123456789abcdef");
	return (count);
}
