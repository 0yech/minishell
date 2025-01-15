/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <marvin@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:04:26 by nrey              #+#    #+#             */
/*   Updated: 2024/10/03 18:04:29 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	return (0);
}

/*
int	main(void)
{
	ft_isalpha(12);		0
	ft_isalpha(176);	0
	ft_isalpha(32);		0
	ft_isalpha(67);		1
	ft_isalpha(103);	1
	ft_isalpha(173);	0
	return (0);
}
*/
