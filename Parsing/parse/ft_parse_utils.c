/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:13:08 by aelison           #+#    #+#             */
/*   Updated: 2024/08/30 07:47:07 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parse_arg(t_token *current, t_token *nxt)
{
	if (current->command >= cd && current->command <= e_exit)
	{
		if (nxt == NULL)
			return ;
		else
		{
			if (nxt->command == option)
				nxt = nxt->next;
			while (nxt && ((nxt->command == not_comm) || (nxt->command == option)))
			{
				nxt->command = argument;
				nxt = nxt->next;
			}
		}
	}
}

void	ft_redirection(t_token *current, t_token *nxt)
{
	if (current->command >= redirect_input
		&& current->command <= append_redirect_output)
	{
		if (nxt)
			nxt->command = argument;
	}
}

static int	ft_replace_word_aux(char *result, int *j, char *line, t_list *env)
{
	int		end;
	int		start;
	char	*value;
	char	*env_variable;

	end = 1;
	while (ft_isalpha(line[end]) != 0 || line[end] == '_')
		end++;
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
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * 1000);
	if (!result)
		return (NULL);
	while (line[i] != '\0')
	{
		if (line[i] == (char)36)
			i += ft_replace_word_aux(result, &j, line + i, env);
		else
			result[j] = line[i];
		j++;
		i++;
	}
	result[j] = '\0';
	free(line);
	return (result);
}

static int	ft_is_char_pair(char *line, char quote)
{
	int	i;

	i = 0;
	while (line[i] != quote)
		i++;
	while (line[i] == quote)
		i++;
	return (i);
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
