/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:18:19 by mtani             #+#    #+#             */
/*   Updated: 2023/10/16 12:12:12 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdlib.h>
//#include "ft_strlen.c"
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	int		i;

	dst = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/*int main() 
{
    const char *str = "Ciao, mondo!"; // La stringa da duplicare
    char *duplicate;

    // Utilizza la funzione strdup per duplicare la stringa
    duplicate = strdup(str);

    if (duplicate != NULL) {
        // Stampa la stringa duplicata
        printf("La stringa duplicata è: %s\n", duplicate);

        // Libera la memoria allocata per la stringa duplicata
        free(duplicate);
    } else {
        printf("Errore durante la duplicazione della stringa.\n");
    }

    return 0;
}*/
