/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:54:10 by aelison           #+#    #+#             */
/*   Updated: 2024/08/29 15:14:43 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	ft_first_quote(char *word, char first, char second)
{
	int		i;

	i = 0;
	if (!word)
		return (-1);
	while (word[i] != '\0')
	{
		if (word[i] == first || word[i] == second)
			return (word[i]);
		i++;
	}
	return (-1);
}

void	ft_echo(t_list *env, char *to_print)
{
	int		i;
	int		quote;
	char	*tmp;

	i = 0;
	quote = ft_first_quote(to_print, 34, 39);
	while (to_print[i] != '\0')
	{
		while (to_print[i] == quote)
			i++;
		if (to_print[i] == '$')
		{
			tmp = ft_env_variable(env, to_print + i + 1);
			if (tmp)
				ft_putstr_fd(tmp, 1);
			while (to_print[i] != '\0' && to_print[i] != ' ')
				i++;
		}
		ft_putchar_fd(to_print[i], 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

void	ft_cd(void);

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
	ft_putstr_fd("exit 💩\n", end);
	exit(end);
}
