/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:44:42 by mtani             #+#    #+#             */
/*   Updated: 2024/04/11 11:56:01 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_exit(int exit_status, char *str)
{
    if (str == NULL)
        perror("minishell");
    else
        ft_putstr_fd(str, 2);
    g_exit_status = exit_status;
    // ft_putnbr_fd(g_exit_status, 2);
    write(1, "\n", 1);
}
