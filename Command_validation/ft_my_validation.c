/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:29:20 by aranaivo          #+#    #+#             */
/*   Updated: 2024/09/25 06:52:39 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_valid_pwd(t_instru *instruction)
{
	t_token	*current;

	current = instruction->start;
	if (instruction->start->command == pwd)
	{
		current = current->next;
		if (current && current->command == option)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_valid_unset(t_instru *instruction)
{
	if (instruction->start->command == unset)
	{
		if (instruction->start == instruction->end)
			return (EXIT_SUCCESS);
		if (instruction->start->next
			&& instruction->start->next->command == option)
		{
			ft_putstr_fd("unset: no option need\n", 2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_valid_exit(t_instru *instruction)
{
	t_token	*current;

	current = instruction->start;
	if (instruction->start->command == e_exit)
	{
		current = current->next;
		if (instruction->start == instruction->end)
			return (EXIT_SUCCESS);
		if (current && current->command == option)
			return (EXIT_FAILURE);
		if (ft_valid_exit_util(current->token) == 1)
			return (2);
	}
	return (EXIT_SUCCESS);
}

int	ft_valid_redirect_and_append_output(t_token *token)
{
	t_token	*current;

	current = token;
	if (current->command == redirect_output
		|| current->command == append_redirect_output)
	{
		current = current->next;
		if (!current)
		{
			ft_putendl_fd("minishell: error parse", 2);
			return (EXIT_FAILURE);
		}
		if (current->command >= e_pipe
			&& current->command <= append_redirect_output)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token", 2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_valid_redirect_input(t_token *token)
{
	t_token	*current;

	current = token;
	if (current->command == redirect_input)
	{
		current = current->next;
		if (!current || (current->command >= e_pipe
				&& current->command <= append_redirect_output))
		{
			ft_putendl_fd("minishell: syntax error near unexpected token", 2);
			return (EXIT_FAILURE);
		}
		if (open(current->token, O_RDONLY) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(current->token, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
