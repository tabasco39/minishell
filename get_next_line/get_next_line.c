/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 07:29:48 by aelison           #+#    #+#             */
/*   Updated: 2024/08/21 06:50:49 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *str)
{
	char	*res;
	int		ind;

	ind = ft_end_of_line(str);
	if (ind == -1)
		res = ft_strdup_gnl(str);
	else
		res = ft_substr_gnl(str, ind);
	return (res);
}

char	*get_remains(char *str)
{
	char	*res;
	int		ind;

	ind = ft_end_of_line(str);
	if (ind == -1)
	{
		free(str);
		return (NULL);
	}
	else
		res = ft_strdup_gnl(str + ind + 1);
	free(str);
	return (res);
}

char	*read_all_aux(int fd, int *read_val, char *buff)
{
	char	*result;

	result = ft_strdup_gnl("\0");
	while (*read_val != 0)
	{
		*read_val = read(fd, buff, BUFFER_SIZE);
		if (*read_val <= 0)
			break ;
		buff[*read_val] = '\0';
		result = ft_strjoin_gnl(result, buff);
		if (ft_end_of_line(buff) != -1)
			break ;
	}
	return (result);
}

char	*read_all(int fd)
{
	char	*buff;
	char	*store;
	int		read_val;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	read_val = 1;
	store = read_all_aux(fd, &read_val, buff);
	if (read_val <= 0 && store[0] == '\0')
	{
		free(buff);
		free(store);
		return (NULL);
	}
	free(buff);
	return (store);
}

char	*get_next_line(int fd)
{
	char		*result;
	char		*read_str;
	static char	*remain;

	if (remain != NULL)
	{
		result = get_line(remain);
		remain = get_remains(remain);
		return (result);
	}
	read_str = read_all(fd);
	if (read_str == NULL)
		return (NULL);
	else
	{
		result = get_line(read_str);
		remain = get_remains(read_str);
	}
	return (result);
}
