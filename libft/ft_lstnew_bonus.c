/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 06:13:14 by nrey              #+#    #+#             */
/*   Updated: 2024/10/10 06:16:00 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*l;

	l = (t_list *)malloc(sizeof(t_list));
	if (!l)
		return (NULL);
	l->content = content;
	l->next = NULL;
	return (l);
}
