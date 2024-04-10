/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_singletons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:32:13 by gsapio            #+#    #+#             */
/*   Updated: 2024/04/09 15:56:53 by gsapio           ###   ########.fr       */
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
