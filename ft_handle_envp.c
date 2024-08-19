/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 07:54:52 by aelison           #+#    #+#             */
/*   Updated: 2024/08/14 10:30:20 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_export(t_var *var, char *to_add)
{
	int		end;
	char	*exist;
	char	*var_envp;
	t_list	*tmp;

	var_envp = NULL;
	end = ft_find_char(to_add, '=');
	if (end == -1)
		return (1);
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

char	*ft_env_variable(t_list *envp, char *to_find, int quote)
{
	int		end;
	char	*tmp;
	char	*result;
	char	*new_find;

	end = ft_find_char(to_find, ' ');
	new_find = ft_del_quote(ft_strdup(to_find), quote);
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
