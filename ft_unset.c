/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:26:07 by mtani             #+#    #+#             */
/*   Updated: 2024/03/26 11:54:22 by mtani            ###   ########.fr       */
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

static void	ft_unsetenv(char *arg, t_shell *shell)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = (char **)malloc(sizeof(char *) * (ft_arrlen(shell->my_env) + 1));
	if (!new_env)
		exit(1);
	while (shell->my_env[i])
	{
		if (ft_strncmp(shell->my_env[i], arg, ft_strlen(arg)))
		{
			new_env[j] = ft_strdup(shell->my_env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	ft_free_array(shell->my_env);
	shell->my_env = new_env;
}

void	ft_unset(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->args[i])
	{
		if (ft_strchr(shell->args[i], '='))
		{
			ft_putstr_fd(RED"minishell: unset: `"WHITE, 2);
			ft_putstr_fd(shell->args[i], 2);
			ft_putendl_fd(RED"': not a valid identifier"WHITE, 2);
		}
		else
			ft_unsetenv(shell->args[i], shell);
		i++;
	}
}