/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 08:12:40 by aelison           #+#    #+#             */
/*   Updated: 2024/08/23 14:16:25 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_error(t_token *lst)
{
	if (ft_valid_dollar(lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_valid_delim_input(lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_valid_pipe(lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_valid_redirect_and_append_output(lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_valid_redirect_input(lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (lst->command == option && lst->is_head == 1)
	{
		ft_putstr_fd("Error : command not found\n", 2);
		return (EXIT_FAILURE);
	}
	if (lst->command == not_comm)
	{
		ft_putstr_fd("Error : input not valid\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_correct_instru(t_token *lst)
{
	while (lst)
	{
		if (ft_is_error(lst) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

void	ft_cmd_validation(t_var *all)
{
	t_instru	*all_instru;

	all_instru = all->instru;
	ft_change_dollar_value(all->token, all->env);
	while (all_instru)
	{
		if (ft_valid_env(all_instru) == EXIT_FAILURE)
			ft_exit(all, 1);
		if (ft_valid_pwd(all_instru) == EXIT_FAILURE)
			ft_exit(all, 1);
		if (ft_valid_unset(all_instru) == EXIT_FAILURE)
			ft_exit(all, 1);
		if (ft_valid_echo(all_instru) == EXIT_FAILURE)
			ft_exit(all, 1);
		if (ft_valid_export(all_instru) == EXIT_FAILURE)
			ft_exit(all, 1);
		if (ft_valid_exit(all_instru) == EXIT_FAILURE)
			ft_exit(all, 1);
		all_instru = all_instru->next;
	}
	if (ft_correct_instru(all->token) == EXIT_FAILURE)
		ft_exit(all, 1);
}
