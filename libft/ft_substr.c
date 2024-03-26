/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:57:18 by mtani             #+#    #+#             */
/*   Updated: 2023/10/16 16:16:28 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdlib.h>
//#include <stdio.h>
//#include "ft_strlen.c"
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start > s_len)
		start = s_len;
	if (len > (s_len - start))
		len = (s_len - start);
	if (start == s_len)
		sub = (char *)malloc(sizeof(char));
	else
		sub = (char *)malloc((sizeof(char) * len) + 1);
	if (sub == NULL)
		return (NULL);
	while (i < len && s[start] != '\0' && start < s_len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

/*int main()
{
	//char esempio[] = "Hello my baby hello my honey hello my ragtime gal";
	
	printf("%s\n", ft_substr("hola", 0, 18446744073709551615));
}*/
