/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:57:41 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/31 19:35:59 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	execute_command(t_node *node, char **envp)
{
	char	*cmd_path;

	if (ft_strchr(node->tab_exec[0], '/'))
		cmd_path = ft_strdup(node->tab_exec[0]);
	else
		cmd_path = get_cmd_path(node->tab_exec[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(node->tab_exec[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return (false);
	}
	if (execve(cmd_path, node->tab_exec, envp) == -1)
	{
		perror("execve error");
		free(cmd_path);
		return (false);
	}
	return (true);
}

static bool	setup_child(t_node *node, int in_fd, int *pipe_fds)
{
	if (!exec_redir(node))
		return (false);
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 error");
			return (false);
		}
		if (in_fd != -1)
			close(in_fd);
	}
	if (node->next)
	{
		if (pipe_fds[0] != -1)
			close(pipe_fds[0]);
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 error");
			return (false);
		}
		if (pipe_fds[1] != -1)
			close(pipe_fds[1]);
	}
	return (true);
}

void	exec_child_process(t_node *node, int in_fd, t_env *env, int *pipe_fds)
{
	char	**envp;
	int		exit_status;

	envp = convert_env_to_tab(env);
	exit_status = EXIT_FAILURE;
	if (setup_child(node, in_fd, pipe_fds))
	{
		if (is_builtin(node))
		{
			exec_builtin(node, env);
			exit_status = env->lst_exit;
		}
		else if (execute_command(node, envp))
			exit_status = EXIT_SUCCESS;
	}
	free_tab(envp);
	free_nodes(node);
	node = NULL;
	free_env(env);
	exit(exit_status);
}

// void	exec_child_process(t_node *node, int in_fd, t_env *env, int *pipe_fds)
// {
// 	char	**envp;

// 	envp = convert_env_to_tab(env);
// 	if (exec_redir(node) == false)
// 		(free_tab(envp), exit(EXIT_FAILURE));
// 	if (in_fd != STDIN_FILENO)
// 	{
// 		if (dup2(in_fd, STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 error");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(in_fd);
// 	}
// 	if (node->next)
// 	{
// 		close(pipe_fds[0]);
// 		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
// 			(perror("dup2 error"), exit(EXIT_FAILURE));
// 		close(pipe_fds[1]);
// 	}
// 	if (is_builtin(node))
// 		(free_tab(envp), exec_builtin(node, env), free_node(node),
// 			free_env(env), free_tab(envp), exit(EXIT_SUCCESS));
// 	execute_command(node, envp);
// 	free_tab(envp);
// 	exit(EXIT_FAILURE);
// }