/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:43:40 by aranaivo          #+#    #+#             */
/*   Updated: 2024/09/02 15:17:32 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**ft_get_execve_parameter(t_instru *current)
{
	t_token	*tmp;
	char	**result;
	int		i;

	i = 0;
	tmp = current->start;
	result = malloc(sizeof(char *) * ft_count_token_in_instru(current) + 1);
	while (i < ft_count_token_in_instru(current))
	{
		result[i] = tmp->token;
		i++;
		tmp = tmp->next;
	}
	result[i] = NULL;
	return (result);
}

static int	ft_count_pipe(t_token *token)
{
	t_token *tmp;
	int		count;

	tmp = token;
	count = 0;
	while (tmp)
	{
		if (tmp->command == e_pipe)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	ft_exec_sys_func(t_instru *instruction, t_var *var)
{
	t_instru	*tmp;
	char		**params;
	char		**all_path;
	char		*path;
	int			start;
	int			end;
	int			input_fd;
	int			i;


	input_fd = STDERR_FILENO;
	start = 0;
	i = 0;
	end = ft_count_pipe(var->token) - 1;
	tmp = instruction;
	while (tmp)
	{
		int			pipefd[2];
		if (i != end)
			pipe(pipefd);
		if (fork() == 0)
		{
			if (i != start)
			{
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}
			if (i != end)
			{
				dup2(pipefd[1] , STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			params = ft_get_execve_parameter(tmp);
			all_path = ft_get_all_path(var->env, params[0]);
			path	= ft_verify_exec_cmd(all_path);
			execve(path, params, var->tab_env);
		}
		if (i != start)
			close(input_fd);
		if (i != end)
		{
			close(pipefd[1]);
			input_fd = pipefd[0];
		}
		// params = ft_get_execve_parameter(tmp);
		// all_path = ft_get_all_path(var->env, params[0]);
		// path	= ft_verify_exec_cmd(all_path);
		// execve(path, params, var->tab_env);
		i++;
		tmp = tmp->next;
	}
	wait(NULL);
}
