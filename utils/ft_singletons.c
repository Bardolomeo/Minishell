/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_singletons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:32:13 by gsapio            #+#    #+#             */
/*   Updated: 2024/04/15 14:37:08 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list **garbage_collector(void)
{
	static t_list *garb_static = NULL;
	return (&garb_static);
}

char ***ft_myenv(void)
{
    static char **env = NULL;
    return(&env);
}

int *n_doc(void)
{
    static int n_doc = 0;
    return(&n_doc);
}