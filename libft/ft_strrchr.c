/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:04:52 by mtani             #+#    #+#             */
/*   Updated: 2023/10/16 14:28:09 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_strlen.c"
//#include <stdlib.h>
//#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if ((unsigned char)s[len] == (unsigned char)c)
			return ((char *)s + len);
		len--;
	}
	return (NULL);
}

/*int main()
{
	char string[] = "Hello my baby hello my honey hello my ragtime gal";
	char *test = ft_strrchr(string, '\0');
	char *test2 = strrchr(string, '\0');
	printf("%s\n", test);
	printf("%s\n", test2);
}*/
