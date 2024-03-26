/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:09:10 by mtani             #+#    #+#             */
/*   Updated: 2023/10/14 16:14:02 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stddef.h>
//#include <strings.h> 
//#include "ft_strlen.c"
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		lilsize;

	i = 0;
	j = 0;
	lilsize = ft_strlen(little);
	if (lilsize == 0)
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[i + j] == little[j] && big[i + j] && (i + j) < len)
				j++;
			if (j == lilsize)
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

/*int main() {
    const char *big = "1232123";
    const char *little = "12321";
    size_t len = ft_strlen(big);

    // Chiamata alla funzione personalizzata ft_strnstr
    char *result = ft_strnstr(big, little, len);

    // Stampa il risultato
    if (result != NULL) {
        printf("La sottostringa è stata trovata: %s\n", result);
    } else {
        printf("La sottostringa non è stata trovata.\n");
    }
    return 0;
}*/
