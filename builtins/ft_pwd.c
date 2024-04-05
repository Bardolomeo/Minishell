/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:22:26 by mtani             #+#    #+#             */
/*   Updated: 2024/04/05 14:00:31 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	if (shell->args[1] != NULL)
	{
		ft_putstr_fd("minishell: pwd: too many arguments\n", 2);
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		perror(RED "minishell$ " WHITE);
	else
	{
		ft_putendl_fd(pwd, 1);
		free(pwd);
	}
}