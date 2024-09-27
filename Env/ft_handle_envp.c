/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 07:54:52 by aelison           #+#    #+#             */
/*   Updated: 2024/09/27 08:47:12 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_move_to_target(t_list *env, char *target)
{
	size_t	len;

	if (!env || !target)
		return (NULL);
	len = ft_strlen(target);
	while (ft_strncmp(env->content, target, len) != 0 && env)
		env = env->next;
	return (env);
}

void	ft_sort_env_list(t_list **result, char **tab_env)
{
	t_list	*tmp;
	t_list	*tmp_nxt;
	void	*stack;
	int		val;

	ft_create_envp(result, tab_env);
	tmp = *result;
	tmp_nxt = tmp->next;
	while (tmp_nxt)
	{
		val = ft_strncmp((char *)tmp->content, (char *)tmp_nxt->content, 1);
		if (val > 0)
		{
			stack = tmp->content;
			tmp->content = tmp_nxt->content;
			tmp_nxt->content = stack;
			tmp = *result;
			tmp_nxt = tmp->next;
		}
		else
		{
			tmp = tmp->next;
			tmp_nxt = tmp->next;
		}
	}
}

int	ft_export(t_var *var, char *to_add)
{
	int		end;
	char	*exist;
	char	*var_envp;
	t_list	*tmp;

	tmp = NULL;
	if (to_add == NULL)
	{
		ft_sort_env_list(&tmp, var->tab_env);
		ft_display_env(&tmp, NULL);
		ft_lstclear(&tmp, free);
		return (0);
	}
	var_envp = NULL;
	end = ft_find_char(to_add, '=');
	if (end == -1)
		var_envp = NULL;
	else
		var_envp = ft_substr(to_add, 0, end);
	exist = ft_getvar(var->env, var_envp);
	if (!exist)
	{
		ft_lstadd_back(&var->env, ft_lstnew(ft_strdup(to_add)));
		ft_free_all(var->tab_env);
		var->tab_env = ft_new_envp(var->env);
		free(var_envp);
		return (0);
	}
	tmp = ft_move_to_target(var->env, var_envp);
	free(tmp->content);
	tmp->content = ft_strjoin_shell(var_envp, to_add + end);
	ft_free_all(var->tab_env);
	var->tab_env = ft_new_envp(var->env);
	return (1);
}

char	*ft_env_variable(t_list *envp, char *to_find)
{
	int		end;
	char	*tmp;
	char	*result;
	char	*new_find;

	end = ft_find_char(to_find, ' ');
	new_find = ft_strdup(to_find);
	if (end != -1)
	{
		free(new_find);
		new_find = ft_substr(to_find, 0, end);
	}
	tmp = ft_getvar(envp, new_find);
	if (new_find)
		free(new_find);
	if (!tmp)
		return (NULL);
	result = ft_strchr(tmp, '=');
	if (!result)
		return (NULL);
	return (result + 1);
}
