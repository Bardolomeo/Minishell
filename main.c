/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:42:25 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/02 17:38:47 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal;

char	**ft_strdup_array(char **array)
{
	int		i;
	char	**new_array;

	i = 0;
	while (array[i])
		i++;
	new_array = (char **)ft_malloc(sizeof(char *) * (i + 1));
	if (new_array == NULL)
		return (NULL);
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("args[%d]: %s\n", i, args[i]);
		i++;
	}
}

int	check_input(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->input[i] == ' ' || shell->input[i] == '\t' || shell->input[i] == '|')
	{
		if (shell->input[i] == '|')
		{
			add_history(shell->input);
			printf("Minishell: Syntax Error near '|'\n");
			return (0);
		}
		i++;
	}
	shell->input = shell->input + i;
	return (1);
}

int main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	argc += 0;
	argv += 0;
	shell = (t_shell *)ft_malloc(sizeof(t_shell));
	if (shell == NULL)
		return (1);
	shell->my_env = ft_myenv();
	*(shell->my_env) = ft_strdup_array(env);
	set_signals("interactive");
	shell->input = ft_readline(RED "minishell$ " WHITE, 0);
	while (shell->input)
	{
		if (!check_input(shell))
		{
			shell->input = ft_readline(RED "minishell$ " WHITE, 0);
			continue ;
		}
		*(shell->my_env) = ft_strdup_array(*(shell->my_env));
		if (ft_strlen(shell->input) > 0)
		{
			add_history(shell->input);
			ft_lexer(shell);
			if (ft_parser(shell))
				ft_executor(shell);
			g_signal = 0;
		}
		set_signals("interactive");
		shell->input = ft_readline(RED "minishell$ " WHITE, 0);
	}
}
