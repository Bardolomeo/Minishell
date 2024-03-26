# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtani <mtani@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 14:01:07 by gsapio            #+#    #+#              #
#    Updated: 2024/03/26 11:56:52 by mtani            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c ft_cd.c ft_pwd.c ft_echo.c ft_env.c ft_export.c ft_unset.c ft_exec.c garbage_collector.c

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
				clear

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
