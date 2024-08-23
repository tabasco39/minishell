# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 10:34:59 by aelison           #+#    #+#              #
#    Updated: 2024/08/23 08:51:54 by aranaivo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = ./libft/libft.a

SRC = ft_program.c \
	  test_readline.c \
	  debug.c \
	  Utils/ft_utils.c \
	  Utils/ft_handle_path.c \
	  Execution/ft_exec_cmd.c \
	  Execution/ft_executor.c \
	  Env/ft_handle_envp.c \
	  Env/ft_new_envp.c \
	  Parsing/lexing/ft_lexing.c \
	  Parsing/lexing/ft_div_by_token.c \
	  Parsing/parse/ft_parse.c \
	  Parsing/parse/ft_parse_utils.c \
	  Parsing/instruction/ft_set_instructions.c \
	  Command_validation/ft_my_validation.c \
	  Command_validation/ft_valid_first.c \
	  Command_validation/ft_valid_second.c \
	  Command_validation/ft_cmd_validation.c \
	  Command_validation/ft_validation_utils.c 

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

all: ${NAME}

${NAME}: ${OBJ} ${LIB}
	${CC} ${CFLAGS} ${OBJ} ${LIB} -lreadline -o ${NAME}

${LIB}:
	make -C ./libft/ bonus

clean:
	rm -f ${OBJ}
	make -C ./libft/ clean

fclean: clean
	rm -f ${NAME}
	make -C ./libft/ fclean

re: fclean all

.PHONY: all fclean re
