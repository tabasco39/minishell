/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:43:40 by aranaivo          #+#    #+#             */
/*   Updated: 2024/08/14 10:04:41 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_exec_sys_func(char *paths, char **cmd_list, char **envp)
{
    pid_t   pid;

    pid = fork();

    if (pid == 0)
    {
        execve(paths, cmd_list, envp);
    }
    else if (pid > 0)
        wait(NULL);
}