/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:25:58 by mtani             #+#    #+#             */
/*   Updated: 2024/04/12 15:07:57 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_error(t_shell *shell, int i)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(shell->args[i], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_status = 1;
	return (1);
}

//export senza argomenti restituisce la lista delle variabili
void	export_no_args(t_shell *shell)
{
	int		i;

	i = 0;
	while ((*shell->my_env)[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd((*shell->my_env)[i] , 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

//"export hello" setta la variabile hello a vuoto, NON visibile con env
void	add_empty_env(char *env, char ***my_env)
{
	int 	i;

	i = 0;
	while ((*my_env)[i] != NULL)
	{
		if (ft_strncmp((*my_env)[i], env, ft_strlen(env)) == 0)
			return ;
		i++;
	}
	(*my_env)[i] = ft_strdup(env);
	(*my_env)[i + 1] = NULL;
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

int	export_not_empty(char *arg, t_shell *shell, int i, int j)
{
	t_str	*env;

	if (arg[j] == '\0' || arg[j - 1] == ' '  || arg[j - 1] == '\0')
		return (export_error(shell, i));
	env = ft_altsplit(arg, '=');
	if (env[1] == NULL)
		env[1] = ft_strdup("");
	env[1] = ft_strtrim(env[1], "\"");
	add_env(shell, env[0], env[1]);
	return (0);
}

void	ft_export(t_shell *shell)
{
	int		i;
	int		j;
	t_str	arg;

	if (shell->args[1] == NULL)
		export_no_args(shell);
	i = 0;
	while (shell->args[++i] != NULL)
	{
		j = 0;
		arg = ft_strdup(shell->args[i]);
		while (arg[j] != '\0' && arg[j] != '=')
		{
			if (is_reserved_export(arg[j]))
			{
				export_error(shell, i);
				return ;
			}
			j++;
		}
		if (arg[j] == '\0' && arg[j - 1] != '=')
		{
			add_empty_env(arg, shell->my_env);
			continue ;
		}
	export_not_empty(arg, shell, i, j);
	}
}
