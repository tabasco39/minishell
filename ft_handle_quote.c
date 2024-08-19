/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:34:55 by aelison           #+#    #+#             */
/*   Updated: 2024/08/13 15:45:25 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_del_quote(char *word, int quote)
{
	int		i;
	int		j;
	int		len;
	int		nb_quote;
	char	*result;

	nb_quote = ft_count_in_word(word, quote);
	len = ft_strlen(word) - nb_quote;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < len)
	{
		while (word[i] == (char)quote)
			i++;
		result[j] = word[i];
		i++;
		j++;
	}
	result[j] = '\0';
	free(word);
	return (result);
}

void	ft_prompt(t_var *var, int quote)
{
	char	*newline;
	char	*tmp;
	char	*end;

	newline = ft_strjoin(ft_strchr(var->line, quote) + 1, "\n");
	while (1)
	{
		tmp = ft_readline(var->env, "> ");
		if (ft_find_char(tmp, quote) != -1)
		{
			end = ft_del_quote(tmp, quote);
			newline = ft_strjoin_shell(newline, end);
			free(end);
			break ;
		}
		else
		{
			newline = ft_strjoin_shell(newline, tmp);
			newline = ft_strjoin_shell(newline, "\n");
			free(tmp);
		}
	}
	ft_putstr_fd(newline, 1);
	free(newline);
}

void	ft_handle_quote(t_var *var, int quote)
{
	if (ft_count_in_word(var->line, quote) % 2 == 0)
		var->line = ft_del_quote(var->line, quote);
	else
		ft_prompt(var, quote);
}
