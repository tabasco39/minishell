/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:33:59 by aelison           #+#    #+#             */
/*   Updated: 2024/08/08 10:10:50 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Si commande invalide afficher "error : invalide command"
 * Si option invalide "error : invalide option"
 * Si ???
 * 
*/
#include "minishell.h"

int	ft_correct_instru(t_token *lst)
{
	while (lst)
	{
		if (lst->is_head == 1 && lst->command == not_comm)
		{
			ft_putstr_fd("Error : first token not a command", 2);
			return (EXIT_FAILURE);
		}
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}
