/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_program.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:38:32 by aelison           #+#    #+#             */
/*   Updated: 2024/08/21 10:06:55 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_var	var;

	if (argc != 1 && argv && envp)
	{
		ft_putstr_fd("error : no arg need\n", 2);
		return (EXIT_FAILURE);
	}
	var.token = NULL;
	var.env = NULL;
	var.line = NULL;
	var.instru = NULL;
	ft_create_envp(&var.env, envp);
	var.tab_env = ft_new_envp(var.env);
	while (1)
	{
		var.line = ft_readline(var.env, NULL);
		ft_debug(&var);
	}
	return (0);
}
