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
			if (nxt && nxt->command == option)
				nxt = nxt->next;
			while (nxt && (nxt->command == not_comm || nxt->command == option))
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

static int	ft_replace_aux(char *result, int *j, t_list *env, char *to_replace)
{
	int		i;
	char	*search;
	char	*value;

	i = 0;
	while (to_replace[i] == '$')
		i++;
	while (ft_isalpha(to_replace[i]) != 0)
		i++;
	search = ft_substr(to_replace, 0, i);
	value = ft_getvar(env, search + 1);
	if (value == NULL)
		result[*j] = ' ';
	else
	{
		value += (ft_find_char(value, '=') + 1);
		while (*value != '\0')
		{
			result[*j] = *value;
			(*j)++;
			value++;
		}
	}
	free(search);
	return (i);
}

static char	*ft_replace_word(char *to_replace, t_list *env, int start)
{
	char	*result;
	int		i;
	int		j;

	result = ft_calloc(ft_strlen(to_replace) + 1000, sizeof(char));
	if (!result || !to_replace || !env)
	{
		free(to_replace);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (to_replace[i] != '\0')
	{
		if (i == start)
			i += ft_replace_aux(result, &j, env, to_replace + i);
		result[j] = to_replace[i];
		j++;
		if (to_replace[i] != '\0')
			i++;
	}
	free(to_replace);
	return (result);
}

void	ft_parse_dollar(t_token *current, t_list *env)
{
	char	first_quote;
	int		pos_char;

	first_quote = ft_first_quote(current->token, 34, 39);
	pos_char = ft_find_char(current->token, '$');
	if (first_quote == -1)
	{
		if (current->command == dollar && ft_strlen(current->token) != 1)
		{
			current->token = ft_replace_word(current->token, env, pos_char);
			if (current->is_head == 1)
				current->command = not_comm;
			else
				current->command = argument;
		}
	}
	else
	{
		if (first_quote == 39)
			return ;
		else
			current->token = ft_replace_word(current->token, env, pos_char);
	}
}
