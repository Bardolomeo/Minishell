/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:42:25 by gsapio            #+#    #+#             */
/*   Updated: 2024/03/28 19:54:52 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status;

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

int main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	argc += 0;
	argv += 0;
	g_exit_status = 0;
	shell = (t_shell *)ft_malloc(sizeof(t_shell));
	if (shell == NULL)
		return (1);
	shell->my_env = ft_myenv();
	*(shell->my_env) = ft_strdup_array(env);
	shell->input = readline(RED "minishell$ " WHITE);
	while (shell->input)
	{
		*(shell->my_env) = ft_strdup_array(*(shell->my_env));
		if (ft_strlen(shell->input) > 0)
		{
			add_history(shell->input);
			ft_lexer(shell);
			if (shell->input)
			{
				shell->args = ft_split(shell->input, ' ');
				if (ft_strncmp(shell->args[0], "exit", 4) == 0)
				{
					clear_garbage();
					exit(g_exit_status);
				}
				else if (ft_strncmp(shell->args[0], "cd", 2) == 0)
					ft_cd(shell);
				else if (ft_strncmp(shell->args[0], "pwd", 3) == 0)
					ft_pwd();
				else if (ft_strncmp(shell->args[0], "echo", 4) == 0)
					ft_echo(shell);
				else if (ft_strncmp(shell->args[0], "env", 3) == 0)
					ft_env(shell);
				else if (ft_strncmp(shell->args[0], "export", 6) == 0)
					ft_export(shell);
				else if (ft_strncmp(shell->args[0], "unset", 5) == 0)
					ft_unset(shell);
				else
					ft_exec(shell);
			}
		}
		// free(shell->input);
		shell->input = readline(RED "minishell$ " WHITE);
	}
}
