/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_by_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:34:47 by aelison           #+#    #+#             */
/*   Updated: 2024/08/19 07:47:08 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_div(char *line, char div)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (line == NULL)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] == div)
			count++;
		i++;
	}
	return (count);
}

void	ft_div_aux(char *res, char div, int *j)
{
	res[*j] = ' ';
	(*j) = (*j) + 1;
	res[*j] = div;
	(*j) = (*j) + 1;
	res[*j] = ' ';
}

char	*ft_div(char *line, char div)
{
	char	*res;
	int		nb;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nb = (ft_count_div(line, div) * 2) + ft_strlen(line);
	res = malloc(sizeof(char) * (nb + 1));
	if (!res)
		return (NULL);
	while (line[i] != '\0')
	{
		if (line[i] == div)
			ft_div_aux(res, div, &j);
		else
			res[j] = line[i];
		j++;
		i++;
	}
	res[j] = '\0';
	free(line);
	return (res);
}

void	ft_div_by_token(char *line, t_token **head)
{
	char	**split;
	char	*newline;
	int		i;

	i = 0;
	newline = ft_strdup(line);
	if (ft_find_char(newline, '|') != -1)
		newline = ft_div(newline, '|');
	if (ft_find_char(newline, 34) != -1)
		newline = ft_div(newline, 34);
	if (ft_find_char(newline, 39) != -1)
		newline = ft_div(newline, 39);
	split = ft_split(newline, ' ');
	if (split == NULL || *split == NULL)
		return ;
	while (split[i])
	{
		ft_add_token(head, ft_create_token(split[i]));
		i++;
	}
	free(newline);
	ft_free_all(split);
}
