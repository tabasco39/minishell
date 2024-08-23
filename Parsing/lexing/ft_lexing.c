/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:00:50 by aelison           #+#    #+#             */
/*   Updated: 2024/08/21 09:40:52 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_check_cmd_aux(char *token)
{
	if (ft_strncmp(token, "cd", 2) == 0)
		return (cd);
	if (ft_strncmp(token, "pwd", 3) == 0)
		return (pwd);
	if (ft_strncmp(token, "env", 3) == 0)
		return (env);
	if (ft_strncmp(token, "echo", 4) == 0)
		return (echo);
	if (ft_strncmp(token, "unset", 5) == 0)
		return (unset);
	if (ft_strncmp(token, "exit", 4) == 0)
		return (e_exit);
	if (ft_strncmp(token, "$", 1) == 0)
		return (dollar);
	if (ft_strncmp(token, "-", 1) == 0)
		return (option);
	if (ft_strncmp(token, "|", 1) == 0)
		return (e_pipe);
	return (not_comm);
}

int	ft_check_cmd(char *token)
{
	int	res;

	if (ft_strncmp(token, "$?", 2) == 0)
		return (question);
	if (ft_strncmp(token, "export", 6) == 0)
		return (e_export);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (delimiter_redirect_input);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (append_redirect_output);
	if (ft_strncmp(token, ">", 1) == 0)
		return (redirect_output);
	if (ft_strncmp(token, "<", 1) == 0)
		return (redirect_input);
	res = ft_check_cmd_aux(token);
	return (res);
}

t_token	*ft_create_token(char *token)
{
	t_token	*result;

	result = malloc(sizeof(t_token));
	if (!result)
		return (NULL);
	result->is_head = 0;
	result->is_end = 0;
	result->command = ft_check_cmd(token);
	result->token = ft_strdup(token);
	result->next = NULL;
	result->prev = NULL;
	return (result);
}

void	ft_add_token(t_token **head, t_token *new_elem)
{
	t_token	*last;

	if (*head == NULL)
	{
		*head = new_elem;
		(*head)->is_head = 1;
	}
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new_elem;
		new_elem->prev = last;
	}
}
