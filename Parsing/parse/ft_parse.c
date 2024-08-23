/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:14:33 by aelison           #+#    #+#             */
/*   Updated: 2024/08/23 14:03:44 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_parse_quote_dquote(t_token *head, char quote)
{
	t_token	*tmp;

	tmp = head->next;
	if (quote == 39)
	{
		while (tmp && tmp->token[0] != quote)
		{
			tmp->command = argument;
			tmp = tmp->next;
		}
	}
	else if (quote == 34)
	{
		while (tmp && tmp->token[0] != quote)
		{
			if (tmp->command == dollar)
				tmp = tmp->next;
			else
			{
				tmp->command = argument;
				tmp = tmp->next;
			}
		}
	}
	if (tmp && tmp->token[0] == quote)
		tmp->command = argument;
}

static void	ft_parse_aux(t_token *current, t_token *nxt)
{
	if (current->command == option)
	{
		if (nxt)
		{
			if (!(nxt->command >= e_pipe
					&& nxt->command <= append_redirect_output))
				nxt->command = argument;
		}
	}
	ft_parse_arg(current, nxt);
	ft_parse_no_arg(current, nxt);
	if (current->command == e_pipe && nxt)
	{
		nxt->is_head = 1;
		if (current->prev)
			current->prev->is_end = 1;
	}
	ft_redirection(current, nxt);
	if (current->is_head == 1 && nxt && nxt->command != option)
	{
		if (!(nxt->command >= e_pipe && nxt->command <= append_redirect_output)
			&& nxt->command != dollar)
			nxt->command = argument;
	}
	ft_parse_dollar(current, nxt);
	if (nxt == NULL)
		current->is_end = 1;
}

void	ft_parse(t_token *token, t_list *env)
{
	t_token	*current;
	char	**all_path;
	int		flag;

	flag = 0;
	current = token;
	while (current)
	{
		if (flag == 0)
		{
			if (current->token[0] == (char)34 || current->token[0] == (char)39)
			{
				ft_parse_quote_dquote(current, current->token[0]);
				flag = 1;
			}
		}
		ft_parse_aux(current, current->next);
		if (current->is_head == 1 && current->command == not_comm)
		{
			all_path = ft_get_all_path(env, current->token);
			if (ft_verify_exec_cmd(all_path) == 1)
				current->command = in_sys;
		}
		current = current->next;
	}
}
