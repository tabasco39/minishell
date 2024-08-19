/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:27:43 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:27:44 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*result;
	char	find;

	i = 0;
	find = (char)c;
	result = (char *)s;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (result[i] == find)
			return ((void *)result + i);
		i = i + 1;
	}
	return (NULL);
}
