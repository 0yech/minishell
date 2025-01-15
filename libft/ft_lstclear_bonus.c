/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 06:54:11 by nrey              #+#    #+#             */
/*   Updated: 2024/10/10 20:02:53 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cpy;

	if (lst && del)
	{
		while (*lst)
		{
			cpy = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = cpy;
		}
		lst = NULL;
	}
}
