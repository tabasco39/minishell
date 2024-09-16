/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:35:34 by aelison           #+#    #+#             */
/*   Updated: 2024/09/13 07:30:37 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

static void	ft_set_canonique(int set)
{
	struct termios	term;

	tcgetattr(0, &term);
	if (set == 0)
		term.c_lflag &= ~(ECHO | ICANON /*| ISIG*/);
	else
		term.c_lflag |= (ECHO | ICANON /*| ISIG*/);
	tcsetattr(0, TCSANOW, &term);
}

static void	ft_handle_arrows(t_read_line *line, char buff[])
{
	if (buff[0] == '\033')
	{
		if (buff[1] == '[')
		{
			if (buff[2] == 'A')			 //arrow up
			{
				printf("nie\n");
			}
			/*else if (buff[2] == 'B')	//arrow down
				write(1, buff, 3);*/
			if (buff[2] == 'C' && line->cur_pos < ft_strlen(line->result))			//arrow right
			{
				write(1, buff, 3);
				line->cur_pos++;
			}
			else if (buff[2] == 'D')	//arrow left
			{
				if (line->cur_pos > 0)
				{
					line->cur_pos--;
					write(1, buff, 3);
				}
			}
		}
	}
}

static void ft_handle_letter(t_read_line *line, char buff[])
{
	int				i;
	char			*tmp;
	unsigned long	pos;

	i = 0;
	if (buff[0] == (char)127 || buff[0] == (char)8)	//handle_back_space(delete prec letter)
	{
		if (line->cur_pos > 0)
		{
			pos = line->cur_pos - 1;
			line->cur_pos--;
			while (line->result[pos + 1] != '\0')
			{
				line->result[pos] = line->result[pos + 1];
				pos++;
			}
			line->result[pos] = '\0';
			write(1, "\033[D", 3);
			write(1, "\0337", 2);
			ft_putstr_fd(line->result + line->cur_pos, 1);
			write(1, " ", 1);
			write(1, "\0338", 2);
		}
	}
	else
	{
		if (line->cur_pos < ft_strlen(line->result))
		{
			tmp = ft_strdup(line->result + line->cur_pos);
			line->result[line->cur_pos] = buff[0];
			line->result[line->cur_pos + 1] = '\0';
			line->result = ft_strjoin_shell(line->result, tmp);
			write(1, "\0337", 2);
			ft_putstr_fd(line->result + line->cur_pos, 1);
			write(1, "\0338", 2);
			write(1, "\033[C", 3);
		}
		else
		{
			line->result = ft_strjoin_shell(line->result, buff);
			write(1, buff, 1);
		}
		line->cur_pos++;
	}
}

char	*ft_readline_de_moi(char *prompt)
{
	t_read_line	line;
	char	 buff[4];
	int		read_val;

	read_val = 1;
	line.cur_pos = 0;
	line.result = ft_strdup("\0");
	ft_putstr_fd("\x1b[32m", 1);	//green color
	ft_putstr_fd(prompt, 1);
	ft_putstr_fd("\x1b[0m", 1);
	ft_set_canonique(0);
	while (read_val != 0)
	{
		read_val = read(0, buff, 3);
		if (read_val <= 0 || buff[0] == '\n')	//when touch "enter", end of readline
			break ;
		buff[read_val] = '\0';
		if (read_val == 1)
			ft_handle_letter(&line, buff);
		if (read_val == 3)
			ft_handle_arrows(&line, buff);
	}
	ft_set_canonique(1);
	write(1, "\n", 1);
	return (line.result);
}
