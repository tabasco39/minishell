/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:13:08 by aelison           #+#    #+#             */
/*   Updated: 2024/08/23 14:02:59 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parse_arg(t_token *current, t_token *nxt)
{
	if (current->command >= cd && current->command <= e_exit)
	{
		if (nxt == NULL)
			return ;
		else if (nxt->command == not_comm)
		{
			nxt->command = argument;
			return ;
		}
	}
}

void	ft_parse_dollar(t_token *current, t_token *nxt)
{
	if (current->command == dollar)
	{
		if (nxt == NULL)
			current->command = argument;
		else
		{
			if (nxt->command >= e_pipe && nxt->command <= append_redirect_output)
				current->command = argument;
			if (nxt->command == not_comm)
				nxt->command = argument;
		}
	}
}

void	ft_parse_no_arg(t_token *current, t_token *nxt)
{
	if (current->command >= env && current->command <= pwd)
	{
		if (nxt == NULL)
			return ;
		else if (nxt->command >= e_pipe && nxt->command <= not_comm)
			return ;
	}
}

void	ft_redirection(t_token *current, t_token *nxt)
{
	t_token	*tmp;

	if (current->command >= redirect_input
		&& current->command <= append_redirect_output)
	{
		if (nxt)
		{
			if (nxt->command == '$')
			{
				if (nxt->next == NULL)
					nxt->command = argument;
				else
				{
					tmp = nxt->next;
					if (!(tmp->command >= e_pipe
							&& tmp->command <= append_redirect_output))
						nxt->next->is_head = 1;
				}
			}
		}
	}
}
