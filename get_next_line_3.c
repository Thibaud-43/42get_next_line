/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 09:26:37 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/23 11:25:37 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

int		ft_read(char **line, char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\n')
	{
		*line = ft_substr((*str), 0, i);
		tmp = ft_strdup((*str) + (i + 1));
		free ((*str));
		(*str) = tmp;
		if ((*str)[0] == '\0')
		{
			free((*str));
			(*str) = NULL;
		}
	}
	else
	{
		*line = ft_strdup((*str));
		free((*str));
		(*str) = NULL;
	}
	return (1);
}

int		ft_generate_output(int fd, char **line, char *str[256], int bytes)
{
	if (bytes < 0)
		return (-1);
	else if (bytes == 0 && str[fd] == NULL)
		return (0);
	else
		return (ft_read(line, &str[fd]));

}

int		get_next_line(int fd, char **line)
{
	static char		*str[256];
	int				bytes;
	char			buf[BUFFER_SIZE + 1];
	char			*tmp;

	if (fd < 0 || fd >= 256 || !line || (read(fd, str[fd], 0) < 0))
		return (-1);
	while ((bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(str[fd], buf);
			free(str[fd]);
			str[fd] = tmp;
		}
		if ((ft_strchr(str[fd], '\n')))
			break;
	}	
	return ((ft_generate_output(fd, line, str, bytes)));
}


int main(void)
{
	int		fd;
	char 	*line;
	int		i;
	int		bytes;
	
	i = 1;
	fd = open("1.txt", O_RDONLY);
	bytes = 1;
	if (fd < 0)
		return (0);
	while (bytes)
	{
		bytes = get_next_line(fd, &line);
		printf("|bytes %d|%s\n", bytes, line);
		free(line);	
	}
	close (fd);
}
