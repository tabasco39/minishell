/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:13:04 by aranaivo          #+#    #+#             */
/*   Updated: 2024/08/23 14:21:55 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_change_argument(t_instru *instruction)
{
	t_token	*current;

	current = instruction->start->next;
	while (current && current != instruction->end)
	{
		if (current->command != dollar && !(current->command >= redirect_input
				&& current->command <= append_redirect_output))
			current->command = argument;
		current = current->next;
	}
	if (current == instruction->end && current->command != dollar
		&& !(current->command >= redirect_input
			&& current->command <= append_redirect_output))
		current->command = argument;
}

int	ft_valid_exit_util(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] != '$' && ft_isdigit(token[i]) == 0)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(token, 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_change_dollar_value(t_token *head, t_list *env)
{
	int		len;
	char	*env_value;
	t_token	*current;

	current = head;
	while (current)
	{
		if (current->next && current->command == dollar
			&& current->next->command == argument)
		{
			current = current->next;
			if (current->token[0] != '?' && current->token[0] != '$')
			{
				env_value = ft_getvar(env, current->token);
				len = ft_strlen(current->token);
				free(current->token);
				if (env_value)
					current->token = ft_strdup(env_value + len + 1);
				else
					current->token = ft_strdup("\n");
			}
		}
		current = current->next;
	}
}
