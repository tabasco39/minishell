/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-13 11:14:07 by aelison           #+#    #+#             */
/*   Updated: 2024/09/23 15:01:02 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_history_stack(t_history **stack)
{
	int		fd;
	char	*line;

	line = "";
	fd = open("history", O_CREAT | O_APPEND | O_RDWR , S_IRWXU);
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line)
		{
			ft_add_node_history(stack, ft_create_node_history(line));
			free(line);
		}
	}
	close(fd);
}

void	ft_add_history(char *to_add, t_history **stack)
{
	int		fd;

	if (to_add && to_add[0] != '\0')
	{
		fd = open("history", O_CREAT | O_APPEND | O_RDWR , S_IRWXU);
		ft_putendl_fd(to_add, fd);
		close(fd);
		ft_add_node_history(stack, ft_create_node_history(to_add));
	}
}
