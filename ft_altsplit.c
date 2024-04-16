/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_altsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:11:44 by mtani             #+#    #+#             */
/*   Updated: 2024/04/16 17:09:32 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if ((s[i] == '"' || s[i] == '\'') && quote == 0)
			quote = s[i];
		else if (s[i] == quote && quote != 0)
			quote = 0;
		if (s[i] != c && in_arr == 0)
		{
			count++;
			in_arr = 1;
		}
		else if (s[i] == c && quote == 0)
			in_arr = 0;
		i++;
	}
	return (count);
}

static char	*ft_make_altstring(char const *s, size_t start, char c, char quote)
{
	char	*division;
	size_t	i;
	size_t	str_len;
	int		dquotes;
	int		squotes;

	i = 0;
	str_len = 0;
	dquotes = 0;
	squotes = 0;
	if (s[i] == '\0' || s == 0)
		return (NULL);
	if (quote == 0)
		str_len = find_unquoted(s, c, start);
	else
		str_len = find_quoted(s, quote, start);
	division = (char *)ft_calloc(str_len + 1, sizeof(char));
	if (division == NULL)
		return (NULL);
	while (i < str_len)
	{
		if (s[start] == '"' && dquotes == 0 && squotes == 0)
			dquotes = 1;
		else if (s[start] == '"' && dquotes == 1)
			dquotes = 0;
		if (s[start] == '\'' && squotes == 0 && dquotes == 0)
			squotes = 1;
		else if (s[start] == '\'' && squotes == 1)
			squotes = 0;
		while ((s[start] == '\'' && dquotes == 0) || (s[start] == '"' && squotes == 0))
			start++;
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
		quote = find_quotetype(s, i, quote, &in_arr);
		if (s[i] != c && in_arr == 0 && s[i + 1] != '\'' && s[i + 1] != '\"')
		{
			array[arr_index++] = ft_make_altstring(s, i, c, quote);
			if (array[arr_index - 1] == NULL)
				return (ft_clear(array, arr_index));
			in_arr = 1;
		}
		else if (s[i] == c && quote == 0)
			in_arr = 0;
	}
	array[arr_index] = 0;
	return (array);
}

char	**ft_altsplit(char *s, char c)
{
	char	**array;

	array = (char **)ft_calloc(ft_altcount_arr(s, c) + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	array = ft_make_altsplit(array, s, c);
	if (array == NULL)
		return (NULL);
	else
		return (array);
}
