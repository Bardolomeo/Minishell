/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:26:15 by mtani             #+#    #+#             */
/*   Updated: 2024/05/06 11:48:02 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	find_quotetype(const char *s, int *i, char quote, int *in_arr)
{
	in_arr = (void *)in_arr;
	if ((s[*i] == '"' || s[*i] == '\'') && quote == 0)
		quote = s[*i];
	else if (s[*i] == quote)
	{
		quote = 0;
	}
	return (quote);
}

int	find_unquoted(const char *s, char c, size_t start)
{
	size_t	j;
	int		str_len;
	char	quote;

	j = start;
	str_len = 0;
	quote = 0;
	while (s[j])
	{
		if ((s[j] == '"' || s[j] == '\'') && quote == 0)
			quote = s[j];
		else if (s[j] == quote && quote != 0)
			quote = 0;
		if (s[j] == c && quote == 0)
			break ;
		j++;
		str_len++;
	}
	return (str_len);
}

int	find_quoted(const char *s, char quote, size_t start, char c)
{
	int	str_len;

	quote = 0;
	str_len = 0;
	while (s[start] && (s[start] != c || quote != 0))
	{
		while (s[start] && (s[start] == '\"' || s[start] == '\''))
		{
			if (quote == 0)
			{
				quote = s[start];
				start++;
			}
			else if (s[start] == quote)
			{
				quote = 0;
				start++;
			}
			else
				break;
		}
		if (!s[start] || (s[start] == c && quote == 0))
			break;
		str_len++;
		start++;
	}
	return (str_len);
}
