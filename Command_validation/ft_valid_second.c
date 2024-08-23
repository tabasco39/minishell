/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_second.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 06:49:56 by aelison           #+#    #+#             */
/*   Updated: 2024/08/23 14:14:51 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_valid_dollar(t_token *head)
{
	if (head && head->command == dollar)
	{
		if (head->prev == NULL)
		{
			ft_putstr_fd("Error: invalid use of $\n", 2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_valid_delim_input(t_token *head)
{
	if (head && head->command == delimiter_redirect_input)
	{
		if (head->next)
		{
			if (head->next->command >= e_pipe
				&& head->next->command <= append_redirect_output)
			{
				ft_putstr_fd("Error : invalid << command\n", 2);
				return (EXIT_FAILURE);
			}
		}
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_valid_pipe(t_token *head)
{
	if (head && head->command == e_pipe)
	{
		if (head->prev == NULL)
			return (EXIT_FAILURE);
		if (head->next)
		{
			if (head->next->command == e_pipe)
			{
				ft_putstr_fd("Error : invalid pipe command\n", 2);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}
