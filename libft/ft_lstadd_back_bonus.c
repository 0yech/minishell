/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 06:31:16 by nrey              #+#    #+#             */
/*   Updated: 2024/10/10 20:43:00 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cpy;

	cpy = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (cpy->next)
		cpy = cpy->next;
	cpy->next = new;
}
