/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:51:45 by aelison           #+#    #+#             */
/*   Updated: 2024/08/13 13:37:44 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_in_word(char *word, int quote)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (!word)
		return (result);
	while (word[i] != '\0')
	{
		if (word[i] == (char)quote)
			result++;
		i++;
	}
	return (result);
}
