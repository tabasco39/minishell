/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 08:36:51 by aelison           #+#    #+#             */
/*   Updated: 2024/08/23 08:44:56 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_valid_env(t_instru *current)
{
	t_token	*head;

	head = current->start;
	if (head && head->command == env)
	{
		head = head->next;
		if (head)
		{
			if (head->command == argument)
			{
				ft_putstr_fd("Error: env don't need argument\n", 2);
				return (EXIT_FAILURE);
			}
			else if (head->command == option)
			{
				ft_putstr_fd("Error: env don't need option\n", 2);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_valid_echo(t_instru *current)
{
	t_token	*head;

	head = current->start;
	if (head && head->command == echo)
	{
		if (head == current->end)
			return (EXIT_SUCCESS);
		head = head->next;
		if (head && head->command == option)
		{
			if (ft_strncmp(head->token, "-n", 2) != 0)
			{
				ft_putstr_fd("Error: wrong echo option\n", 2);
				return (EXIT_FAILURE);
			}
		}
		else
			ft_change_argument(current);
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
		if (head && head->command == option)
		{
			ft_putstr_fd("Error: cd don't need option\n", 2);
			return (EXIT_FAILURE);
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
		else
			ft_change_argument(current);
	}
	return (EXIT_SUCCESS);
}
