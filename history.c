/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.mg>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-13 11:14:07 by aelison           #+#    #+#             */
/*   Updated: 2024-09-13 11:14:07 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_history(char *to_add)
{
	int	fd;

	fd = open("history", O_CREAT | O_APPEND | O_RDWR , S_IRWXU);
	ft_putendl_fd(to_add, fd);
	close(fd);
}