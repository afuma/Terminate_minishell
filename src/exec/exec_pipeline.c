/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:04:50 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/28 16:09:22 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	init_pipe_fds(int *pipe_fds, t_node *node)
{
	if (node->next != NULL)
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("pipe error");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		pipe_fds[0] = -1;
		pipe_fds[1] = -1;
	}
	return (EXIT_SUCCESS);
}

static void	exec_child_process(t_node *node, int in_fd, t_env *env, int *pipe_fds)
{
	char	**envp;

	envp = convert_env_to_tab(env);
	if (exec_redir(node) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 error");
			exit(EXIT_FAILURE);
		}
		close(in_fd);
	}
	if (node->next)
	{
		close(pipe_fds[0]);
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			(perror("dup2 error"), exit(EXIT_FAILURE));
		close(pipe_fds[1]);
	}
	if (is_builtin(node))
		exit(exec_builtin(node, env));
	execute_command(node, envp);
	exit(EXIT_SUCCESS);
}

static void	manage_parent_process(int *in_fd, int *pipe_fds,
	t_node *current_node, int pid)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (current_node->next != NULL)
	{
		close(pipe_fds[1]);
		*in_fd = pipe_fds[0];
	}
	else
		*in_fd = -1;
	waitpid(pid, NULL, 0);
}

void	exec_pipeline(t_node *node, t_env *env)
{
	int	pipe_fds[2];
	int	pid;
	int	in_fd;

	in_fd = STDIN_FILENO;
	while (node != NULL)
	{
		if (init_pipe_fds(pipe_fds, node) == -1)
			return ;
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			exec_child_process(node, in_fd, env, pipe_fds);
		else
			manage_parent_process(&in_fd, pipe_fds, node, pid);
		if (node->next == NULL && in_fd != -1)
			close(in_fd);
		node = node->next;
	}
}
// void exec_pipeline(t_node *node, char **envp, t_env *env) {
//     int pipe_fds[2];
//     int pid;
//     int in_fd = STDIN_FILENO;
//     t_node *current_node = node;

//     while (current_node) {
//         if (current_node->next) {
//             if (pipe(pipe_fds) == -1) {
//                 perror("pipe error");
//                 exit(EXIT_FAILURE);
//             }
//         }

//         pid = fork();
//         if (pid == -1) {
//             perror("fork error");
//             exit(EXIT_FAILURE);
//         }

//         if (pid == 0) { // Processus enfant
//             if (in_fd != STDIN_FILENO) {
//                 if (dup2(in_fd, STDIN_FILENO) == -1) {
//                     perror("dup2 error");
//                     exit(EXIT_FAILURE);
//                 }
//                 close(in_fd);
//             }
//             if (current_node->next != NULL) {
//                 close(pipe_fds[0]);
//                 if (dup2(pipe_fds[1], STDOUT_FILENO) == -1) {
//                     perror("dup2 error");
//                     exit(EXIT_FAILURE);
//                 }
//                 close(pipe_fds[1]);
//             }
//             if (is_builtin(current_node))
//                 exit(exec_builtin(current_node, env));
//             execute_command(current_node, envp);
//             exit(EXIT_SUCCESS);
//         } else { // Processus parent
//             if (in_fd != STDIN_FILENO)
//                 close(in_fd);
//             if (current_node->next != NULL) {
//                 close(pipe_fds[1]);
//                 in_fd = pipe_fds[0];
//                 in_fd = -1; // Aucun pipe supplémentaire pour le dernier nœud
//             }
//             waitpid(pid, NULL, 0);
//         }
//         current_node = current_node->next;
//     }

//     if (in_fd != STDIN_FILENO) {
//         close(in_fd);
// }
