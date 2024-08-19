/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:02:09 by aelison           #+#    #+#             */
/*   Updated: 2024/08/19 13:53:07 by aelison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <termcap.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

/*
 *============ Compile tgetent	: -ltermcap
 *============ Compile readline	: -lreadline
 */

typedef enum e_command
{
	argument,	//0
	option,		//1
	env,		//2
	pwd,		//3
	cd,			//4
	echo,		//5
	unset,		//6
	dollar,		//7
	question,	//8				$? c'est quoi caaa
	e_export,	//9
	e_exit,		//10
	e_pipe,		//11
	redirect_input,	//12				<
	redirect_output,	//13			>
	delimiter_redirect_input,	//14	<<
	append_redirect_output,		//15	>>
	not_comm,					//16
	in_sys						//17
}							t_comm;

typedef struct s_token
{
	int						is_head;
	char					*token;
	t_comm					command;
	struct s_token			*next;
	struct s_token			*prev;
}	t_token;

typedef struct s_instruction
{
	int						id;
	t_token					*start;
	t_token					*end;
	struct s_instruction	*next;
	struct s_instruction	*prev;
}							t_instru;

typedef struct s_var
{
	char					*line;
	t_list					*env;
	char					**tab_env;
	char					**path;
	t_instru				*instru;
	t_token					*token;
}							t_var;

int		ft_check_cmd(char *token);
int		ft_verify_exec_cmd(char **paths, char **envp);
int		ft_export(t_var *var, char *to_add);
int		ft_find_char(char *token, char to_find);
int		ft_unset_envp(t_var *var, char *to_del);
int		ft_count_in_word(char *word, int quote);

char	*ft_pwd(void);
char	*ft_strdup_shell(char *s);
char	*ft_getvar(t_list *envp, char *var);
char	*ft_del_quote(char *word, int quote);
char	*ft_readline(t_list *env, char *prompt);
char	*ft_strjoin_shell(char *first, char *second);
char	*ft_env_variable(t_list *envp, char *to_find, int quote);

char	**ft_new_envp(t_list *env);
char	**ft_get_all_path(t_list *env, char *line);

void	ft_exit(t_var *var, int end);
void	ft_free_all(char **split);
void	ft_lstclear_shell(t_token **head);
void	ft_echo(t_list *env, char *to_print);
void	ft_div_by_token(char *line, t_token **head);
void	ft_create_envp(t_list **all_env, char **envp);
void	ft_add_token(t_token **head, t_token *new_elem);
void	ft_handle_quote(t_var *var, int quote);
void	ft_exec_sys_func(char *paths, char **cmd_list, char **envp);
void	ft_parse(t_token *token);

t_token	*ft_create_token(char *token);

/*====================== Debug =========================*/
void	ft_debug(t_var *var);
void	ft_disp_dchar(char **str);
void	ft_display_env(t_list **env);
void	ft_display_token(t_token *token);
#endif
