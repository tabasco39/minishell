/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:34:20 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:34:22 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len_s;
	char	*addr;

	i = 0;
	len_s = ft_strlen(s);
	addr = (char *)s;
	if ((char)c == '\0')
		return (addr + len_s);
	while (addr[i] != '\0')
	{
		if (addr[i] == (char)c)
			return (addr + i);
		i = i + 1;
	}
	return (NULL);
}
