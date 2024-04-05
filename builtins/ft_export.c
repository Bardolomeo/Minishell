/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:25:58 by mtani             #+#    #+#             */
/*   Updated: 2024/04/05 11:43:23 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(t_shell *shell, char *key, char *value)
{
	int		i;
	t_str	*new_env;

	i = 0;
	while ((*shell->my_env)[i] != NULL)
	{
		if (ft_strncmp((*shell->my_env)[i], key, ft_strlen(key)) == 0)
		{
			(*shell->my_env)[i] = ft_strjoin(key, "=");
			(*shell->my_env)[i] = ft_strjoin((*shell->my_env)[i], value);
			return ;
		}
		i++;
	}
	new_env = (t_str *)ft_malloc(sizeof(t_str) * (i + 2));
	i = 0;
	while ((*shell->my_env)[i] != NULL)
	{
		new_env[i] = ft_strdup((*shell->my_env)[i]);
		i++;
	}
	new_env[i] = ft_strjoin(key, "=");
	new_env[i] = ft_strjoin(new_env[i], value);
	new_env[i + 1] = NULL;
	*(shell->my_env) = new_env;
}

void	ft_export(t_shell *shell)
{
	int		i;
	int		j;
	t_str	*env;

	i = 1;
	while (shell->args[i] != NULL)
	{
		j = 0;
		while (shell->args[i][j] != '\0' && shell->args[i][j] != '=')
			j++;
		if ((shell->args[i][j] == '\0' && shell->args[i][j - 1] == '=') || shell->args[i][j + 1] == ' ' || shell->args[i][j + 1] == '\0' || shell->args[i][j - 1] == ' ' )
		{
			ft_putstr_fd("minishell: export: `=", 2);
			ft_putstr_fd(shell->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_status = 1;
			return ;
		}
		if (shell->args[i][j] == '=')
		{
			env = ft_altsplit(shell->args[i], '=');
			if (env[1] == NULL)
				env[1] = ft_strdup("");
			env[1] = ft_strtrim(env[1], "\"");
			add_env(shell, env[0], env[1]);
			break ;
		}
		else
			add_env(shell, shell->args[i], "");
		i++;
	}
}