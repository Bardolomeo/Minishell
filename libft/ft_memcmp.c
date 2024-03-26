/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:47:21 by mtani             #+#    #+#             */
/*   Updated: 2023/10/14 13:48:42 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdlib.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	if (n <= 0)
		return (0);
	while (i < n && tmp1[i] == tmp2[i])
		i++;
	if (i == n)
		return (tmp1[i - 1] - tmp2[i - 1]);
	else
		return (tmp1[i] - tmp2[i]);
}

/*int main()
{
	char string1[] = "Hello my baby";
	char string2[] = "Hello my honey";

	printf("%i", ft_memcmp(string1, string2, 12));
}*/
