/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:15:34 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/31 20:44:44 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	redir_in(t_node *node)
{
	int	fd_in;

	fd_in = open(node->redir_in, O_RDONLY);
	if (fd_in < 0)
		return (perror("open"), false);
	if (dup2(fd_in, STDIN_FILENO) < 0)
	{
		close(fd_in);
		return (perror("dup2"), false);
	}
	close(fd_in);
	return (true);
}

static bool	redir_out(int fd, const char *file, bool type_redir)
{
	int	file_fd;

	if (!type_redir)
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd < 0)
		return (perror("open"), false);
	if (dup2(file_fd, fd) < 0)
	{
		close(file_fd);
		return (perror("dup2"), false);
	}
	close(file_fd);
	return (true);
}

// static bool	redir_append(t_node *node)
// {
// 	int	fd_append;

// 	fd_append = open(node->redir_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd_append < 0)
// 		return (perror("open"), false);
// 	if (dup2(fd_append, STDOUT_FILENO) < 0)
// 	{
// 		close(fd_append);
// 		return (perror("dup2"), false);
// 	}
// 	close(fd_append);
// 	return (true);
// }

// static bool	redir_heredoc(t_node *node)
// {
// 	int	fd_heredoc;

// 	fd_heredoc = open(node->redir_heredoc, O_RDONLY);
// 	if (fd_heredoc < 0)
// 		return (perror("open"), false);
// 	if (dup2(fd_heredoc, STDIN_FILENO) < 0)
// 	{
// 		close(fd_heredoc);
// 		return (perror("dup2"), false);
// 	}
// 	close(fd_heredoc);
// 	return (true);
// }

bool	exec_redir(t_node *node)
{
	if (!exec_redir_1(node))
		return (false);
	if (!exec_redir_2(node))
		return (false);
	return (true);
}

bool	exec_redir_1(t_node *node)
{
	if (node->redir_in)
	{
		if (is_empty_file(node->redir_in) || \
			!is_redir_in(node->redir_in) || \
			!redir_in(node))
		{
			return (false);
		}
	}
	if (node->redir_out)
	{
		if (is_empty_file(node->redir_out)
			|| !is_redir_out(node->redir_out, 0)
			|| !redir_out(STDOUT_FILENO, node->redir_out, 0))
		{
			return (false);
		}
	}	
	return (true);
}

bool	exec_redir_2(t_node *node)
{
	if (node->redir_append)
	{
		if (is_empty_file(node->redir_append) || \
			!is_redir_out(node->redir_append, 1) || \
			!redir_out(STDOUT_FILENO, node->redir_append, 1))
		{
			return (false);
		}
	}
	return (true);
}
