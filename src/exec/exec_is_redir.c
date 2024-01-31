/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_is_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:15:57 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/31 20:47:42 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_empty_file(char *name)
{
	if (name[0] == '\0')
		return (perror("empty file name"), true);
	return (false);
}

bool	is_redir_out(char *name, int type_redir)
{
	int	fd;

	if (access(name, F_OK))
	{
		if (!type_redir)
			fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (perror("open"), false);
		close(fd);
		return (true);
	}
	if (access(name, W_OK) == -1)
		return (perror("write access denied"), false);
	return (true);
}

bool	is_redir_in(char *name)
{
	int	fd;

	if (access(name, F_OK))
	{
		fd = open(name, O_RDONLY, 0644);
		if (fd < 0)
			return (perror("open"), false);
		close(fd);
		return (true);
	}
	if (access(name, R_OK) == -1)
		return (perror("read access denied"), false);
	return (true);
}
