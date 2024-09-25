/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_program.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:38:32 by aelison           #+#    #+#             */
/*   Updated: 2024/09/25 11:03:44 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("\0", 0);
		rl_redisplay();
	}
}

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
	t_var				all_var;
	struct sigaction	act;
	struct sigaction	ignore;

	if (argc != 1 && argv && envp)
	{
		ft_putstr_fd("error : no arg need\n", 2);
		return (EXIT_FAILURE);
	}
	ft_init_var(&all_var, envp);
	ignore.sa_handler = SIG_IGN;
	ignore.sa_flags = SA_RESTART;
	act.sa_handler = my_handler;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	while (1)
	{
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &ignore, NULL);
		all_var.line = readline(GREEN"Minishell$> "RESET);
		if (all_var.line == NULL)
			ft_exit(&all_var, 0);
		add_history(all_var.line);
		ft_debug(&all_var);
	}
	return (0);
}
