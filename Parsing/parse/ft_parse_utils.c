/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:13:08 by aelison           #+#    #+#             */
/*   Updated: 2024/09/25 07:17:01 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parse_arg(t_token *current, t_token *nxt)
{
	if (current->command >= cd && current->command <= e_exit)
	{
		if (nxt == NULL)
			return ;
		else
		{
			if (nxt->command == option)
				nxt = nxt->next;
			while (nxt && ((nxt->command == not_comm)
					|| (nxt->command == option)))
			{
				nxt->command = argument;
				nxt = nxt->next;
			}
		}
	}
}

void	ft_redirection(t_token *current, t_token *nxt)
{
	if (current->command >= redirect_input
		&& current->command <= append_redirect_output)
	{
		if (nxt)
			nxt->command = argument;
	}
}

int	ft_is_char_pair(char *line, char quote)
{
	int	i;

	i = 0;
	while (line[i] != quote)
		i++;
	while (line[i] == quote)
		i++;
	return (i);
}
