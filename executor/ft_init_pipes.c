/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:24:13 by mtani             #+#    #+#             */
/*   Updated: 2024/05/10 15:48:37 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_first_pipe(int *fd, int i)
{
	dup2(fd[i * 2 + 1], 1);
	close(fd[i * 2 + 1]);
}

void	init_last_pipe(int *fd, int i)
{
	dup2(fd[(i - 1) * 2], 0);
	close(fd[(i - 1) * 2]);
}

void	init_mid_pipe(int *fd, int i)
{
	dup2(fd[(i - 1) * 2], 0);
	close(fd[(i - 1) * 2]);
	dup2(fd[i * 2 + 1], 1);
	close(fd[i * 2 + 1]);
}

void	clean_exit(void)
{
	clear_garbage();
	exit(*exit_status());
}
