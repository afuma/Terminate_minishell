/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:04:50 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/30 21:55:22 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int    init_pipe_fds(int *pipe_fds, t_node *node)
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

static void    manage_parent_process(int *in_fd, int *pipe_fds,
    t_node *current_node)
{
    if (*in_fd != STDIN_FILENO)
        close(*in_fd);
    if (current_node->next != NULL)
    {
        close(pipe_fds[1]);
        *in_fd = pipe_fds[0];
    }
    else
    {
        close(pipe_fds[1]);
        if (pipe_fds[0] != -1)
            close(pipe_fds[0]);
        *in_fd = -1;
    }
}

static void    init_pids_array(int *pids, int max_cmds)
{
    int    index;

    index = 0;
    while (index < max_cmds)
    {
        pids[index] = -1;
        index++;
    }
}

static void    wait_for_children(int *pids, int num_cmds)
{
    int    index;
    int    status;

    index = 0;
    while (index < num_cmds)
    {
        if (pids[index] > 0)
            waitpid(pids[index], &status, 0);
        index++;
    }
}

void    exec_pipeline(t_node *node, t_env *env)
{
    int    pipe_fds[2];
    int    pids[1024];
    int    num_cmds;
    int    in_fd;

    num_cmds = 0;
    in_fd = STDIN_FILENO;
    init_pids_array(pids, 1024);
    while (node != NULL && num_cmds < 1024)
    {
        if (init_pipe_fds(pipe_fds, node) == -1)
            break ;
        pids[num_cmds] = fork();
        if (pids[num_cmds] == -1)
            break ;
        if (pids[num_cmds] == 0)
            exec_child_process(node, in_fd, env, pipe_fds);
        else
            manage_parent_process(&in_fd, pipe_fds, node);
        node = node->next;
        num_cmds++;
    }
    if (in_fd != -1)
        close(in_fd);
    wait_for_children(pids, num_cmds);
}
