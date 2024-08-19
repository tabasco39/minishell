/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:36:25 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:36:33 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*substr_aux(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while ((i < len) && s[i] != '\0')
	{
		result[i] = s[start];
		start = start + 1;
		i = i + 1;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	len_s;

	len_s = ft_strlen((const char *)s);
	i = 0;
	if (len > len_s - start)
		len = len_s - start;
	if (start >= len_s)
	{
		result = (char *)malloc(sizeof(char) * 1);
		if (!result)
			return (NULL);
		result[i] = '\0';
		return (result);
	}
	else
		result = substr_aux(s, start, len);
	return (result);
}
