/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 09:12:09 by aranaivo          #+#    #+#             */
/*   Updated: 2024/09/27 10:03:14 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	handle echo / pwd / env
	call exit function when exit
*/

// static int	ft_use_my_own_functions(char *line)
// {
// 	char	*cmd;

// 	if (line[0] == '/')
// 		cmd = ft_strrchr(line, '/');
// 	else
// 		cmd = line;
// 	if (ft_check_cmd(cmd) == 1 || ft_check_cmd(cmd) == 2
// 		|| ft_check_cmd(cmd) == 3)
// 		return (1);
// 	if (ft_check_cmd(line) == 0 || ft_check_cmd(line) == 4
// 		|| ft_check_cmd(line) == 5 || ft_check_cmd(line) == 8)
// 		return (1);
// 	return (0);
// }

char	**ft_get_all_path(t_list *env, char *line)
{
	char	*paths;
	char	**paths_tab;
	int		i;

	i = 0;
	paths = ft_getvar(env, "PATH");
	paths += 6;
	if (line[0] == '/')
	{
		paths_tab = malloc(sizeof(char *) * 2);
		paths_tab[0] = ft_strdup(line);
		paths_tab[1] = NULL;
		return (paths_tab);
	}
	paths_tab = ft_split(paths, ':');
	while (paths_tab[i] != NULL)
	{
		paths_tab[i] = ft_strjoin_shell(paths_tab[i], "/");
		paths_tab[i] = ft_strjoin_shell(paths_tab[i], line);
		i++;
	}
	return (paths_tab);
}

char	*ft_verify_exec_cmd(char **paths)
{
	int		i;
	char	*result;
	i = 0;
	while (paths[i] != NULL)
	{
		if (access(paths[i], X_OK) == 0)
		{
			result = ft_strdup_shell(paths[i]);
			ft_free_all(paths);
			return (result);
		}
		i++;
	}
	ft_free_all(paths);
	return (NULL);
}
