/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:20:17 by lgomez-h          #+#    #+#             */
/*   Updated: 2024/10/19 12:20:24 by lgomez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	if (c == '\0')
	{
		return ((char *)str);
	}
	return (NULL);
}

static void	ft_read(int fd, char *buf_tmp, char **str)
{
	char	*tmp;
	int		i;

	if (!*str || !ft_strchr(*str, '\n'))
	{
		i = read(fd, buf_tmp, BUFFER_SIZE);
		while (i > 0)
		{
			buf_tmp[i] = '\0';
			if (!*str)
				*str = ft_strdup(buf_tmp);
			else
			{
				tmp = *str;
				*str = ft_strjoin(*str, buf_tmp);
				free(tmp);
			}
			if (ft_strchr(buf_tmp, '\n'))
			{
				break ;
			}
			i = read(fd, buf_tmp, BUFFER_SIZE);
		}
	}
}

static char	*ft_get_line(char **str)
{
	char	*line;
	char	*with_nl;
	size_t	len_line;

	if (!*str || !**str)
		return (free(*str), *str = NULL, NULL);
	with_nl = ft_strchr(*str, '\n');
	if (!with_nl)
	{
		line = *str;
		*str = NULL;
	}
	else
	{
		len_line = with_nl - *str + 1;
		line = (char *)malloc(len_line + 1);
		if (!line)
			return (NULL);
		ft_strlcpy(line, *str, len_line + 1);
		ft_memmove(*str, with_nl + 1, ft_strlen(with_nl + 1) + 1);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buf_tmp;

	buf_tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf_tmp)
	{
		return (0);
	}
	if (fd == -1 || BUFFER_SIZE < 1)
	{
		free(buf_tmp);
		return (0);
	}
	ft_read(fd, buf_tmp, &str);
	free(buf_tmp);
	return (ft_get_line(&str));
}
/*#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    // Abre el archivo en modo de solo lectura
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error al abrir el archivo");
        return (1);
    }

    // Lee cada línea y la imprime
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
        // Pausa hasta que el usuario presione Enter
        printf("Presiona Enter para continuar...\n");
        //getchar();  // Espera a que el usuario presione Enter
        line = NULL;
    }

    // Cierra el archivo
    close(fd);
    return (0);
}*/
