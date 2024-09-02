/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 08:48:33 by aelison           #+#    #+#             */
/*   Updated: 2024/08/29 13:55:27 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_move_nxt_to_head(t_token **head, t_token *target)
{
	t_token	*tmp_one;
	t_token	*tmp_two;
	t_token	*tmp_three;

	if (head && *head)
	{
		if (target)
		{
			tmp_one = (*head)->next;
			tmp_two = target->prev;
			(*head)->next = target;
			target->prev = (*head);
			while (target->next && !(target->next->command >= e_pipe
					&& target->next->command <= append_redirect_output))
				target = target->next;
			tmp_three = target->next;
			tmp_two->next = tmp_three;
			target->next = tmp_one;
			tmp_one->prev = target;
			if (tmp_three)
				tmp_three->prev = tmp_two;
		}
	}
}

void	ft_move_target_prev_head(t_token **head, t_token *target)
{
	t_token	*tmp_one;
	t_token	*tmp_two;

	if (head && *head)
	{
		tmp_one = (*head)->prev;
		tmp_two = *head;
		while (tmp_two->next && !(tmp_two->next->command >= e_pipe
				&& tmp_two->next->command <= append_redirect_output))
			tmp_two = tmp_two->next;
		(*head)->prev = NULL;
		tmp_one->next = tmp_two->next;
		tmp_two->next = target;
		target->prev = tmp_two;
	}
}

void	ft_cmd_setup_aux(t_token *nxt, t_token **tmp, t_token **head)
{
	t_token	*moi;

	moi = NULL;
	if (nxt->next && nxt->next->next)
		moi = nxt->next->next;
	if (*tmp)
	{
		if (moi && moi->command != e_pipe)
			ft_move_nxt_to_head(tmp, moi);
	}
	else
	{
		if (moi && moi->command != e_pipe)
		{
			*tmp = moi;
			ft_move_target_prev_head(tmp, nxt);
			*head = *tmp;
		}
	}
	*tmp = nxt->prev;
}

void	ft_command_setup(t_token **head)
{
	t_token	*tmp;
	t_token	*nxt;

	tmp = NULL;
	nxt = (*head);
	while (nxt)
	{
		if (nxt->command == e_pipe)
			tmp = NULL;
		if (nxt->command >= redirect_input
			&& nxt->command <= append_redirect_output)
		{
			if (tmp == NULL)
				tmp = nxt->prev;
			ft_cmd_setup_aux(nxt, &tmp, head);
		}
		nxt = nxt->next;
	}
}
