/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:36:08 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:36:09 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*ptr;
	char			*result;

	i = 0;
	ptr = (char *)s;
	result = NULL;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == (char)c)
			result = ptr + i;
		i = i + 1;
	}
	if ((char)c == '\0')
	{
		result = ptr + i;
	}
	return (result);
}
