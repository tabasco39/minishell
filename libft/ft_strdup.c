/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:34:30 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:34:32 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*result;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	len = ft_strlen(s);
	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = s[i];
		i = i + 1;
	}
	result[i] = '\0';
	return (result);
}
