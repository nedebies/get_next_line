/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndebiesm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:14:21 by ndebiesm          #+#    #+#             */
/*   Updated: 2019/10/28 10:15:17 by ndebiesm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "get_next_line.h"

int		adjust_content(int fd, char **line, char **opened_files)
{
	int		check;

	check = ft_strchr(*line, '\n');
	free(opened_files[fd]);
	if (check != -1)
	{
		if (!(opened_files[fd] = ft_strdup(*line + check + 1)))
			return (-1);
		if (!(*line = ft_substr(*line, 0, check)))
			return (-1);
	}
	else
	{
		opened_files[fd] = NULL;
		return (0);
	}
	return (1);
}

int		read_line(int fd, char **line, char **opened_files)
{
	int		ret;
	char	*buffer;
	int		check;

	if (!(buffer = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	if (!(*line = ft_strdup(opened_files[fd])))
		return (-1);
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (!(*line = ft_strjoin(*line, buffer)))
			return (-1);
		check = ft_strchr(*line, '\n');
		if (check != -1)
			break ;
	}
	free(buffer);
	if (ret < 0)
		return (-1);
	return (adjust_content(fd, line, opened_files));
}

int		get_next_line(int fd, char **line)
{
	static char		*opened_files[OPEN_MAX];

	if (fd < 0 || fd > OPEN_MAX || !line)
		return (-1);
	if (BUFFER_SIZE < 1)
		return (-1);
	if (!opened_files[fd])
		if (!(opened_files[fd] = ft_strdup("")))
			return (-1);
	return (read_line(fd, line, opened_files));
}
