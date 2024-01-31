/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:04:08 by blax              #+#    #+#             */
/*   Updated: 2024/01/31 18:03:19 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	execute_single_cmd(t_node *node, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (!exec_redir(node))
			exit (EXIT_FAILURE);
		envp = convert_env_to_tab(env);
		if (!execute_command(node, envp))
			return (false);
		free(envp);
		free_node(node);
		free_env(env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_info = WEXITSTATUS(status);
	}
	return (true);
}

void	execute_command_node(t_node *node, t_env *env)
{
	// char	**envp;
	int		stdout_backup;

	stdout_backup = dup(STDOUT_FILENO);
	if (!node || !node->tab_exec || !node->tab_exec[0] || !node->type)
		(ft_putstr_fd("Invalid command\n", STDERR_FILENO), exit(1));
	if (node->id == 0 && node->next == NULL && is_builtin(node))
	{
		if (!exec_redir(node))
		{
			// free_nodes(node);
			return ;
		}
		if (node->tab_exec[0] && ft_strcmp(node->tab_exec[0], "exit") == 0)
			ft_putendl_fd("exit", STDOUT_FILENO);
		if (exec_builtin(node, env))
			free_node(node);
		if (dup2(stdout_backup, STDOUT_FILENO) < 0)
			(close(stdout_backup), exit(1));
		close(stdout_backup);
	}
	else if (node->next != NULL)
	{
		// envp = convert_env_to_tab(env);
		exec_pipeline(node, env);
		// free(envp);
	}
	else
	{
		// free(envp);
		execute_single_cmd(node, env);
	}
}
