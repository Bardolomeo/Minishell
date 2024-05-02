/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_altsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:11:44 by mtani             #+#    #+#             */
/*   Updated: 2024/04/26 19:25:01 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static size_t	ft_altcount_arr(char const *s, char c)
{
	size_t	count;
	size_t	i;
	size_t	in_arr;
	char	quote;

	i = 0;
	count = 0;
	in_arr = 0;
	quote = 0;
	quote = 0;
	if (s == NULL)
		return (0);
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
			count++;
		if (s[i] != 0)
			i++;
	}
	return (count);
}

static char	*ft_make_altstring(char const *s, size_t start, char c, char quote)
{
	char	*division;
	size_t	i;
	size_t	str_len;

	i = 0;
	str_len = 0;
	if (s[i] == '\0' || s == 0)
		return (NULL);
	if (quote == 0)
		str_len = find_unquoted(s, c, start);
	else
		str_len = find_quoted(s, quote, start, c);
	division = (char *)ft_calloc(str_len + 1, sizeof(char));
	if (division == NULL)
		return (NULL);
	quote = 0;
	while (i < str_len)
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
				break ;
		}
		if (s[start] == 0 || (s[start] == c && quote == 0))
			break ;
		if (c == ' ')
			special_check((char *)&s[start], quote);
		division[i++] = s[start++];
	}
	division[i] = '\0';
	return (division);
}

static char	**ft_clear(char **array, size_t arr_index)
{
	while (arr_index-- > 0)
		free(array[arr_index]);
	free(array);
	return (NULL);
}

static char	**ft_make_altsplit(char **array, char const *s, char c)
{
	int		i;
	int		in_arr;
	int		arr_index;
	char	quote;

	i = -1;
	in_arr = 0;
	arr_index = 0;
	quote = 0;
	if (s == NULL)
		return (NULL);
	while (s[++i] != '\0')
	{
		quote = find_quotetype(s, &i, quote, &in_arr);
		if (s[i] != c && in_arr == 0)
		{
			array[arr_index++] = ft_make_altstring(s, i, c, quote);
			if (array[arr_index - 1] == NULL)
				return (ft_clear(array, arr_index));
			in_arr = 1;
		}
		else if ((s[i] == c && quote == 0))
			in_arr = 0;
	}
	if (arr_index > 0 && !ft_strncmp(array[arr_index - 1], "", 1))
		array[arr_index - 1] = 0;
	else
		if (array)
			array[arr_index] = 0;
	return (array);
}

char	**ft_altsplit(char *s, char c)
{
	char	**array;

	array = (char **)ft_calloc(ft_altcount_arr(s, c) + 2, sizeof(char *));
	if (array == NULL)
		return (NULL);
	array = ft_make_altsplit(array, s, c);
	if (array == NULL)
		return (NULL);
	else
		return (array);
}
