/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:26:07 by mtani             #+#    #+#             */
/*   Updated: 2024/05/09 17:15:35 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_unsetenv_loop(t_shell *shell, t_uns_ind *ind, char ***new_env,
		t_str arg)
{
	if (ft_strncmp((*shell->my_env)[ind->i], arg, ft_strlen(arg)))
	{
		(*new_env)[ind->j] = ft_strdup((*shell->my_env)[ind->i]);
		ind->j++;
	}
	if (ft_strncmp((*shell->my_env)[ind->i], arg, ft_strlen(arg)) == 0)
	{
		if (!((*shell->my_env)[ind->i][ft_strlen(arg)] == '=')
			&& !((*shell->my_env)[ind->i][ft_strlen(arg)] == 0))
		{
			(*new_env)[ind->j] = ft_strdup((*shell->my_env)[ind->i]);
			ind->j++;
		}
	}
	ind->i++;
}

static void	ft_unsetenv(char *arg, t_shell *shell)
{
	t_uns_ind	ind;
	char		**new_env;

	ind.i = 0;
	ind.j = 0;
	new_env = (char **)ft_malloc(sizeof(char *) * (ft_arrlen(*(shell->my_env))
				+ 1));
	if (!new_env)
		exit(1);
	while ((*shell->my_env)[ind.i])
	{
		ft_unsetenv_loop(shell, &ind, &new_env, arg);
	}
	new_env[ind.j] = NULL;
	*(shell->my_env) = new_env;
}

void	ft_unset(t_shell *shell, int i)
{
	int	j;

	j = 1;
	if (!shell->cmd_table[i].cmd.cmd_wargs[1])
	{
		ft_putendl_fd("minishell: unset: not enough arguments", 2);
		return ;
	}
	while (shell->cmd_table[i].cmd.cmd_wargs[j])
	{
		if (ft_strchr(shell->cmd_table[i].cmd.cmd_wargs[j], '='))
		{
			ft_putstr_fd(RED "minishell: unset: `" WHITE, 2);
			ft_putstr_fd(shell->cmd_table[i].cmd.cmd_wargs[j], 2);
			ft_putendl_fd(RED "': not a valid identifier" WHITE, 2);
		}
		else
			ft_unsetenv(shell->cmd_table[i].cmd.cmd_wargs[j], shell);
		j++;
	}
}
