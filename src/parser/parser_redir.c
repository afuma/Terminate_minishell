/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:15:57 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/29 19:47:52 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool sub_process_heredoc(t_env *env, t_node *node, char *delimiter)
{
    int fd;
    
	node->redir_in = get_name_heredoc();
    fd = open(node->redir_in, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (false);
    get_and_save_heredoc_content(env, fd, delimiter);
    close(fd);
    return (true);
}

bool update_redir(t_env *env, t_node *node, t_token *token)
{
    char *name;

    name = get_name_redir(token);
    if (is_file_redir(token))
    {
        if (token->type_token == T_REDIR_IN)
            node->redir_in = name;
        if (token->type_token == T_REDIR_OUT)
        {
            node->redir_out = name;
            node->redir_append = NULL;
        }
        if (token->type_token == T_REDIR_APPEND)
        {
            node->redir_append = name;
            node->redir_out = NULL;
        }
        if (token->type_token == T_REDIR_HEREDOC)
        {
            if (!sub_process_heredoc(env, node, token->next->str))
                return (false);
        }
    }
    return (true);
}

bool init_redir(t_data *data, t_node *node, t_token *token)
{
    while (token && in_node(data, token))
    {
        if (!update_redir(data->env, node, token))
            return (perror("fd in redir failed !"), false);
        token = token->next;
    }
    return (true);
}