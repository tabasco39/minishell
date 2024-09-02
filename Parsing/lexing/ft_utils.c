/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:59:05 by aranaivo          #+#    #+#             */
/*   Updated: 2024/08/30 07:52:31 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count_quote(char *str, char *to_count)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_find_char(to_count, str[i]) != -1)
			count++;
		i++;
	}
	return (count);
}

void	ft_check_quote(char *str, int *is_dquote, int *is_squote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)34)
		{
			i++;
			(*is_dquote)++;
			while (str[i] && str[i] != (char)34)
				i++;
			if (str[i] && str[i] == (char)34)
				(*is_dquote)++;
		}
		else if (str[i] == (char)39)
		{
			i++;
			(*is_squote)++;
			while (str[i] && str[i] != (char)39)
				i++;
			if (str[i] && str[i] == (char)39)
				(*is_squote)++;
		}
		i++;
	}
}

char	*ft_get_to_removes(int is_dq, int is_sq)
{
	char	*result;

	result = malloc(sizeof(char) * 3);
	if (!result)
		return (NULL);
	if ((is_sq != 0 && is_dq != 0) && (is_sq % 2 == 0 && is_dq % 2 == 0))
	{
		result[0] = (char)34;
		result[1] = (char)39;
		result[2] = '\0';
		return (result);
	}
	if (is_dq != 0 && is_dq % 2 == 0)
	{
		result[0] = (char)34;
		result[1] = '\0';
		return (result);
	}
	if (is_sq != 0 && is_sq % 2 == 0)
	{
		result[0] = (char)39;
		result[1] = '\0';
		return (result);
	}
	free(result);
	return (NULL);
}

char	*ft_get_first_quote(char *str)
{
	int		is_squote;
	int		is_dquote;
	char	*result;

	is_dquote = 0;
	is_squote = 0;
	ft_check_quote(str, &is_dquote, &is_squote);
	result = ft_get_to_removes(is_dquote, is_squote);
	return (result);
}

char	*ft_del_quote(char *word, char *quote)
{
	int		i;
	int		j;
	int		len;
	int		nb_quote;
	char	*result;

	nb_quote = ft_count_quote(word, quote);
	len = ft_strlen(word) - nb_quote + 1;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (word[i] != '\0')
	{
		while (ft_find_char(quote, word[i]) != -1 && word[i] != '\0')
			i++;
		result[j] = word[i];
		j++;
		if (word[i] != '\0')
			i++;
	}
	result[j] = '\0';
	return (result);
}
