/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:30:14 by aelison           #+#    #+#             */
/*   Updated: 2024/08/19 07:03:52 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_char(char *token, char to_find)
{
	int	result;

	result = 0;
	if (!token)
		return (-1);
	while (token[result] != '\0')
	{
		if (token[result] == to_find)
			return (result);
		result++;
	}
	return (-1);
}

char	*ft_strdup_shell(char *s)
{
	char			*result;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	len = ft_strlen(s);
	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	while (i < len && s[i] != '\n')
	{
		result[i] = s[i];
		i = i + 1;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin_shell(char *first, char *second)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(sizeof(char) * (ft_strlen(first) + ft_strlen(second) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (first[i] != '\0')
	{
		result[i] = first[i];
		i++;
	}
	j = 0;
	while (second[j] != '\0')
	{
		result[i + j] = second[j];
		j++;
	}
	result[i + j] = '\0';
	free(first);
	return (result);
}

void	ft_lstclear_shell(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = *head;
		(*head) = (*head)->next;
		free(tmp->token);
		free(tmp);
	}
	*head = NULL;
}

void	ft_free_all(char **split)
{
	int	i;

	i = 0;
	if (*split != NULL)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}
