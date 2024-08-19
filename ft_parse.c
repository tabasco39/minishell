/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:14:33 by aelison           #+#    #+#             */
/*   Updated: 2024/08/19 14:33:07 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_parse_quote_dquote(t_token *head, char quote)
{
	t_token	*tmp;

	tmp = head->next;
	while (tmp && tmp->token[0] != quote)
	{
		tmp->command = argument;
		tmp = tmp->next;
	}
	if (tmp && tmp->token[0] == quote)
		tmp->command = argument;
}

int	ft_delimiter(t_token *nxt)
{
	t_comm	start;

	start = e_pipe;
	while (start != not_comm)
	{
		if (nxt->command == start)
			return (0);
		start++;
	}
	if (start == not_comm)
		return (1);
	return (0);
}

int	ft_parse_arg(t_token *nxt)
{
	if (nxt == NULL)
		return (0);
	else if (nxt->command == not_comm)
	{
		nxt->command = argument;
		return (0);
	}
	else if (nxt->command == option)
		return (0);
	if (ft_delimiter(nxt) == 1)
		nxt->command = argument;
	return (0);
}

int	ft_parse_no_arg(t_token *nxt)
{
	if (nxt == NULL)
		return (0);
	if (ft_delimiter(nxt) == 1)
	{
		ft_putstr_fd("error : parse no arg, don't need arg !\n", 2);
		return (1);
	}
	return (0);
}

int	ft_parse_aux(t_token *current, t_token *nxt)
{
	if (current->command == argument)
		return (0);
	/*command whith possible options, arguments*/
	if (current->command == cd)
		return (ft_parse_arg(nxt));
	else if (current->command == echo)
		return (ft_parse_arg(nxt));
	else if (current->command == unset)
		return (ft_parse_arg(nxt));
	else if (current->command == dollar)
		return (ft_parse_arg(nxt));
	else if (current->command == question)
		return (ft_parse_arg(nxt));
	else if (current->command == e_export)
		return (ft_parse_arg(nxt));
	else if (current->command == e_exit)
		return (ft_parse_arg(nxt));
	/*command whith NO arguments*/
	else if (current->command == pwd)
		return (ft_parse_no_arg(nxt));
	else if (current->command == env)
		return (ft_parse_no_arg(nxt));
	else
	{
		if (nxt)
		{
			if (nxt->command >= env && nxt->command <= e_exit)
				nxt->is_head = 1;
		}
	}
	return (0);
}

void	ft_parse(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->token[0] == (char)34 || current->token[0] == (char)39)
			ft_parse_quote_dquote(current, current->token[0]);
		if (ft_parse_aux(current, current->next) == 1)
			return ;
		current = current->next;
	}
}
