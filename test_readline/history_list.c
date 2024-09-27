/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-17 03:35:00 by aelison           #+#    #+#             */
/*   Updated: 2024/09/25 13:37:13 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_history	*ft_create_node_history(char *line)
{
	t_history	*result;

	result = malloc(sizeof(t_history));
	if (!result)
		return (NULL);
	result->line = ft_strdup(line);
	result->prev = NULL;
	result->next = NULL;
	return (result);
}

void	ft_add_node_history(t_history **head, t_history *to_add)
{
	t_history	*tmp;

	if (*head == NULL)
		*head = to_add;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = to_add;
		to_add->prev = tmp;
	}
}

void	ft_clear_history(t_history **head)
{
	t_history	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->line);
		free(tmp);
	}
}

t_history	*ft_get_pos_history(t_history *current, char pos)
{
	if (current == NULL)
		return (NULL);
	if (pos == 's')
	{
		while (current->prev != NULL)
			current = current->prev;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
	}
	return (current);
}

void	ft_show_history(t_history *current, char *message)
{
	t_history	*head;

	head = current;
	printf("%s\n", message);
	while (head)
	{
		printf("%s", head->line);
		head = head->next;
	}
}
