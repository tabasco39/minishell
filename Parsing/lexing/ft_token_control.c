/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 08:48:33 by aelison           #+#    #+#             */
/*   Updated: 2024/09/25 07:32:17 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*ft_move_first_aux(t_token *head, t_token *b_end,
	t_token *start, t_token *end)
{
	t_token	*tmp_prev;

	tmp_prev = start->prev;
	head = start;
	while (head->prev)
		head = head->prev;
	b_end->next = head;
	head->prev = b_end;
	tmp_prev->next = end;
	if (end)
		end->prev = tmp_prev;
	return (start);
}

t_token	*ft_move_sec_aux(t_token *head, t_token *b_end,
	t_token *start, t_token *end)
{
	t_token	*tmp_nxt;
	t_token	*tmp_prev;

	tmp_nxt = head->next;
	head->next = start;
	tmp_prev = start->prev;
	start->prev = head;
	tmp_nxt->prev = b_end;
	b_end->next = tmp_nxt;
	tmp_prev->next = end;
	if (end)
		end->prev = tmp_prev;
	return (tmp_nxt);
}

t_token	*ft_move_next_to_target(t_token *head, t_token *start, t_token *end)
{
	t_token	*before_end;
	t_token	*result;

	before_end = start;
	while (before_end->next != end)
		before_end = before_end->next;
	if (head == NULL)
		result = ft_move_first_aux(head, before_end, start, end);
	else
		result = ft_move_sec_aux(head, before_end, start, end);
	return (result);
}

int	ft_command_setup_aux(t_token **head)
{
	t_token	*start;
	t_token	*end;

	start = (*head)->next;
	if (start)
	{
		end = start->next;
		if (end && !(end->command >= e_pipe
				&& end->command <= append_redirect_output))
		{
			start = end;
			while (end)
			{
				if (end->command >= e_pipe
					&& end->command <= append_redirect_output)
					break ;
				end = end->next;
			}
			*head = ft_move_next_to_target((*head)->prev, start, end);
			return (1);
		}
	}
	return (0);
}

void	ft_command_setup(t_token **head)
{
	t_token	*tmp;
	int		value;

	tmp = *head;
	while (tmp)
	{
		value = 0;
		if (tmp->command >= redirect_input
			&& tmp->command <= append_redirect_output)
			value = ft_command_setup_aux(&tmp);
		if (value == 0)
			tmp = tmp->next;
		else if (!(tmp->command >= redirect_input
				&& tmp->command <= append_redirect_output))
			*head = tmp;
		else
			tmp = *head;
	}
}
