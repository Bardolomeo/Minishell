/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_altsplit_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:51:30 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/06 13:26:48 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	special_check(char *to_check, char quote)
{
	if (quote)
	{
		if (*to_check == '<')
			*to_check = -23;
		if (*to_check == '>')
			*to_check = -22;
		if (*to_check == '|')
			*to_check = -21;
	}
}

void	ft_altcount_arr_loop(char const *s, char c, size_t *count)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == '\"' || s[i] == '\''))
		{
			if (quote == 0)
				quote = s[i];
			else if (s[i] == quote)
				quote = 0;
			i++;
		}
		if (s[i] == c && quote == 0)
			(*count)++;
		if (s[i] != 0)
			i++;
	}
}

size_t	ft_altcount_arr(char const *s, char c)
{
	size_t	count;
	size_t	in_arr;

	count = 0;
	in_arr = 0;
	if (s == NULL)
		return (0);
	ft_altcount_arr_loop(s, c, &count);
	return (count);
}

void	skip_quotes(const char *s, size_t *start, char *quote)
{
	while (s[*start] && (s[*start] == '\"' || s[*start] == '\''))
	{
		if (*quote == 0)
		{
			*quote = s[*start];
			(*start)++;
		}
		else if (s[*start] == *quote)
		{
			*quote = 0;
			(*start)++;
		}
		else
			break ;
	}
	return ;
}

size_t	ft_altstrlen(const char *s, size_t start, char c, char quote)
{
	size_t	str_len;

	str_len = 0;
	if (quote == 0)
		str_len = find_unquoted(s, c, start);
	else
		str_len = find_quoted(s, quote, start, c);
	return (str_len);
}
