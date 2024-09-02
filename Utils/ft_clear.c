/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:36:49 by aelison           #+#    #+#             */
/*   Updated: 2024/08/29 13:18:24 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_del_token(t_token **head)
{
	t_token	*tmp;

	if (head && *head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->token);
		free(tmp);
	}
}

void	ft_lstclear_shell(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = *head;
		(*head) = (*head)->next;
		free(tmp->token);
		free(tmp);
	}
	*head = NULL;
}

void	ft_free_all(char **split)
{
	int	i;

	i = 0;
	if (*split != NULL)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}
