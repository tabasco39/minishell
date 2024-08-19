/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:35:36 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:35:37 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	result = (char *)malloc(sizeof(char) * (ft_strlen((const char *)s) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		result[i] = (*f)(i, s[i]);
		i = i + 1;
	}
	result[i] = '\0';
	return (result);
}
