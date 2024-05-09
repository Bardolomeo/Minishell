/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:25:58 by mtani             #+#    #+#             */
/*   Updated: 2024/05/09 17:27:50 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_not_empty(char *arg, t_shell *shell, int j)
{
	t_str	*env;

	if (arg[j] == '\0' || arg[j - 1] == ' ' || arg[j - 1] == '\0')
		return (export_error());
	env = ft_altsplit(arg, '=');
	if (env[1] == NULL)
		env[1] = ft_strdup("");
	env[1] = ft_strtrim(env[1], "\"");
	add_env(shell, env[0], env[1]);
	return (0);
}

int	export_check_errors(int *k, t_str *arg, const char *s)
{
	*k = 0;
	*arg = ft_strdup(s);
	while ((*arg)[*k] != '\0' && (*arg)[*k] != '=')
	{
		if (is_reserved_export((*arg)[*k])
			|| ft_isdigit(*arg[0]))
		{
			export_error();
			return (0);
		}
		(*k)++;
	}
	return (1);
}

void	ft_export(t_shell *shell, int i, char *pflag)
{
	int		j;
	int		k;
	t_str	arg;

	arg = NULL;
	if (ft_strncmp(pflag, "inpipe", 6) == 0
		&& shell->cmd_table[i].cmd.cmd_wargs[1] != NULL)
		return ;
	if (shell->cmd_table[i].cmd.cmd_wargs[1] == NULL)
		export_no_args(shell);
	j = 0;
	while (shell->cmd_table[i].cmd.cmd_wargs[++j] != NULL)
	{
		if (!export_check_errors(&k, &arg,
				shell->cmd_table[i].cmd.cmd_wargs[j]))
			return ;
		if (arg[k] == '\0' && arg[k - 1] != '=')
		{
			add_empty_env(arg, shell->my_env);
			continue ;
		}
		export_not_empty(arg, shell, k);
	}
}
