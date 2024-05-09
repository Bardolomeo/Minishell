# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtani <mtani@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 14:01:07 by gsapio            #+#    #+#              #
#    Updated: 2024/05/09 15:15:18 by mtani            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c \
	./split/ft_altsplit.c ./split/ft_altsplit_utils.c\
	./builtins/ft_cd.c ./builtins/ft_pwd.c ./builtins/ft_echo.c ./builtins/ft_env.c ./builtins/ft_export.c ./builtins/ft_unset.c \
	./utils/ft_single.c ./utils/ft_error.c ./utils/ft_readline.c ./utils/is_reserved.c ./utils/ft_single_ii.c utils/garbage_collector.c \
	./utils/ft_find_functions.c \
	./lexer/ft_lexer.c ./lexer/expander_utils.c ./lexer/expander_brackets.c\
	./parser/ft_parser.c ./parser/create_heredoc.c ./parser/redirect_heredoc.c ./parser/redirections.c\
	./executor/ft_executor.c \
	./signals/ft_signals.c

LFLAGS = -lft -lreadline

PATH_LIBS = -Llibft

LIBFT_PATH = libft

OBJS	= $(SRCS:.c=.o)

HEADER			= ./

CC				= cc -g

RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror

NAME			= minishell


all:			$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

$(NAME):		$(OBJS)
				make -C $(LIBFT_PATH) --no-print-directory
				make bonus -C $(LIBFT_PATH) --no-print-directory
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(PATH_LIBS) $(LFLAGS)
				#clear

clean:
				$(RM) $(OBJS)
				make clean -C $(LIBFT_PATH) --no-print-directory

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY: re clean fclean all
