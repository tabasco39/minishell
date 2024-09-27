/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:54:10 by aelison           #+#    #+#             */
/*   Updated: 2024/09/27 09:52:38 by aranaivo         ###   ########.fr       */
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

int	ft_exec_builtin(t_var *all_var, t_token *start, t_token *end)
{
	int		result;
	char	*tmp;
	t_token	*new_s;

	tmp = "\n";
	result = 1;
	new_s = start->next;
	if (start->command == echo)
	{
		if (new_s && new_s->command == option)
		{
			tmp = new_s->token;
			new_s = new_s->next;
		}
		while (new_s != end && new_s && new_s->command == argument)
		{
			ft_echo(new_s->token, '\0');
			ft_putstr_fd(" ", 1);
			new_s = new_s->next;
		}
		if (new_s && new_s == end)
			ft_echo(new_s->token, tmp[0]);
		else
			ft_echo("\0", tmp[0]);
		return (0);
	}
	else if (start->command == cd)
	{
		tmp = ft_getvar(all_var->env, "HOME");
		if (new_s)
		{
			if (new_s->token[0] == '~')
				result = ft_cd(tmp + 5);
			else
				result = ft_cd(new_s->token);
		}
		else
			result = ft_cd(tmp + 5);
	}
	else if (start->command == pwd)
	{
		tmp = ft_pwd();
		if (tmp != NULL)
		{
			printf("%s\n", tmp);
			result = 0;
		}
	}
	else if (start->command == e_export)
	{
		while (new_s != end && new_s)
		{
			ft_export(all_var, new_s->token);
			new_s = new_s->next;
		}
		if (new_s)
			result = ft_export(all_var, new_s->token);
		else
			result = ft_export(all_var, NULL);
	}
	else if (start->command == unset)
	{
		while (new_s != end && new_s)
		{
			ft_unset_envp(all_var, new_s->token);
			new_s = new_s->next;
		}
		if (new_s)
			result = ft_unset_envp(all_var, new_s->token);
		else
		{
			ft_putchar_fd('\n', 1);
			result = 0;
		}
	}
	else if (start->command == env)
	{
		ft_display_env(&all_var->env, "exist");
		result = 0;
	}
	return (result);
}
