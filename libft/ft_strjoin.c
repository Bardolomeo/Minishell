/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:12:33 by mtani             #+#    #+#             */
/*   Updated: 2024/03/28 15:08:09 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_strlen.c"
//#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;

	if (s2 == NULL)
		return ((char *)s1);
	if (s1 == NULL)
		return ((char *)s2);
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = (char *)ft_malloc(sizeof(char) * ((s1_len + s2_len) + 1));
	if (join == NULL)
		return (NULL);
	ft_memcpy(join, s1, s1_len);
	ft_memcpy(join + s1_len, s2, s2_len);
	join[s1_len + s2_len] = '\0';
	return (join);
}

/*int	main()
{
	char	s1[] = "lorem ipsum";
	char	s2[] = "dolor sit amet";

	char *result = ft_strjoin(s1, s2);
	printf("%s", result);
	free(result);
}*/
