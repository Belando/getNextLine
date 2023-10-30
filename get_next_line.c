/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelando <fbelando@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:45:19 by fbelando          #+#    #+#             */
/*   Updated: 2023/10/23 15:45:26 by fbelando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Lee datos desde un archivo o flujo de entrada, 
acumulandolos en el stash hasta que se encuentre un caracter 
de nueva linea o se alcance el final del archivo.
Se asigna memoria dinamica en buffer + 1 para el caracter nulo al 
final de la cadena. Se inicializa un bucle, mientras no llegue 
a nueva linea en el stash y mientras se sigan leyendo bytes del 
descriptor de archivo. Usamos read para leer hasta buffersize y
devolvemos los bytes leidos. Si devuelve -1 se liberan las memorias
asignadas y se devuelve null. Usamos strjoin para unir ambos contenidos
y devolvemos un puntero al stash.*/
char	*ft_read_to_stash(int fd, char *stash)
{
	char	*buffer;
	int		read_bytes;

	read_bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stash, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(stash);
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		stash = ft_strjoin_gnl(stash, buffer);
	}
	free(buffer);
	return (stash);
}

/* Obtiene una linea de texto hasta nueva linea, desde un stash (buffer) 
que almacena los datos leidos previamente. Si el primer caracter de stash es 
nulo, significa que no hay datos que leer en el stash y devuelve null. 
Entra en un bucle while que recorre el stash hasta que encuentre caracter
nulo o de nueva linea y aumenta el index para saber el tamaño de la linea.
Asignamos memoria dinamica en str con el tamaño de index + nueva linea y caracter
nulo. Si falla, retornamos null. Tras esto volvemos a dar 0 a index y copiamos 
el contenido del stash en str y avanzamos el index. Cuando encuentra salto de 
linea, lo copiamos, iteramos y despues colocamos el nulo y devolvemos el str.*/
char	*ft_get_line(char *stash)
{
	int		index;
	char	*str;

	index = 0;
	if (stash[index] == '\0')
		return (NULL);
	while (stash[index] != '\0' && stash[index] != '\n')
		index++;
	str = malloc(sizeof(char) * (index + 2));
	if (!str)
		return (NULL);
	index = 0;
	while (stash[index] != '\0' && stash[index] != '\n')
	{
		str[index] = stash[index];
		index++;
	}
	if (stash[index] == '\n')
	{
		str[index] = '\n';
		index++;
	}
	str[index] = '\0';
	return (str);
}

/* Crea un nuevo stash a partir de uno existente, eliminando la primera 
linea de texto hasta nueva linea. Entra en un bucle hasta que encuentra
salto de linea o nulo. Verifica stash en i_stash, si es nulo no encontro
caracter de nueva linea por lo que libera memoria del stash y devuelve null.
Memoria dinamica en str con tamaño del strlen de stash -i_stash + 1. Si falla
la reserva de memoria retornamos null. se incrementa i_stash para saltar nueva
linea o cualquier caracter adicional en el stash. Se copia el contenido restante 
del stash (tras la primera linea) en str. Se coloca nulo al final. liberamos 
la memoria en stash y devolvemos str.*/
char	*ft_new_stash(char *stash)
{
	int		i_stash;
	int		i_str;
	char	*str;

	i_stash = 0;
	while (stash[i_stash] != '\0' && stash[i_stash] != '\n')
		i_stash++;
	if (stash[i_stash] == '\0')
	{
		free(stash);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(stash) - i_stash + 1));
	if (!str)
		return (NULL);
	i_stash++;
	i_str = 0;
	while (stash[i_stash] != '\0')
		str[i_str++] = stash[i_stash++];
	str[i_str] = '\0';
	free(stash);
	return (str);
}

/* Lee y obtiene lineas de un archivo o flujo de entrada. Implementa 
una lectura linea por linea, donde cada llamada a la funcion devuelve la
siguiente linea. En la estatica stash almacenamos los datos leidos que aun
no se han procesado. Verifica si el fd es invalido < 0 o si el buffersize 
es <= 0. Devolviendo NULL. Sino llamamos a read_to_slash para leer datos y 
acumularlos en el stash. verifica si stash no es valido. y devuelve null.
Después llama a get_line para extraer la primera linea del stash y luego
a new_stash para eliminar la primera linea y actualizarlo. Devuelve line,
un puntero a la linea obtenida, en la siguiente llamada se continuara 
desde ahi.*/
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	stash = ft_new_stash(stash);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*line;

	fd = open("../test.txt", O_RDONLY);
	printf("LINE.1-> %s", get_next_line(fd));
	printf("----------------\n");
	printf("LINE.2-> %s", get_next_line(fd));
	printf("----------------\n");
	printf("LINE.3-> %s", get_next_line(fd));
	printf("----------------\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("LINE-> %s", line);
	}
	return (0);
}*/
