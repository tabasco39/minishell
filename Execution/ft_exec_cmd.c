/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:54:10 by aelison           #+#    #+#             */
/*   Updated: 2024/09/25 08:02:49 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	ft_first_quote(char *word, char first, char second)
{
	int		i;

	i = 0;
	if (!word)
		return ('\0');
	while (word[i] != '\0')
	{
		if (word[i] == first || word[i] == second)
			return (word[i]);
		i++;
	}
	return ('\0');
}

void	ft_lstclear_instru(t_instru **instru, t_token **head)
{
	t_instru	*tmp;

	ft_lstclear_shell(head);
	while (*instru)
	{
		tmp = *instru;
		*instru = (*instru)->next;
		free(tmp);
	}
}

void	ft_exit(t_var *var, int end)
{
	rl_clear_history();
	ft_lstclear_instru(&var->instru, &var->token);
	ft_lstclear(&var->env, free);
	ft_free_all(var->tab_env);
	free(var->line);
	ft_putstr_fd("exit : good bye beautiful shell 💩\n", end);
	exit(end);
}
