/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:02:09 by aelison           #+#    #+#             */
/*   Updated: 2024/09/27 12:52:27 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <time.h>

# define GREEN "\x1b[32m"
# define RESET "\x1b[0m"

typedef enum e_command
{
	argument,
	option,
	env,
	pwd,
	cd,
	echo,
	unset,
	dollar,
	question,
	e_export,
	e_exit,
	e_pipe,
	redirect_input,
	redirect_output,
	delimiter_redirect_input,
	append_redirect_output,
	not_comm,
	in_sys,
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

typedef struct s_history
{
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}	t_history;

typedef struct s_read_line
{
	char			*result;
	char			*old_result;
	unsigned long	cur_pos;
}	t_read_line;

typedef struct s_var
{
	char					*line;
	t_list					*env;
	char					**tab_env;
	char					**path;
	t_instru				*instru;
	t_token					*token;
}							t_var;

typedef struct s_exec_iteration
{
	int	i;
	int	start;
	int	end;
	int	here_doc_fd[2];
	int	pipefd[2];
}	t_exec;

int			ft_cd(char *path);
int			ft_check_cmd(char *token);
int			ft_export(t_var *var, char *to_add);
int			ft_find_char(char *token, char to_find);
int			ft_unset_envp(t_var *var, char *to_del);
int			ft_count_quote(char *str, char *to_count);
char		*ft_verify_exec_cmd(char **paths);
char		*ft_pwd(void);
char		*ft_strdup_shell(char *s);
char		*ft_getvar(t_list *envp, char *var);
char		*ft_strjoin_shell(char *first, char *second);
char		*ft_env_variable(t_list *envp, char *to_find);
char		**ft_new_envp(t_list *env);
char		**ft_get_all_path(t_list *env, char *line);
char		**ft_split_shell(char const *s, char c);
void		ft_exit(t_var *var, int end);
void		ft_free_all(char **split);
void		ft_lstclear_shell(t_token **head);
void		ft_echo(char *to_print, char option);
void		ft_div_by_token(char *line, t_token **head);
void		ft_create_envp(t_list **all_env, char **envp);
void		ft_add_token(t_token **head, t_token *new_elem);

/*========== Parsing =================*/

void	ft_parse_dollar_up(t_var *var, char **to_change);
void		ft_redirection(t_token *current, t_token *nxt);
void		ft_parse_no_arg(t_token *current, t_token *nxt);
void		ft_parse_arg(t_token *current, t_token *nxt);
void		ft_parse(t_var *var, t_token *current);
char		*ft_del_quote(char *word, char *quote);
char		*ft_get_first_quote(char *str);
t_token		*ft_create_token(char *token);

/*============== instructions =================*/
int			ft_count_token_in_instru(t_instru *current);
t_instru	*ft_set_instru(t_token *head);

/*=============== valid instruction ============*/
int			ft_valid_pipe(t_token *head);
int			ft_valid_dollar(t_token *head);
int			ft_valid_delim_input(t_token *head);
int			ft_valid_env(t_instru *current);
int			ft_valid_echo(t_instru *current);
int			ft_valid_cd(t_instru *current);
int			ft_valid_export(t_instru *current);
int			ft_valid_pwd(t_instru *instruction);
int			ft_valid_unset(t_instru *instruction);
int			ft_valid_exit(t_instru *instruction);
int			ft_valid_redirect_and_append_output(t_token *token);
int			ft_valid_redirect_input(t_token *token);
int			ft_valid_exit_util(char *token);
void		ft_change_dollar_value(t_token *head, t_list *env);
void		ft_cmd_validation(t_var *all);
void		ft_change_argument(t_instru *instruction);

/*=================== Execution =============================*/
void		ft_exec(t_instru *instruction, t_var *var);
char		ft_first_quote(char *word, char first, char second);
int			ft_exec_builtin(t_var *all_var, t_token *start, t_token *end);

/*============= Token control ========================*/
void		ft_move_nxt_to_head(t_token **head, t_token *target);
void		ft_command_setup(t_token **head);

/*================== Clear =======================*/
void		ft_lstclear_instru(t_instru **instru, t_token **head);

/*===================== test_readline =============================*/
char		*ft_readline(t_list *env, char *prompt);
char		*ft_readline_de_moi(char *prompt, t_history **history);

/*==================== HISTORY ====================*/
void		ft_init_history_stack(t_history **stack);
void		ft_add_history(char *to_add, t_history **stack);

void		ft_add_node_history(t_history **head, t_history *to_add);
t_history	*ft_create_node_history(char *line);
t_history	*ft_get_pos_history(t_history *current, char pos);
void		ft_show_history(t_history *current, char *message);
void		ft_clear_history(t_history **head);

/*==================== Utils =====================*/
int			ft_is_char_pair(char *line, char quote);
char		*ft_div_by_redirect(char *line, char *ref);
void		ft_edit(char *line, int *i, char *result, int *j);
void		ft_div_aux(char *result, char div, int *j, int nb);
t_token 	*ft_find_cmd(t_token *start, t_comm to_find);


/*====================== Env ====================*/
void		ft_sort_env_list(t_list **result, char **tab_env);

/*====================== Debug =========================*/
void		ft_debug(t_var *var);
void		ft_disp_dchar(char **str);
void		ft_display_env(t_list **env, char *before);
void		ft_display_token(t_token *token);
#endif
