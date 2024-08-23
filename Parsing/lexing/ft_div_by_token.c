/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_by_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:34:47 by aelison           #+#    #+#             */
/*   Updated: 2024/08/23 06:46:38 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count_div(char *line, char div)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (line == NULL)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] == div)
			count++;
		i++;
	}
	return (count);
}

void	ft_redirect_aux(char *line, char div, int *j, int nb)
{
	int	start;

	line[*j] = ' ';
	*j = *j + 1;
	start = 0;
	while (start < nb)
	{
		line[*j] = div;
		*j = *j + 1;
		start++;
	}
	line[*j] = ' ';
}

char	*ft_edit(char *line, char *result, char div)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == div)
		{
			if (div != '|' && div != '$')
			{
				if (line[i + 1] == div)
				{
					ft_redirect_aux(result, div, &j, 2);
					i++;
				}
				else
					ft_redirect_aux(result, div, &j, 1);
			}
			else
				ft_redirect_aux(result, div, &j, 1);
		}
		else
			result[j] = line[i];
		j++;
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*ft_div_by_redirect(char *line, char div)
{
	char	*result;
	int		len;

	len = (ft_count_div(line, div) * 2) + strlen(line);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result = ft_edit(line, result, div);
	free(line);
	return (result);
}

void	ft_div_by_token(char *line, t_token **head)
{
	char	**split;
	char	*newline;
	int		i;

	i = 0;
	newline = ft_strdup(line);
	newline = ft_div_by_redirect(newline, '|');
	newline = ft_div_by_redirect(newline, 34);
	newline = ft_div_by_redirect(newline, 39);
	newline = ft_div_by_redirect(newline, '<');
	newline = ft_div_by_redirect(newline, '>');
	newline = ft_div_by_redirect(newline, '$');
	split = ft_split(newline, ' ');
	if (split == NULL || *split == NULL)
		return ;
	while (split[i])
	{
		ft_add_token(head, ft_create_token(split[i]));
		i++;
	}
	free(newline);
	ft_free_all(split);
}
