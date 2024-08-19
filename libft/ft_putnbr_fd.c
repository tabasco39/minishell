/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:30:30 by aelison           #+#    #+#             */
/*   Updated: 2024/07/31 07:30:31 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			n = n * -1;
			ft_putchar_fd('-', fd);
		}
		if (n >= 0 && n <= 9)
			ft_putchar_fd(n + '0', fd);
		else
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putchar_fd((n % 10) + '0', fd);
		}
	}
}
