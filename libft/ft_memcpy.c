/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:28:05 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:28:07 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	tmp1 = (unsigned char *)dest;
	tmp2 = (unsigned char *)src;
	while (i < n)
	{
		tmp1[i] = tmp2[i];
		i = i + 1;
	}
	return (dest);
}
