/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_altsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:11:44 by mtani             #+#    #+#             */
/*   Updated: 2024/05/06 13:12:50 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_make_altstring(char const *s, size_t start, char c, char quote)
{
	char	*division;
	size_t	i;
	size_t	str_len;

	i = 0;
	if (s[i] == '\0' || s == 0)
		return (NULL);
	str_len = ft_altstrlen(s, start, c, quote);
	division = (char *)ft_calloc(str_len + 1, sizeof(char));
	if (division == NULL)
		return (NULL);
	quote = 0;
	while (i < str_len)
	{
		skip_quotes(s, &start, &quote);
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

static char	**end_array(int arr_index, char ***array)
{
	if (arr_index > 0 && !ft_strncmp((*array)[arr_index - 1], "", 1))
		(*array)[arr_index - 1] = 0;
	else
		if (*array)
			(*array)[arr_index] = 0;
	return (*array);
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
	return (end_array(arr_index, &array));
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
