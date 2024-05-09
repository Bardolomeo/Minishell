/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:24:13 by mtani             #+#    #+#             */
/*   Updated: 2024/05/09 16:32:44 by mtani            ###   ########.fr       */
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
