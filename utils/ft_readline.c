/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:09:54 by mtani             #+#    #+#             */
/*   Updated: 2024/04/30 18:42:21 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(const char *str, int heredoc)
{
	char	*line;
	t_list	*node;

	line = readline(str);
	if (line == NULL && !heredoc)
	{
		clear_garbage();
		printf("exit\n");
		exit(0);
	}
	if (line == NULL)
	{
		write(1, "\n", 1);
	}
	node = ft_lstnew(line);
	ft_lstadd_front(garbage_collector(), node);
	return (line);
}
