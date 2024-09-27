/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:35:34 by aelison           #+#    #+#             */
/*   Updated: 2024/09/25 13:40:20 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <termios.h>

/*Passer le terminal en mode canonique 
 * pour traiter chaque touche de l'utilisateur
*/
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

char	ft_get_pos_cursor()
{
	char	buff[7];
	char	tmp;
	int		byte;
	int		i;

	i = 0;
	write(1, "\033[6n", 4);
	while (1)
	{
		byte = read(STDOUT_FILENO, &tmp, 1);
		if (byte <= 0 || tmp == 'R')
			break ;
		buff[i] = tmp;
		i++;
	}
	buff[i] = '\0';
	return (buff[2]);
}

/*Cherche les occurences possibles : auto-completion*/
char	*ft_grep(char *to_search, char *file)
{
	char	*res;
	char	*join;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	res = "";
	join = ft_strdup("\0");
	while (res != NULL)
	{
		res = get_next_line(fd);
		if (res)
		{
			if (ft_strncmp(res, to_search, ft_strlen(to_search)) == 0)
				join = ft_strjoin_shell(join, res);
			free(res);
		}
	}
	return (join);
}

static void ft_handle_letter(t_read_line *line, char buff[])
{
	int				i;
	char			*tmp;
	unsigned long	pos;

	i = 0;
	if (buff[0] == (char)127 || buff[0] == (char)8)
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
		if (ft_strncmp(buff, "\t", 1) != 0)
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
	free(line->old_result);
	line->old_result = ft_strdup(line->result);
}

static void	ft_handle_arrows(t_read_line *line, char buff[],
							 t_history **history, int *pos_history)
{
	char	*tmp;
	char	test;

	tmp = NULL;
	if (buff[0] == '\033' && buff[1] == '[')
	{
		if (buff[2] == 'A' && (*history))			 //arrow up
		{
			if (*pos_history != 0)
			{
				if ((*history)->prev)
					*history = (*history)->prev;
			}
			while (line->cur_pos != 0)
			{
				write(1, "\033[D", 3);
				write(1, " ", 1);
				write(1, "\033[D", 3);
				line->cur_pos--;
			}
			free(line->result);
			line->result = ft_strdup_shell((*history)->line);
			ft_putstr_fd(line->result, 1);
			line->cur_pos += ft_strlen(line->result);
			(*pos_history)--;
			test = ft_get_pos_cursor();
			write(1, &test, 1);
			}
		else if (buff[2] == 'B' && (*history))	//arrow down
		{
			if ((*history)->next != NULL)
			{
				(*history) = (*history)->next;
				tmp = ft_strdup_shell((*history)->line);
			}
			else
				tmp = ft_strdup(line->old_result);
			while (line->cur_pos != 0)
			{
				write(1, "\033[D", 3);
				write(1, " ", 1);
				write(1, "\033[D", 3);
				line->cur_pos--;
			}
			free(line->result);
			line->result = ft_strdup_shell(tmp);
			ft_putstr_fd(line->result, 1);
			line->cur_pos += ft_strlen(line->result);
			(*pos_history)++;
		}
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
	else
		ft_handle_letter(line, buff);
}


char	*ft_readline_de_moi(char *prompt, t_history **history)
{
	t_read_line	line;
	char	 buff[4];
	int		read_val;
	int		pos_history;

	pos_history = 0;
	read_val = 1;
	line.cur_pos = 0;
	line.result = ft_strdup("\0");
	line.old_result = ft_strdup("\0");
	ft_putstr_fd(prompt, 1);
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
			ft_handle_arrows(&line, buff, history, &pos_history);
	}
	ft_set_canonique(1);
	write(1, "\n", 1);
	free(line.old_result);
	return (line.result);
}
