/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:32:17 by aelison           #+#    #+#             */
/*   Updated: 2024/08/28 11:36:09 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(t_list *env, char *prompt)
{
	char	*line;
	char	*buff;
	int		end;

	if (prompt)
	{
		ft_putstr_fd("\x1b[32m", 1);	//green color
		ft_putstr_fd(prompt, 1);
		ft_putstr_fd("\x1b[0m", 1);
	}
	else
	{
		ft_putstr_fd("\x1b[32m", 1);	//green color
		ft_putstr_fd(ft_getvar(env, "USER") + 5, 1);
		ft_putstr_fd("@minishell$ ", 1);
		ft_putstr_fd("\x1b[0m", 1);
	}
	buff = malloc(sizeof(char) * 10000);
	if (!buff)
		return (NULL);
	end = read(0, buff, 9999);
	buff[end] = '\0';
	line = ft_strdup_shell(buff);
	free(buff);
	return (line);
}
