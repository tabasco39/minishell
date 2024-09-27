/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:55:02 by aelison           #+#    #+#             */
/*   Updated: 2024/09/27 12:52:55 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	ft_display_command(t_comm cmd)
{
	printf("t_comm = ");
	if (cmd == argument)
		printf("argument");
	else if (cmd == option)
		printf("option");
	else if (cmd == env)
		printf("env");
	else if (cmd == pwd)
		printf("pwd");
	else if (cmd == cd)
		printf("cd");
	else if (cmd == echo)
		printf("echo");
	else if (cmd == unset)
		printf("unset");
	else if (cmd == dollar)
		printf("dollar");
	else if (cmd == question)
		printf("question");
	else if (cmd == e_export)
		printf("export");
	else if (cmd == e_exit)
		printf("exit");
	else if (cmd == e_pipe)
		printf("pipe");
	else if (cmd == redirect_input)
		printf("redirect_input : <");
	else if (cmd == redirect_output)
		printf("redirect_input : >");
	else if (cmd == delimiter_redirect_input)
		printf("delimiter_redir_input : <<");
	else if (cmd == append_redirect_output)
		printf("append_redir_output : >>");
	else if (cmd == not_comm)
		printf("not_comm");
	else if (cmd == in_sys)
		printf("in_sys");
	printf("\n\n");
}

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
		ft_display_command(token->command);
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

void	ft_display_env(t_list **env, char *before)
{
	t_list	*tmp;
	int		i;
	char	*to_print;
	int		count_char;

	tmp = *env;
	while (tmp)
	{
		i = 0;
		count_char = 0;
		to_print = (char *)tmp->content;
		if (before == NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			while (to_print[i] != '\0')
			{
				if (count_char == 1)
				{
					ft_putchar_fd((char)34, 1);
					count_char++;
				}
				if (to_print[i] == '=')
					count_char++;
				ft_putchar_fd(to_print[i], 1);
				i++;
			}
			if (count_char > 0)
				ft_putchar_fd((char)34, 1);
			ft_putchar_fd('\n', 1);
		}
		else
		{
			if (ft_find_char((char *)tmp->content, '=') != -1)
				printf("%s\n", (char *)tmp->content);
		}
		tmp = tmp->next;
	}
}

void	ft_debug(t_var *var)
{
	char	*test;

	var->path = ft_get_all_path(var->env, var->line);
	test = ft_verify_exec_cmd(var->path);
	if (ft_strncmp(var->line, "exit", 4) == 0)
		ft_exit(var, 0);
	ft_div_by_token(var->line, &var->token);
	ft_command_setup(&var->token);
	ft_parse(var, var->token);
	var->instru = ft_set_instru(var->token);
	//ft_cmd_validation(var);

	// if (var->token->command >= env && var->token->command <= e_exit)
	// 	ft_exec_builtin(var, var->instru->start, var->instru->end);
	//ft_display_token(var->token);
	ft_exec(var->instru, var);
	ft_lstclear_instru(&var->instru, &var->token);
	var->token = NULL;
	free(test);
	free(var->line);
}
