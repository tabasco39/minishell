/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:35:34 by aelison           #+#    #+#             */
/*   Updated: 2024/08/29 07:16:32 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	ft_set_canonique(int set)
{
	struct termios	term;

	tcgetattr(0, &term);
	if (set == 0)
		term.c_lflag &= ~(ECHO | ICANON /*| ISIG*/);
	else
		term.c_lflag |= (ECHO | ICANON /*| ISIG*/);
	tcsetattr(0, TCSANOW, &term);
}

void	ft_handle_arrows(char buff[])
{
	if (buff[0] == '\033')
	{
		write(1, buff, 3);
	}
}

int	main(void)
{
	char	 buff[3];
	int		read_val;
	int		i;

	ft_set_canonique(0);
	read_val = 1;
	while (read_val != 0)
	{
		i = 0;
		read_val = read(0, buff, 3);
		if (read_val <= 0 || buff[0] == 'x')
			break ;
		buff[read_val] = '\0';
		if (read_val == 1)
			write(1, buff, 1);
		else
			ft_handle_arrows(buff);
	}
	ft_set_canonique(1);
	return (0);
}
