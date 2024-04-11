/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:09:54 by mtani             #+#    #+#             */
/*   Updated: 2024/04/11 18:17:07 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(const char *str)
{
	char	*line;
	t_list	*node;

	line = readline(str);
	if (line == NULL)
	{
		clear_garbage();
		printf("exit\n");
		exit(0);
	}
	node = ft_lstnew(line);
	ft_lstadd_front(garbage_collector(), node);
	return (line);
}