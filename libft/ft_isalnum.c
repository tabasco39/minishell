/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:21:24 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:21:29 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (8);
	else if (c >= 'A' && c <= 'Z')
		return (8);
	else if (c >= 'a' && c <= 'z')
		return (8);
	else
		return (0);
}
