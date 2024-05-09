/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:51:44 by mtani             #+#    #+#             */
/*   Updated: 2024/05/09 16:51:46 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(int exit_code, char *str)
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
