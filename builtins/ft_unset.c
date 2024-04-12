/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:26:07 by mtani             #+#    #+#             */
/*   Updated: 2024/04/12 15:53:18 by gsapio           ###   ########.fr       */
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
	new_env = (char **)ft_malloc(sizeof(char *) * (ft_arrlen(*(shell->my_env)) + 1));
	if (!new_env)
		exit(1);
	while ((*shell->my_env)[i])
	{
		if (ft_strncmp((*shell->my_env)[i], arg, ft_strlen(arg)))
		{
			new_env[j] = ft_strdup((*shell->my_env)[i]);
			j++;
		}
		if (ft_strncmp((*shell->my_env)[i], arg, ft_strlen(arg)) == 0)
		{
			if (!((*shell->my_env)[i][ft_strlen(arg)] == '=') && !((*shell->my_env)[i][ft_strlen(arg)] == 0))
			{
				new_env[j] = ft_strdup((*shell->my_env)[i]);
				j++;
			}
		}
		i++;
	}
	new_env[j] = NULL;
	*(shell->my_env) = new_env;
}

void	ft_unset(t_shell *shell)
{
	int		i;

	i = 0;
	if (!shell->args[1])
	{
		ft_putendl_fd("minishell: unset: not enough arguments", 2);
		return ;
	}
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
