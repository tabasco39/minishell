/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:59:12 by aelison           #+#    #+#             */
/*   Updated: 2024/09/26 12:54:39 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
static void	ft_echo_aux(char *to_print, int quote, int nb_quote)
{
	int	i;

	i = 0;
	nb_quote = 1;
	while (to_print[i] != '\0')
	{
		if (to_print[i] != quote)
			ft_putchar_fd(to_print[i], 1);
		i++;
	}
	if (nb_quote % 2 == 0 || nb_quote == 1)
	{
	}
	else if (nb_quote % 2 != 0)
	{
		while (to_print[i] == quote)
			i++;
		ft_putchar_fd(quote, 1);
		while (to_print[i] != quote && to_print[i])
		{
			ft_putchar_fd(to_print[i], 1);
			i++;
		}
		ft_putchar_fd(quote, 1);
	}
}
*/
void	ft_echo(char *to_print, char option)
{
	int		quote;
	int		i;
	//	int		nb_quote;

	i = 0;
	quote = ft_first_quote(to_print, 34, 39);
	if (quote == '\0' && to_print)
		ft_putstr_fd(to_print, 1);
	else if (quote != '\0' && to_print)
	{
		while (to_print[i] != '\0')
		{
			if (to_print[i] != quote)
				ft_putchar_fd(to_print[i], 1);
			i++;
		}

		//nb_quote = ft_is_char_pair(to_print, quote);
		//ft_echo_aux(to_print, quote, nb_quote);
	}
	if (option == '\n')
		ft_putchar_fd('\n', 1);
}

char	*ft_pwd(void)
{
	char	directory[1024];
	char	*result;

	result = getcwd(directory, sizeof(directory));
	if (result == NULL)
	{
		ft_putstr_fd("error : getcwd\n", 2);
		return (NULL);
	}
	return (result);
}

int	ft_cd(char *path)
{
	if (chdir(path) == -1)
		return (-1);
	return (0);
}
