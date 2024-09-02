/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:55:02 by aelison           #+#    #+#             */
/*   Updated: 2024/09/02 10:26:21 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_token(t_token *token)
{
	int	i;

	i = 0;
	printf("\n=================== Display token ==========================\n");
	while (token)
	{
		printf("Token %d\n", i);
		printf("token = %s\t", token->token);
		printf("is_head = %d\t", token->is_head);
		printf("is_end = %d\t", token->is_end);
		printf("t_comm = %d\n\n", token->command);
		i++;
		token = token->next;
	}
}

void	ft_display_instru(t_instru *head)
{
	printf("\n=================== Display INSTRU ==========================\n");
	while (head)
	{
		printf("id = %d\t", head->id);
		printf("start = %s\t", head->start->token);
		printf("end = %s\n\n", head->end->token);
		head = head->next;
	}
}

void	ft_disp_dchar(char **str)
{
	int	i;

	i = 0;
	printf("\n===================== Display char ** ======================\n");
	while (str[i])
	{
		printf("str[%d] = %s\n", i, str[i]);
		i++;
	}
}

void	ft_display_env(t_list **env)
{
	t_list	*tmp;

	printf("\n================ Display t_list env ====================\n");
	tmp = *env;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

void	ft_debug(t_var *var)
{
	var->path = ft_get_all_path(var->env, var->line);
	ft_verify_exec_cmd(var->path);
	if (ft_strncmp(var->line, "exit", 4) == 0)
		ft_exit(var, 0);
	/*else if (ft_strncmp(var->line, "unset", 5) == 0)
		ft_unset_envp(var, var->line + 6);
	else if (ft_strncmp(var->line, "env", 3) == 0)
	{
		ft_display_env(&var->env);
		ft_disp_dchar(var->tab_env);
	}
	else if (ft_strncmp(var->line, "export", 6) == 0)
		ft_export(var, var->line + 7);
	*/
	//else
	//{
	ft_div_by_token(var->line, &var->token);
	ft_command_setup(&var->token);
	ft_parse(var->token, var->env);
	ft_display_token(var->token);
	var->instru = ft_set_instru(var->token);
	ft_cmd_validation(var);
	ft_exec_sys_func(var->instru, var);
	ft_lstclear_instru(&var->instru, &var->token);
	var->token = NULL;
	free(var->line);
}
