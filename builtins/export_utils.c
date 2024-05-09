/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:18:05 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/09 16:22:32 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_error(void)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	*exit_status() = 1;
	return (1);
}

void	export_no_args(t_shell *shell)
{
	int	i;

	i = 0;
	while ((*shell->my_env)[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd((*shell->my_env)[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	add_empty_env(char *env, char ***my_env)
{
	int		i;
	t_str	*new_env;

	i = 0;
	while ((*my_env)[i] != NULL)
	{
		if (ft_strncmp((*my_env)[i], env, ft_strlen(env)) == 0)
			return ;
		i++;
	}
	new_env = (t_str *)ft_malloc(sizeof(t_str) * (i + 2));
	i = 0;
	while ((*my_env)[i] != NULL)
	{
		new_env[i] = ft_strdup((*my_env)[i]);
		i++;
	}
	new_env[i] = ft_strdup(env);
	new_env[i + 1] = NULL;
	(*my_env) = new_env;
}

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
