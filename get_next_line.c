/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouchon <trouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 14:33:23 by trouchon          #+#    #+#             */
/*   Updated: 2020/11/23 16:38:14 by trouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
int ft_check_inputs(int fd, char **line)
{
	char	test[1];

	if (fd < 0 || fd > 256)
		return (1);
	else if ((read(fd, test, 0)) < 0)
		return (1);
	else if (!line)
		return (1);
	else if (BUFFER_SIZE < 1)
		return (1);
	return (0);
}

void	ft_set_line(char **line, char **str, int *ret)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i])
		i++;
	if ((*str)[i] == 0)
	{
		*line = ft_strdup(*str);
		free(*str);
		*str = NULL;
		*ret = 0;
	}
	else
	{
		*line = ft_substr((*str), 0, i);
		tmp = ft_strdup(&((*str)[i + 1]));
		free(*str);
		(*str) = tmp;
		if ((*str)[0] == '\0' && (BUFFER_SIZE != 1))
		{
			free(*str);
			*str = ft_strdup("");
		}
	}
}

int		get_next_line(int fd, char **line)
{
	static char		*str;
	char			*tmp;
	char			buf[BUFFER_SIZE + 1];
	int				ret;
	int				bytes;
		
	ret = 1;
	if (ft_check_inputs(fd, line))
		return (-1);
	while ((bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		if (!str)
			str = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(str, buf);
			free(str);
			str = tmp;
		}
		ret = 1;
		if (ft_strchr(str, '\n'))
			break;
	}
	if (bytes == 0 && str == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	ft_set_line(line, &str, &ret);
	return(ret);	
}
