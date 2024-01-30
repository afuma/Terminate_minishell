/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:15:34 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/29 20:10:12 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	redir_in(t_node *node)
{
	int	fd_in;

	fd_in = open(node->redir_in, O_RDONLY);
	if (fd_in < 0)
		return (perror("open"), EXIT_FAILURE);
	if (dup2(fd_in, STDIN_FILENO) < 0)
	{
		close(fd_in);
		return (perror("dup2"), EXIT_FAILURE);
	}
	close(fd_in);
	return (EXIT_SUCCESS);
}

static int	redir_out(int fd, const char *file, bool type_redir)
{
	int	file_fd;

	if (!type_redir)
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd < 0)
		return (perror("open"), EXIT_FAILURE);
	if (dup2(file_fd, fd) < 0)
	{
		close(file_fd);
		return (perror("dup2"), EXIT_FAILURE);
	}
	close(file_fd);
	return (EXIT_SUCCESS);
}

// static int	redir_append(t_node *node)
// {
// 	int	fd_append;

// 	fd_append = open(node->redir_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd_append < 0)
// 		return (perror("open"), EXIT_FAILURE);
// 	if (dup2(fd_append, STDOUT_FILENO) < 0)
// 	{
// 		close(fd_append);
// 		return (perror("dup2"), EXIT_FAILURE);
// 	}
// 	close(fd_append);
// 	return (EXIT_SUCCESS);
// }

// static int	redir_heredoc(t_node *node)
// {
// 	int	fd_heredoc;

// 	fd_heredoc = open(node->redir_heredoc, O_RDONLY);
// 	if (fd_heredoc < 0)
// 		return (perror("open"), EXIT_FAILURE);
// 	if (dup2(fd_heredoc, STDIN_FILENO) < 0)
// 	{
// 		close(fd_heredoc);
// 		return (perror("dup2"), EXIT_FAILURE);
// 	}
// 	close(fd_heredoc);
// 	return (EXIT_SUCCESS);
// }

int	exec_redir(t_node *node)
{
	if (node->redir_in && is_redir_in(node->redir_in) && redir_in(node))
		return (EXIT_FAILURE);
	if (node->redir_out && is_redir_out(node->redir_out, 0) && \
		redir_out(STDOUT_FILENO, node->redir_out, 0))
	{
		return (EXIT_FAILURE);
	}
	if (node->redir_append && is_redir_out(node->redir_append, 1) && \
		redir_out(STDOUT_FILENO, node->redir_append, 1))
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
	// if (node->redir_err && is_redir_out(node->redir_out, 0) &&
	// redir_out(STDERR_FILENO, node->redir_err, 0))
	// {
	// 	return (EXIT_FAILURE);
	// }
	// if (node->redir_heredoc && redir_heredoc(node))
	// 	return (EXIT_FAILURE);
}
