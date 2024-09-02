/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 09:12:09 by aranaivo          #+#    #+#             */
/*   Updated: 2024/09/02 09:58:59 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	handle echo / pwd / env
	call exit function when exit
*/

static int	ft_use_my_own_functions(char *line)
{
	char	*cmd;

	if (line[0] == '/')
		cmd = ft_strrchr(line, '/');
	else
		cmd = line;
	if (ft_check_cmd(cmd) == 1 || ft_check_cmd(cmd) == 2
		|| ft_check_cmd(cmd) == 3)
		return (1);
	if (ft_check_cmd(line) == 0 || ft_check_cmd(line) == 4
		|| ft_check_cmd(line) == 5 || ft_check_cmd(line) == 8)
		return (1);
	return (0);
}

char	**ft_get_all_path(t_list *env, char *line)
{
	char	*paths;
	char	**paths_tab;
	int		i;

	i = 0;
	paths = ft_getvar(env, "PATH");
	paths += 6;
	if (ft_use_my_own_functions(line) == 1)
		printf("command must execute our own function\n");
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
	//char	*sl[3];
	i = 0;
	// sl[0] = "cat";
	// sl[1] = "debug.c";
	// sl[2] = NULL;
	while (paths[i] != NULL)
	{
		if (access(paths[i], X_OK) == 0)
		{
			//ft_exec_sys_func(paths[i], sl, envp);
			//ft_free_all(paths);
			return (paths[i]);
		}
		i++;
	}
	printf("command not found\n");
	ft_free_all(paths);
	return (NULL);
}
