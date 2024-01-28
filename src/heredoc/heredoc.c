/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:03:00 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/28 12:43:52 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_redir_heredoc(t_state ttoken_1, t_state ttoken_2)
{
	return (ttoken_1 == T_REDIR_HEREDOC && ttoken_2 == T_FILE);
}

bool sub_process_heredoc(t_env *env, t_node *node, char *delimiter)
{
    int fd;
    int old_fd;
    
    old_fd = dup(STDIN_FILENO);
    fd = open(node->redir_heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        close(old_fd);
        return (false);
    }
	get_and_save_heredoc_content(env, fd, delimiter);
	node->redir_heredoc = get_name_heredoc();
    close(fd);
    if (dup2(old_fd, STDIN_FILENO) < 0)
    {
        close(old_fd);
        return (false);
    }
	close(old_fd);
    return (true);
}

bool process_heredoc(t_data *data, t_node *node)
{
    t_token *token;

    token = data->token;
    while (token)
    {
		if (token && token->next && in_node(data, token))
		{
			if (is_redir_heredoc(token->type_token, token->next->type_token))
			{
				if (!sub_process_heredoc(data->env, node, token->next->str))
					return (false);
			}
		}
        token = token->next;
    }
    return (true);
}

bool fill_heredoc(t_data *data)
{
    t_node *node;
    t_token *token;

    node = data->node;
    token = data->token;
    while (node)
    {
        token = get_first_token(data, node, token);
        if (!delimit_node(data, token))
            return ("erreur");
        if (!process_heredoc(data, node))
            return ("erreur");
        node = node->next;
    }
    data->start = 0;
    data->end = 0;
    return (true);
}