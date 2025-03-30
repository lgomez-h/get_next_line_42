/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-h <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:20:59 by lgomez-h          #+#    #+#             */
/*   Updated: 2024/10/19 12:21:02 by lgomez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char		*ft_strchr(const char *str, int c);
void		ft_read(int fd, char *buf_tmp, char **str);
static char	*ft_get_line(int fd, char **str);
size_t		ft_strlen(const char *c);

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

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*buf_tmp;

	buf_tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf_tmp)
	{
		return (NULL);
	}
	if (fd == -1 || BUFFER_SIZE < 1)
	{
		free(buf_tmp);
		return (NULL);
	}
	ft_read(fd, buf_tmp, str);
	free(buf_tmp);
	return (ft_get_line(fd, str));
}

void	ft_read(int fd, char *buf_tmp, char **str)
{
	int		i;
	char	*tmp;

	if (!str[fd] || !ft_strchr(str[fd], '\n'))
	{
		i = read(fd, buf_tmp, BUFFER_SIZE);
		while (i > 0)
		{
			buf_tmp[i] = '\0';
			if (!str[fd])
				str[fd] = ft_strdup(buf_tmp);
			else
			{
				tmp = str[fd];
				str[fd] = ft_strjoin(str[fd], buf_tmp);
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

static char	*ft_get_line(int fd, char **str)
{
	char	*line;
	char	*with_nl;
	size_t	len_line;

	if (!str[fd] || !*str[fd])
		return (free(str[fd]), str[fd] = NULL, NULL);
	with_nl = ft_strchr(str[fd], '\n');
	if (!with_nl)
	{
		line = str[fd];
		str[fd] = NULL;
	}
	else
	{
		len_line = with_nl - str[fd] + 1;
		line = (char *)malloc(len_line + 1);
		if (!line)
			return (NULL);
		ft_strlcpy(line, str[fd], len_line + 1);
		ft_memmove(str[fd], with_nl + 1, ft_strlen(with_nl + 1) + 1);
	}
	return (line);
}
/*#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

int	main(int argc, char **argv)
{
	int		fd[OPEN_MAX];
	char	*line;
	int		files_remaining;
	int		i;

	if (argc < 2)
	{
		printf("Uso: %s archivo1 [archivo2 ... archivoN]\n", argv[0]);
		return (1);
	}
	
	// Abrir archivos y contar cuántos están disponibles
	files_remaining = 0;
	for (i = 1; i < argc && i <= OPEN_MAX; i++)
	{
		fd[i - 1] = open(argv[i], O_RDONLY);
		if (fd[i - 1] == -1)
		{
			perror("Error al abrir el archivo");
			fd[i - 1] = -1; // Marcar FD inválido
		}
		else
			files_remaining++;
	}

	// Leer y alternar entre archivos
	while (files_remaining > 0)
	{
		for (i = 0; i < argc - 1 && i < OPEN_MAX; i++)
		{
			if (fd[i] != -1)  // Asegurarse de que el FD es válido
			{
				line = get_next_line(fd[i]);
				if (line)
				{
					printf("Archivo %s: %s", argv[i + 1], line);
					free(line);
				}
				else
				{
					close(fd[i]);
					fd[i] = -1;
					files_remaining--;
				}
			}
		}
		printf("Presiona Enter para mostrar la siguiente línea...\n");
		getchar();  // Espera a que el usuario presione Enter para continuar
	}
	return (0);
}*/
/*#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

int	main(void)
{
	char	*line;

	printf("Escribe algo (presiona Ctrl+D para terminar):\n");
	line = get_next_line(0);  // Usa `0` 
	para leer desde el teclado (entrada estándar)
	while (line)
	{
		printf("Linea leída: %s", line);
		free(line);
		line = get_next_line(0);
	}
	line = NULL;
	return (0);
}*/
