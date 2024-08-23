/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:28:16 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:28:17 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_last_aux(unsigned char *p1, unsigned char *p2, size_t n)
{
	while (n)
	{
		n = n - 1;
		p1[n] = p2[n];
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	size_t			i;

	tmp1 = (unsigned char *)dest;
	tmp2 = (unsigned char *)src;
	i = 0;
	if ((dest == NULL) && (src == NULL))
		return (NULL);
	if (src < dest)
		ft_last_aux(tmp1, tmp2, n);
	else
	{
		while (i < n)
		{
			tmp1[i] = tmp2[i];
			i = i + 1;
		}
	}
	return (dest);
}
