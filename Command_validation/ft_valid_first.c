/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 08:36:51 by aelison           #+#    #+#             */
/*   Updated: 2024/08/29 15:38:33 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_valid_env(t_instru *current)
{
	t_token	*head;

	head = current->start;
	if (head && head->command == env)
	{
		if (head == current->end)
			return (EXIT_SUCCESS);
		head = head->next;
		if (head)
		{
			if (!(head->command >= e_pipe
					&& head->command <= append_redirect_output))
			{
				ft_putstr_fd("Error: env don't need arg\n", 2);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_valid_cd(t_instru *current)
{
	t_token	*head;

	head = current->start;
	if (head && head->command == cd)
	{
		if (head == current->end)
			return (EXIT_SUCCESS);
		head = head->next;
		if (head)
		{
			if (head->command == option)
				return (EXIT_FAILURE);
			if (head->next)
			{
				head = head->next;
				if (!(head->command >= e_pipe && head->command <= append_redirect_output))
					ft_putstr_fd("Error: cd too many arg\n", 2);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_valid_export(t_instru *current)
{
	t_token	*head;

	head = current->start;
	if (head && head->command == e_export)
	{
		if (head == current->end)
			return (EXIT_SUCCESS);
		head = head->next;
		if (head->command == option)
		{
			ft_putstr_fd("Error: export don't need option\n", 2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
