/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_is_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:15:57 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/29 19:54:24 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_redir_out(char *name, int type_redir)
{
    int fd;

    if (access(name, F_OK))
    {
        if (!type_redir)
            fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else
            fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
            return (ft_error("open"), false);
        close(fd);
        return (true);
    }
    if (access(name, W_OK) == -1)
        return (ft_error("write access denied"), false); // enlever le false
    return (true);
}

bool is_redir_in(char *name)
{
    int fd;

    if (access(name, F_OK))
    {
        fd = open(name, O_RDONLY, 0644);
        if (fd < 0)
            return (ft_error("open"), false);
        close(fd);
        return (true);
    }
    if (access(name, R_OK) == -1)
        return (ft_error("read access denied"), false);
    return (true);
}