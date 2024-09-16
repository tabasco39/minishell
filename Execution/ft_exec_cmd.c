/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:54:10 by aelison           #+#    #+#             */
/*   Updated: 2024/09/16 09:02:07 by aranaivo         ###   ########.fr       */
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

void	ft_echo(char *to_print, char option)
{
	int		i;
	int		quote;

	i = 0;
	quote = ft_first_quote(to_print, 34, 39);
	if (quote == '\0' && to_print)
		ft_putstr_fd(to_print, 1);
	else if (quote != '\0')
	{
	}
	if (option != '\0')
		ft_putchar_fd('\n', 1);
}

// void	ft_cd(void)
// {

// }

char	*ft_pwd(void)
{
	char	directory[1024];
	char	*result;

	result = getcwd(directory, sizeof(directory));
	if (result == NULL)
	{
		ft_putstr_fd("error : getcwd\n", 2);
		return (NULL);
	}
	return (result);
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
	ft_lstclear_instru(&var->instru, &var->token);
	ft_lstclear(&var->env, free);
	ft_free_all(var->tab_env);
	free(var->line);
	ft_putstr_fd("exit : good bye beautiful shell 💩\n", end);
	exit(end);
}
