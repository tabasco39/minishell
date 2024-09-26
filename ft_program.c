/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_program.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:38:32 by aelison           #+#    #+#             */
/*   Updated: 2024/09/25 08:02:21 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_var(t_var *all, char **envp)
{
	all->token = NULL;
	all->env = NULL;
	all->line = NULL;
	all->instru = NULL;
	ft_create_envp(&all->env, envp);
	all->tab_env = ft_new_envp(all->env);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	all_var;

	if (argc != 1 && argv && envp)
	{
		ft_putstr_fd("error : no arg need\n", 2);
		return (EXIT_FAILURE);
	}
	ft_init_var(&all_var, envp);
	while (1)
	{
		all_var.line = readline(GREEN"Minishell$> "RESET);
		add_history(all_var.line);
		ft_debug(&all_var);
	}
	return (0);
}
