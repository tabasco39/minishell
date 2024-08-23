/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:35:05 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:35:06 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	len_src;
	unsigned int	len_dest;

	i = 0;
	len_src = ft_strlen(src);
	len_dest = ft_strlen(dest);
	if (size > len_dest)
	{
		while (src[i] != '\0' && size > len_dest + 1)
		{
			dest[len_dest + i] = src[i];
			i = i + 1;
			size = size - 1;
		}
		dest[len_dest + i] = '\0';
	}
	else
		return (size + len_src);
	return (len_src + len_dest);
}
