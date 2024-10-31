/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 04:54:57 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/31 03:23:59 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_to_temp(int fd, char *line)
{
	if (!line)
	{
		if (write(fd, "\n\n", ft_strlen(line)) == -1)
			return (-1);
	}
	if (write(fd, line, ft_strlen(line)) == -1)
		return (error_msg("Problem writing to temp.txt"), free(line), close(fd),
			-1);
	if (write(fd, "\n", 1) == -1)
		return (error_msg("Problem writing newline to temp.txt"), free(line),
			close(fd), -1);
	return (0);
}

int	here_doc_management(char *limiter, char *name_file, t_shell *shell)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = open(name_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (error_msg("Problem opening temp.txt"));
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, limiter) == 0 || len == 0)
			return (ft_printf("\n"), free(line), close(fd), 0);
		line = replace_in_charstar(&line, shell);
		if (write_to_temp(fd, line) == -1)
			return (-1);
		free(line);
	}
	return (free(line), close(fd), 0);
}

int	delete_all_temp_files(int total_here_doc)
{
	int		i;
	char	*name_file;

	i = 0;
	while (i < total_here_doc)
	{
		name_file = name_files_here_doc(i);
		if (unlink(name_file) == -1)
			return (error_msg("Problem deleting temp.txt"), -1);
		free(name_file);
		i++;
	}
	return (0);
}
