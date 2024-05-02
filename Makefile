# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 14:01:07 by gsapio            #+#    #+#              #
#    Updated: 2024/04/30 17:49:02 by gsapio           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c garbage_collector.c ft_altsplit.c ft_find_functions.c \
	./builtins/ft_cd.c ./builtins/ft_pwd.c ./builtins/ft_echo.c ./builtins/ft_env.c ./builtins/ft_export.c ./builtins/ft_unset.c \
	./utils/ft_singletons.c ./utils/ft_error.c ./utils/ft_readline.c utils/is_reserved.c utils/ft_singletons_ii.c\
	./lexer/ft_lexer.c ./lexer/expander_utils.c \
	./parser/ft_parser.c \
	./executor/ft_executor.c \
	./signals/ft_signals.c

LFLAGS = -lft -lreadline

PATH_LIBS = -Llibft

LIBFT_PATH = libft

OBJS	= $(SRCS:.c=.o)

# BONUS			= main_bonus.c error_management_bonus.c pipex.c utils.c pipex_bonus.c

# OBJS_BONUS		= $(BONUS:.c=.o)

HEADER			= ./

CC				= cc -g

RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror

NAME			= minishell

# BONUS_NAME		= pipex_bonus

all:			$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

$(NAME):		$(OBJS)
				make -C $(LIBFT_PATH) --no-print-directory
				make bonus -C $(LIBFT_PATH) --no-print-directory
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(PATH_LIBS) $(LFLAGS)
				#clear

# bonus:			${BONUS_NAME}

# ${BONUS_NAME}:	$(OBJS_BONUS)
# 				make -C ./libft
# 				$(CC) $(CFLAGS) ${OBJS_BONUS} -Llibft -lft -o pipex -no-pie

clean:
				$(RM) $(OBJS)
				make clean -C $(LIBFT_PATH) --no-print-directory

fclean:			clean
				$(RM) $(NAME)
				# $(RM) $(BONUS_NAME)

re:				fclean all

.PHONY: re clean fclean all
