/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:45:37 by nrey              #+#    #+#             */
/*   Updated: 2024/10/15 16:57:44 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"
#include <stdio.h>

int	main(void)
{
	printf("Real printf : ");
	printf("%c%c%c\n", 'a', '\t', 'b');
	ft_printf("ft_printf : ");
	ft_printf("%c%c%c\n", 'a', '\t', 'b');
	return (0);
}
