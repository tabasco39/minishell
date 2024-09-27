/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:33:37 by aelison           #+#    #+#             */
/*   Updated: 2024/09/26 15:06:51 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_create_envp(t_list **all_env, char **envp)
{
	int		i;
	char	*val;
	t_list	*new_env;

	i = 0;
	while (envp[i])
	{
		new_env = ft_lstnew(ft_strdup((void *)envp[i]));
		if (new_env == NULL)
		{
			ft_lstclear(all_env, free);
			return ;
		}
		if (ft_strncmp((char *)new_env->content, "SHLVL", 5) == 0)
		{
			val = ft_itoa(ft_atoi((char *)new_env->content + 6) + 1);
			ft_lstdelone(new_env, free);
			new_env = ft_lstnew(ft_strjoin("SHLVL=", val));
			free(val);
		}
		ft_lstadd_back(all_env, new_env);
		i++;
	}
}

int	ft_unset_aux(t_var *var, char *to_del, size_t len)
{
	t_list	*after;
	t_list	*current;

	current = var->env;
	if (current == NULL || to_del == NULL)
		return (1);
	after = current->next;
	if (ft_strncmp(current->content, to_del, len) == 0)
	{
		ft_lstdelone(current, free);
		var->env = after;
		ft_free_all(var->tab_env);
		var->tab_env = ft_new_envp(var->env);
		return (1);
	}
	return (0);
}

int	ft_unset_envp(t_var *var, char *to_del)
{
	t_list	*tmp;
	t_list	*after;
	size_t	len;

	tmp = var->env;
	after = tmp->next;
	len = ft_strlen(to_del);
	if (ft_unset_aux(var, to_del, len) != 0)
		return (0);
	while (after)
	{
		if (ft_strncmp(after->content, to_del, len) == 0)
		{
			tmp->next = after->next;
			ft_lstdelone(after, free);
			ft_free_all(var->tab_env);
			var->tab_env = ft_new_envp(var->env);
			return (0);
		}
		tmp = tmp->next;
		after = after->next;
	}
	return (1);
}

char	**ft_new_envp(t_list *env)
{
	int		i;
	int		len_env;
	char	**result;

	if (!env)
		return (NULL);
	len_env = ft_lstsize(env);
	result = malloc(sizeof(char *) * (len_env + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (env)
	{
		result[i] = ft_strdup((char *)env->content);
		if (result[i] == NULL)
		{
			ft_free_all(result);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	result[i] = NULL;
	return (result);
}

char	*ft_getvar(t_list *env, char *var)
{
	size_t	var_len;

	if (!env || !var)
		return (NULL);
	var_len = ft_strlen(var);
	while (env)
	{
		if (ft_strncmp((char *)env->content, var, var_len) == 0)
			return ((char *)env->content);
		env = env->next;
	}
	return (NULL);
}
