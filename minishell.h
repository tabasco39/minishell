/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:02:09 by aelison           #+#    #+#             */
/*   Updated: 2024/09/02 10:26:11 by aranaivo         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*
 *============ Compile tgetent	: -ltermcap
 *============ Compile readline	: -lreadline
 */

/*
Moi
	env;	✅
	echo;	✅
	cd;		✅
	dollar;
	e_export;	✅
	delimiter_redirect_input;
*/

/*
Tabasco
	pwd; ✅
	unset; ✅
	redirect_output; ✅
	append_redirect_output;
	e_exit; ✅
	redirect_input; ✅
*/

typedef enum e_command
{
	argument,                 // 0
	option,                   // 1
	env,                      // 2
	pwd,                      // 3
	cd,                       // 4
	echo,                     // 5
	unset,                    // 6
	dollar,                   // 7
	question,                 // 8				$? c'est quoi caaa
	e_export,                 // 9
	e_exit,                   // 10
	e_pipe,                   // 11
	redirect_input,           // 12				<
	redirect_output,          // 13			>
	delimiter_redirect_input, // 14	<<
	append_redirect_output,   // 15	>>
	not_comm,                 // 16
	in_sys                    // 17
}							t_comm;

typedef struct s_token
{
	int						is_head;
	int						is_end;
	char					*token;
	t_comm					command;
	struct s_token			*next;
	struct s_token			*prev;
}							t_token;

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

int							ft_check_cmd(char *token);
int							ft_export(t_var *var, char *to_add);
int							ft_find_char(char *token, char to_find);
int							ft_unset_envp(t_var *var, char *to_del);
int							ft_count_quote(char *str, char *to_count);

char						*ft_verify_exec_cmd(char **paths);
char						*ft_pwd(void);
char						*ft_strdup_shell(char *s);
char						*ft_getvar(t_list *envp, char *var);
char						*ft_readline(t_list *env, char *prompt);
char						*ft_strjoin_shell(char *first, char *second);
char						*ft_env_variable(t_list *envp, char *to_find);

char						**ft_new_envp(t_list *env);
char						**ft_get_all_path(t_list *env, char *line);
char						**ft_split_shell(char const *s, char c);

void						ft_exit(t_var *var, int end);
void						ft_free_all(char **split);
void						ft_lstclear_shell(t_token **head);
void						ft_echo(t_list *env, char *to_print);
void						ft_div_by_token(char *line, t_token **head);
void						ft_create_envp(t_list **all_env, char **envp);
void						ft_add_token(t_token **head, t_token *new_elem);
void						ft_exec_sys_func(t_instru *instruction, t_var *var);

/*========== Parsing =================*/
void						ft_redirection(t_token *current, t_token *nxt);
void						ft_parse_no_arg(t_token *current, t_token *nxt);
void						ft_parse_arg(t_token *current, t_token *nxt);
void						ft_parse(t_token *token, t_list *env);
void						ft_parse_dollar(t_token *current, t_list *env);
char						*ft_del_quote(char *word, char *quote);
char						*ft_get_first_quote(char *str);

t_token						*ft_create_token(char *token);

/*============== instructions =================*/
int							ft_count_token_in_instru(t_instru *current);
t_instru					*ft_set_instru(t_token *head);

/*=============== valid instruction ============*/
int							ft_valid_pipe(t_token *head);
int							ft_valid_dollar(t_token *head);
int							ft_valid_delim_input(t_token *head);
int							ft_valid_env(t_instru *current);
int							ft_valid_echo(t_instru *current);
int							ft_valid_cd(t_instru *current);
int							ft_valid_export(t_instru *current);
int							ft_valid_pwd(t_instru *instruction);
int							ft_valid_unset(t_instru *instruction);
int							ft_valid_exit(t_instru *instruction);
int							ft_valid_redirect_and_append_output(t_token *token);
int							ft_valid_redirect_input(t_token *token);
int							ft_valid_exit_util(char *token);
void						ft_change_dollar_value(t_token *head, t_list *env);
void						ft_cmd_validation(t_var *all);
void						ft_change_argument(t_instru *instruction);

/*=================== Execution =============================*/
char	ft_first_quote(char *word, char first, char second);

/*============= Token control ========================*/
void	ft_move_nxt_to_head(t_token **head, t_token *target);
void	ft_command_setup(t_token **head);

/*================== Clear =======================*/
void	ft_lstclear_instru(t_instru **instru, t_token **head);

/*====================== Debug =========================*/
void						ft_debug(t_var *var);
void						ft_disp_dchar(char **str);
void						ft_display_env(t_list **env);
void						ft_display_token(t_token *token);
#endif
