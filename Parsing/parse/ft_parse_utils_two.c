/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelison <aelison@student.42antananarivo.m  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 06:43:46 by aelison           #+#    #+#             */
/*   Updated: 2024/09/25 07:18:11 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*TO DO : expand $? and $$*/
static int	ft_replace_word_aux(char *result, int *j, char *line, t_list *env)
{
	int		end;
	int		start;
	char	*value;
	char	*env_variable;

	end = 1;
	while (ft_isalpha(line[end]) != 0 || line[end] == '_')
		end++;
	if (end == 1)
		return (0);
	env_variable = ft_substr(line, 1, end - 1);
	value = ft_getvar(env, env_variable);
	if (value)
	{
		start = ft_find_char(value, '=');
		while (value[++start] != '\0')
		{
			result[*j] = value[start];
			(*j)++;
		}
	}
	else
		result[*j] = '\n';
	(*j)--;
	end--;
	free(env_variable);
	return (end);
}

static char	*ft_replace_word_new(char *line, t_list *env)
{
	int		i;
	int		j;
	int		value;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * 1000);
	if (!result)
		return (NULL);
	while (line[i] != '\0')
	{
		if (line[i] == (char)36)
		{
			value = ft_replace_word_aux(result, &j, line + i, env);
			i += value;
			if (value != 0)
				j++;
		}
		else
		{
			result[j] = line[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	free(line);
	return (result);
}

void	ft_parse_dollar(t_token *current, t_list *env)
{
	char	first_quote;
	int		nb_quote;

	if (ft_find_char(current->token, '$') == -1)
		return ;
	first_quote = ft_first_quote(current->token, 34, 39);
	if (first_quote == -1)
	{
		current->token = ft_replace_word_new(current->token, env);
		if (current->is_head == 1)
			current->command = not_comm;
		else
			current->command = argument;
	}
	else
	{
		if (first_quote == 39)
		{
			nb_quote = ft_is_char_pair(current->token, first_quote);
			if (nb_quote % 2 == 0)
				current->token = ft_replace_word_new(current->token, env);
		}
		else
			current->token = ft_replace_word_new(current->token, env);
	}
}
