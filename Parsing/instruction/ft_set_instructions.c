/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:13:39 by aelison           #+#    #+#             */
/*   Updated: 2024/08/21 10:02:20 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count_token_in_instru(t_instru *current)
{
	int		result;
	t_token	*head;

	result = 1;
	if (!current || !current->start || !current->end)
		return (0);
	head = current->start;
	while (head && head != current->end)
	{
		result++;
		head = head->next;
	}
	return (result);
}

static t_instru	*ft_create_instru(t_token *head, t_token *end, int id)
{
	t_instru	*result;

	result = malloc(sizeof(t_instru));
	if (!result)
		return (NULL);
	result->id = id;
	result->start = head;
	result->end = end;
	result->next = NULL;
	result->prev = NULL;
	return (result);
}

static void	ft_add_instru(t_instru **head, t_instru *elem)
{
	t_instru	*tmp;

	if (*head == NULL)
		*head = elem;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
		elem->prev = tmp;
	}
}

t_instru	*ft_set_instru(t_token *head)
{
	t_instru	*result;
	t_token		*start;
	t_token		*end;
	int			id;

	id = 1;
	result = NULL;
	start = NULL;
	end = NULL;
	while (head)
	{
		if (head->is_head == 1)
			start = head;
		if (head->is_end == 1)
			end = head;
		if (start && end)
		{
			ft_add_instru(&result, ft_create_instru(start, end, id));
			id++;
			start = NULL;
			end = NULL;
		}
		head = head->next;
	}
	return (result);
}
