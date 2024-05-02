/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:45:04 by gsapio            #+#    #+#             */
/*   Updated: 2024/04/30 19:36:03 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	clear_garbage()
{
	t_list	*node;
	t_list	*tmp;
	int		i;
	char	*fname;

	i = -1;
	node = *garbage_collector();
	while (node)
	{
		tmp = node->next;
		if (node)
		{
			if (node->content)
				free(node->content);
			free(node);
		}
		node = tmp;
	}
	while (++i < *n_doc())
	{
		fname = ft_strjoin("./tmp/heredoc", ft_itoa(i));
		unlink(fname);
	}
	*garbage_collector() = NULL;
	rl_clear_history();
}

void	clear_garbage_no_unlink()
{
	t_list	*node;
	t_list	*tmp;
	int		i;

	i = -1;
	node = *garbage_collector();
	while (node)
	{
		tmp = node->next;
		if (node)
		{
			if (node->content)
				free(node->content);
			free(node);
		}
		node = tmp;
	}
	*garbage_collector() = NULL;
	rl_clear_history();
}
