/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:57:29 by aelison           #+#    #+#             */
/*   Updated: 2024/09/27 13:18:05 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_get_before_dollar(char *ref)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("\0");
	if (!ref)
		return (result);
	i = ft_find_char(ref, '$');
	if (i != 0)
	{
		free(result);
		result = ft_substr(ref, 0, i);
	}
	return (result);
}

static char	*ft_get_after_dollar(char *ref)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = ft_strdup("\0");
	if (!ref)
		return (result);
	i = ft_find_char(ref, '$');
	while (ref[i + j] && ref[i + j] != ' ' && ref[i + j] != (char)34 && ref[i + j] != (char)39)
		j++;
	if (j == 0)
		return (result);
	else
	{
		free(result);
		result = ft_strdup(ref + (i + j));
	}
	return (result);
}

static char	*ft_get_dollar_input(char *ref)
{
	char	*result;
	int		i;
	int		j;

	j = 0;
	result = ft_strdup("\0");
	if (!ref)
		return (result);
	i = ft_find_char(ref, '$');
	while (ref[i + j] && ref[i + j] != ' ' && ref[i + j] != (char)34 && ref[i + j] != (char)39 && ref[i + j] != '\n')
		j++;
	if (j == 0)
		return (result);
	else
	{
		free(result);
		result = ft_substr(ref, i, j);
	}
	return (result);
}


static char	*ft_replace_dollar(t_var *var, char *to_change)
{
	char	*result;

	if (to_change[1] == '\0')
		return (to_change);
	else
	{
		if (ft_isalpha(to_change[1]) == 0)
		{
			/*if (to_change[1] == '?')
			{

			}
			else if (to_change[1] == '$')
			{

			}*/
			if (to_change[1] == (char)34 || to_change[1] == (char)39)
				result = ft_strdup(to_change + 1);
			else
				result = ft_strdup(to_change + 2);
		}
		else
		{
			result = ft_getvar(var->env, to_change + 1);
			if (result)
				result = result + ft_find_char(result, '=') + 1;
			else
				result = ft_strdup("\0");
		}
	}
	return (result);
}

void	ft_parse_dollar_up(t_var *var, char **to_change)
{
	char	quote_ref;
	char	*result;
	char	*dollar_input;
	char	*after_dollar;

	if (ft_find_char(*to_change, '$') == -1)
		return ;
	quote_ref = ft_first_quote(*to_change, (char)34, (char)39);
	result = ft_get_before_dollar(*to_change);
	dollar_input = ft_get_dollar_input(*to_change);
	after_dollar = ft_get_after_dollar(*to_change);
	if (quote_ref == '\0')
	{
		result = ft_strjoin_shell(result, ft_replace_dollar(var, dollar_input));
		result = ft_strjoin_shell(result, after_dollar);
	}
	else
	{
		if (quote_ref == (char)39)
		{
			free(result);
			result = ft_strdup(*to_change);
		}
		else
		{
			result = ft_strjoin_shell(result, ft_replace_dollar(var, dollar_input));
			result = ft_strjoin_shell(result, after_dollar);
		}
	}
	free(dollar_input);
	free(after_dollar);
	free(*to_change);
	*to_change = result;
}
