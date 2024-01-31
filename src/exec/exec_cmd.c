/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:57:41 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/31 13:12:49 by edesaint         ###   ########.fr       */
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
	free(cmd_path);
	return (true);
}

void    exec_child_process(t_node *node, int in_fd, t_env *env, int *pipe_fds)
{
    char    **envp;

    envp = convert_env_to_tab(env);
    if (!exec_redir(node))
        (free_nodes(node), exit(EXIT_FAILURE));
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