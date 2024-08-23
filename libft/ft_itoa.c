/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:27:23 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:27:25 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	len_nb(int nb)
{
	unsigned int	result;

	if (nb < 0)
	{
		result = 1;
		nb = nb * -1;
	}
	else
		result = 0;
	while (nb > 9)
	{
		result = result + 1;
		nb = nb / 10;
	}
	if (nb >= 0 && nb <= 9)
		result = result + 1;
	return (result);
}

static char	*negatif(char *result, int nb, int len)
{
	result[0] = '-';
	nb = nb * -1;
	while (len)
	{
		result[len] = (nb % 10) + '0';
		nb = nb / 10;
		len = len - 1;
	}
	return (result);
}

static char	*positif(char *result, int nb, int len)
{
	while (len)
	{
		result[len] = (nb % 10) + '0';
		nb = nb / 10;
		len = len - 1;
	}
	result[0] = nb + '0';
	return (result);
}

char	*ft_itoa(int nb)
{
	unsigned int	len;
	char			*result;

	len = len_nb(nb);
	if (nb == -2147483648)
	{
		result = ft_strdup("-2147483648");
		return (result);
	}
	else
	{
		result = ft_calloc(len + 1, sizeof(char));
		if (!result)
			return (NULL);
	}
	if (nb < 0)
		result = negatif(result, nb, len - 1);
	else
		result = positif(result, nb, len - 1);
	return (result);
}
