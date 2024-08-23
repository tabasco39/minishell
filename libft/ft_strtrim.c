/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:36:17 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:36:19 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	i_start(char const *p1, char const *p2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (p1[i] != '\0')
	{
		j = 0;
		while (p2[j] != '\0' && p1[i] != p2[j])
		{
			j = j + 1;
		}
		if (p2[j] == '\0')
			return (i);
		i = i + 1;
	}
	return (i);
}

static size_t	i_last(char const *p1, char const *p2)
{
	size_t	i;
	size_t	j;

	if (ft_strlen((const char *)p1) == 0)
		return (0);
	i = ft_strlen((const char *)p1) - 1;
	while (i)
	{
		j = 0;
		while (p2[j] != '\0' && p1[i] != p2[j])
			j = j + 1;
		if (p2[j] == '\0')
			return (i);
		i = i - 1;
	}
	return (i);
}

static char	*strtrim_aux(char const *s1, size_t i, size_t j)
{
	char	*result;
	size_t	k;

	result = (char *)malloc(sizeof(char) * (j - i + 1 + 1));
	if (!result)
		return (NULL);
	k = 0;
	while (i <= j)
	{
		result[k] = s1[i];
		i = i + 1;
		k = k + 1;
	}
	result[k] = '\0';
	return (result);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = i_start(s1, set);
	j = i_last(s1, set);
	if ((set[0] == '\0' && s1[0] == '\0') || s1[0] == '\0')
	{
		result = ft_strdup("\0");
		return (result);
	}
	if (i > j)
	{
		result = ft_strdup("\0");
		return (result);
	}
	result = strtrim_aux(s1, i, j);
	return (result);
}
