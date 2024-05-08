/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:49:55 by mtani             #+#    #+#             */
/*   Updated: 2024/05/08 17:11:57 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *str, int bra_flag)
{
	int		i;
	int		len;
	t_str	*myenv;

	myenv = *ft_myenv();
	len = 0;
	i = -1;
	while (myenv[++i] && *str != '\"' && *str != '\''
		&& !is_reserved_export(*str) && *str != '\0' && *str != ' '
		&& *str != '=')
	{
		get_env_loop(str, bra_flag, &len);
		if (ft_strncmp(myenv[i], str, len) == 0 && myenv[i][len] == '=')
			return (ft_strchr(myenv[i], '=') + 1);
	}
	return (NULL);
}

int	fill_input(char *str, int *i, char **tmp2, int bra_flag)
{
	char	*tmp;
	char	*tmpenv;

	tmp = NULL;
	tmpenv = ft_getenv(str + *i + 1, bra_flag);
	if (tmpenv)
	{
		if (*tmp2 == NULL)
		{
			tmp = ft_substr(str, 0, *i);
			*tmp2 = ft_strjoin(tmp, ft_getenv(str + *i + 1, bra_flag));
		}
		else
			*tmp2 = ft_strjoin(*tmp2, ft_getenv(str + *i + 1, bra_flag));
	}
	return (1);
}

int	expander_loop(t_shell *shell, t_exp_vars *vars)
{
	handle_quotes(shell, vars->i, vars->quotes);
	if (long_ass_condition(shell, vars->quotes, vars->i))
	{
		if (redirect_no_expand(shell, vars->i) == 1)
		{
			vars->tmp2 = ft_strjoin(vars->tmp2,
					ft_substr(shell->input, vars->i, 1));
			vars->i++;
			return (0);
		}
		if (shell->input[vars->i + 1] == 123)
			vars->f_break = handle_brackets(shell->input,
					&vars->i, &vars->bra_flag, &vars->tmp2);
		else
			vars->f_break = expand_wo_brackets(shell->input, &vars->i,
					&vars->tmp2, &vars->bra_flag);
	}
	else
	{
		vars->tmp2 = ft_strjoin(vars->tmp2,
				ft_substr(shell->input, vars->i, 1));
		vars->i++;
	}
	return (1);
}

void	expander(t_shell *shell)
{
	t_exp_vars	vars;

	init_expander(&vars);
	while (shell->input[vars.i])
	{
		if (!expander_loop(shell, &vars))
			continue ;
		if (vars.f_break == 0)
		{
			shell->input = NULL;
			return ;
		}
	}
	shell->input = vars.tmp2;
}

void	ft_lexer(t_shell *shell)
{
	expander(shell);
	if (shell->input != NULL)
		shell->args = ft_altsplit(shell->input, ' ');
}
