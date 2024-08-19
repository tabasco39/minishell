/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:21:07 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:51:42 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*result;
	size_t	i;

	i = 0;
	if (size != 0 && nmemb > ((size_t) - 1 / size))
		return (NULL);
	result = malloc(size * nmemb);
	if (!result)
		return (NULL);
	while (i < nmemb * size)
	{
		result[i] = 0;
		i = i + 1;
	}
	return ((void *)result);
}
