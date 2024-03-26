/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:24:45 by mtani             #+#    #+#             */
/*   Updated: 2023/10/14 15:37:43 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdlib.h>
#include "libft.h"

static int	ft_count_digits(int n)
{
	int			i;
	long long	num;

	num = (long long)n;
	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num *= -1;
		i++;
	}
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	long long		num;
	int				n_len;
	int				i;
	int				j;

	i = 0;
	n_len = ft_count_digits(n);
	j = n_len - 1;
	num = (long long)n;
	str = (char *)malloc(sizeof(char) * (n_len + 1));
	if (str == NULL)
		return (NULL);
	if (num < 0)
	{
		str[i++] = '-';
		num *= -1;
	}
	while (i++ < n_len)
	{
		str[j--] = (char)((num % 10) + 48);
		num /= 10;
	}
	str[i - 1] = '\0';
	return (str);
}

/*int main()
{
	//printf("%d\n", ft_count_digits(-2147483648));
	char *test = ft_itoa(-2147483648);
	printf("%s\n", test);
	free(test);
}*/
