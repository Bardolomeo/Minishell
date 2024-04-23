/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:44:42 by mtani             #+#    #+#             */
/*   Updated: 2024/04/12 16:25:41 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_error(int exit_code, char *str)
{
    if (str == NULL)
        perror("minishell");
    else
	{
        ft_putstr_fd(str, 2);
   		write(1, "\n", 1);
	}
	*exit_status() = exit_code;
}
