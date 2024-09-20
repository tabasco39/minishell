/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_by_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:34:47 by aelison           #+#    #+#             */
/*   Updated: 2024/09/20 14:05:48 by aranaivo         ###   ########.fr       */
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

int	ft_should_delete(char *line)
{
	int		i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '$')
			return (0);
	}
	return (1);
}
char	*ft_clean_quote(char *line)
{
	int		i;
	char	simple_quote;
	char	double_quote;
	char	*result;

	i = 0;
	simple_quote = (char)39;
	double_quote = (char)34;
	result = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == simple_quote && line[i + 1] == simple_quote)
		{
			result = ft_del_quote(line, &simple_quote);
			return (result);
		}
		else if (line[i] == double_quote && line[i + 1] == double_quote)
		{
			result = ft_del_quote(line, &double_quote);
			return (result);
		}
		i++;
	}
	return (line);
}

void	ft_div_by_token(char *line, t_token **head)
{
	char	**split;
	char	*newline;
	char	*tmp;
	int		i;

	i = 0;
	newline = ft_div_by_redirect(line, "<>|");
	split = ft_split_shell(newline, ' ');
	if (split == NULL || *split == NULL)
		return ;
	free(newline);
	newline = NULL;
	while (split[i])
	{
		newline = ft_get_first_quote(split[i]);
		if (ft_should_delete(split[i]) == 1)
		{
			tmp = ft_del_quote(split[i], newline);
			ft_add_token(head, ft_create_token(tmp));
			free(tmp);
		}
		else
			ft_add_token(head, ft_create_token(split[i]));
		free(newline);
		free(split[i]);
		i++;
	}
	free(split);
}
