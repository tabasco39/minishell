/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 06:55:48 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 06:58:29 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (*lst && del)
	{
		while (*lst)
		{
			tmp = *lst;
			(*lst) = (*lst)->next;
			del(tmp->content);
			free(tmp);
		}
		lst = NULL;
	}
}
