/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:26:15 by mtani             #+#    #+#             */
/*   Updated: 2024/04/16 17:10:01 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	find_quotetype(const char *s, size_t i, char quote, int *in_arr)
{
	if ((s[i] == '"' || s[i] == '\'') && quote == 0)
		quote = s[i];
	else if (s[i] == quote && quote != 0)
	{
		*in_arr = 0;
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

int	find_quoted(const char *s, char quote, size_t start)
{
	size_t		j;
	int			str_len;

	j = start + 1;
	str_len = 0;
	while (s[j] != quote && s[j] && quote != 0)
	{
		j++;
		str_len++;
	}
	if (s[j + 1] != '\0' && s[j + 1] != ' ')
	{
		while (s[j + 1] != ' ' && s[j + 1] != '\0')
		{
			j++;
			str_len++;
		}
	}
	return (str_len);
}
