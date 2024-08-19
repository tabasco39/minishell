# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aranaivo <aranaivo@student.42antananarivo. +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 10:34:59 by aelison           #+#    #+#              #
#    Updated: 2024/08/19 13:33:20 by aelison          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = ./libft/libft.a

SRC = ft_program.c \
	  ft_lexing.c \
	  ft_get_cmd.c \
	  ft_utils.c \
	  ft_new_envp.c \
	  test_readline.c \
	  ft_div_by_token.c \
	  ft_handle_path.c \
	  ft_handle_envp.c \
	  debug.c \
	  ft_handle_quote.c \
	  ft_quote_utils.c \
	  ft_executor.c \
	  ft_parse.c

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
