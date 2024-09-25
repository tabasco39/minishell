/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.mg>  #+#  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-23 05:24:56 by aelison           #+#    #+#             */
/*   Updated: 2024/09/25 07:18:37 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_div_aux(char *result, char div, int *j, int nb)
{
	result[*j] = ' ';
	*j = *j + 1;
	while (nb)
	{
		result[*j] = div;
		*j = *j + 1;
		nb--;
	}
	result[*j] = ' ';
}

void	ft_edit(char *line, int *i, char *result, int *j)
{
	if (line[*i + 1] == line[*i] && line[*i + 1])
	{
		ft_div_aux(result, line[*i], j, 2);
		(*i)++;
	}
	else
		ft_div_aux(result, line[*i], j, 1);
}

char	*ft_div_by_redirect(char *line, char *ref)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(line) + ft_count_quote(line, ref) * 2;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (ft_find_char(ref, line[i]) != -1)
			ft_edit(line, &i, result, &j);
		else
			result[j] = line[i];
		j++;
		i++;
	}
	result[j] = '\0';
	return (result);
}
