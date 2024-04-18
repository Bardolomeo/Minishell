/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:22:26 by mtani             #+#    #+#             */
/*   Updated: 2024/04/18 16:32:11 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *shell, int i)
{
	char	*pwd;

	if (shell->cmd_table[i].cmd.cmd_wargs[1] != NULL)
	{
		ft_putstr_fd("minishell: pwd: too many arguments\n", 2);
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		perror(RED "minishell$ " WHITE);
	else
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
		free(pwd);
	}
}