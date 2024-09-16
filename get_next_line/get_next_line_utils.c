/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:10:27 by aelison           #+#    #+#             */
/*   Updated: 2024/08/21 06:45:49 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup_gnl(char *str)
{
	char	*res;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	res = malloc(sizeof(char) * ft_strlen_gnl(str) + 1);
	if (!res)
		return (NULL);
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_substr_gnl(char *str, int end)
{
	char	*res;
	int		i;

	if (str == NULL)
		return (NULL);
	res = malloc(sizeof(char) * end + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (i <= end)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin_gnl(char *first, char *second)
{
	char	*res;
	int		i;
	int		j;
	int		len_f;
	int		len_s;

	len_f = ft_strlen_gnl(first);
	len_s = ft_strlen_gnl(second);
	res = malloc(sizeof(char) * len_f + len_s + 1);
	if (!res)
		return (res);
	i = -1;
	j = -1;
	while (++i < len_f)
		res[i] = first[i];
	while (++j < len_s)
		res[i++] = second[j];
	free(first);
	res[i] = '\0';
	return (res);
}

int	ft_end_of_line(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
