/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:43:40 by aranaivo          #+#    #+#             */
/*   Updated: 2024/09/16 10:09:55 by aranaivo         ###   ########.fr       */
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
	result = malloc(sizeof(char *) * (ft_count_token_in_instru(current) + 1));
	while (i < ft_count_token_in_instru(current))
	{
		result[i] = tmp->token;
		if (tmp->command >= redirect_input && tmp->command <= append_redirect_output)
		{
			result[i] = NULL;
			return (result);
		}
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


static t_token *ft_find_cmd_token(t_instru *instru)
{
	t_token *result;
	int		i;

	result = instru->start;
	i = ft_count_token_in_instru(instru);
	while (i > 0)
	{
		if (result->command >= redirect_input && result->command <= append_redirect_output)
			return (result);
		i--;
		result = result->next;
	}
	return (NULL);
}



void	ft_exec_sys_func(t_instru *instruction, t_var *var)
{
	t_instru	*tmp;
	t_token		*target;
	t_token		*last_token;
	char		**params;
	char		**all_path;
	char		*path;
	char		*here_doc_result;
	int			start;
	int			end;
	int			input_fd;
	int			i;

	input_fd = STDIN_FILENO;
	start = 0;
	i = 0;
	end = ft_count_pipe(var->token);
	tmp = instruction;
	path = NULL;
	here_doc_result = ft_strdup_shell("");
	while (tmp)
	{
		int	pipefd[2];
		target = ft_find_cmd_token(tmp);
		if (i != end)
			pipe(pipefd);
		pid_t pid = fork();
		if (pid == 0)
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
			if (target != NULL)
			{
				last_token = instruction->end;
				while (last_token != target->prev)
				{
					if (last_token->command == redirect_output)
					{
						input_fd = open(last_token->next->token, O_CREAT | O_RDWR | O_TRUNC , S_IRWXU);
						dup2(3, STDOUT_FILENO);
					}
					if (last_token->command == append_redirect_output)
					{
						input_fd = open(last_token->next->token, O_CREAT | O_RDWR | O_APPEND , S_IRWXU);
						dup2(3, STDOUT_FILENO);
					}
					if (last_token->command == redirect_input)
					{
						input_fd = open(last_token->next->token,O_RDONLY);
						dup2(3, STDIN_FILENO);
					}
					if (last_token->command == delimiter_redirect_input)
					{
						char 	buffer[1024];
						int		here_doc_fd[2];
						while (1)
						{
							ft_putstr_fd(">", STDIN_FILENO);
							int bytes_read = read(0, buffer, 1023);
							if (bytes_read > 1)
								buffer[bytes_read - 1] = '\0';
							else
								buffer[bytes_read] = '\0';
							if (ft_strncmp(last_token->next->token, buffer, ft_strlen(buffer)) != 0)
							{
								if (bytes_read > 1)
								{
									here_doc_result = ft_strjoin_shell(here_doc_result, buffer);
									here_doc_result = ft_strjoin_shell(here_doc_result, "\n");
								}
								else
									here_doc_result = ft_strjoin_shell(here_doc_result, buffer);
							}
							else
								break;
						}
						pipe(here_doc_fd);
						if (here_doc_result)
						{
							ft_putstr_fd(here_doc_result, here_doc_fd[1]);
							close(here_doc_fd[1]);
							//free(here_doc_result);
						}
						dup2(here_doc_fd[0], STDIN_FILENO);
						close(here_doc_fd[0]);
					}
					last_token = last_token->prev;
				}
				while(input_fd > 2)
				{
					close(input_fd);
					input_fd--;
				}
			}
			params = ft_get_execve_parameter(tmp);
			all_path = ft_get_all_path(var->env, params[0]);
			path	= ft_verify_exec_cmd(all_path);
			execve(path, params, var->tab_env);
		}
		waitpid(pid, NULL, 0);
		if (i != start)
			close(input_fd);
		if (i != end)
		{
			close(pipefd[1]);
			input_fd = pipefd[0];
		}
		i++;
		tmp = tmp->next;
	}
	free(here_doc_result);
	tmp = instruction;
	while (tmp)
	{
		wait (NULL);
		tmp = tmp->next;
	}
}
