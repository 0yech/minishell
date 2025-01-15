/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:57:39 by nrey              #+#    #+#             */
/*   Updated: 2024/10/15 14:22:03 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *str, ...);
int		ft_vartype(va_list args, char c);
int		ft_printfnbr(int n);
int		ft_printfuint(unsigned int n);
char	*ft_unsigneditoa(unsigned int n);
size_t	nlen(int n);
size_t	unlen(unsigned int n);
int		ft_printfptr(void *ptr);
int		ft_printfhex(unsigned int n, char c);
int		ft_putnbr_base(unsigned long n, char *base);
int		ft_printfstr(char *str);
int		ft_printfchar(int c);

#endif
