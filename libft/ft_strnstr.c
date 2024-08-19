/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:35:57 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:35:58 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int	result;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if ((int)len < 0)
		len = ft_strlen(big);
	if (big[0] == '\0' && little[0] != '\0')
		return (NULL);
	while (i < (int)len)
	{
		if ((i + ft_strlen(little)) > len)
			return (NULL);
		result = ft_strncmp(big + i, little, ft_strlen(little));
		if (result == 0)
			return ((char *)(big + i));
		else
			i++;
	}
	return (NULL);
}
