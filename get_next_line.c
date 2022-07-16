/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassouf <rkassouf@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 08:51:30 by rkassouf          #+#    #+#             */
/*   Updated: 2022/07/15 23:59:05 by rkassouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_getline(char *str)
{
	int		i;
	char	*line;

	if (!str || *str == '\0')
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i])
	{
		line[i] = str[i];
		i++;
		if (str[i - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_update(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	if (!str)
		return (NULL);
	j = 0;
	while (str[j] != '\n' && str[j])
		j++;
	if (str[j] == '\0')
	{
		free(str);
		return (NULL);
	}
	new_str = malloc(sizeof(char) * (ft_strlen(str) - j));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[++j])
		new_str[i++] = str[j];
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

char	*ft_read(int fd, char *buf, char *str)
{
	int		rd;
	char	*tmp;

	rd = 1;
	while (rd != 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			return (NULL);
		buf[rd] = '\0';
		tmp = str;
		if (!tmp)
			str = ft_strjoin("", buf);
		else
		{
			str = ft_strjoin(tmp, buf);
			free(tmp);
		}
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	str = ft_read(fd, buf, str);
	free(buf);
	if (!str)
		return (NULL);
	line = ft_getline(str);
	str = ft_update(str);
	return (line);
}
