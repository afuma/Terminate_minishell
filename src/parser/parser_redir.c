/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:15:57 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/26 17:48:32 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_redir_append(t_token *token, char *name)
{
    int fd;

    if (!token)
        return (false);
    if (token->type_token != T_REDIR_APPEND)
        return (false);
    if (access(name, F_OK) == -1)
    {
        fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
            return (ft_error("open"), false);
        close(fd);
        return (true);
    }
    if (access(name, W_OK) == -1)
        return (ft_error("write access denied"), false);
    return (true);
}

bool is_redir_out(t_token *token, char *name)
{
    int fd;

    if (!token)
        return (false);
    if (token->type_token != T_REDIR_OUT)
        return (false);
    if (access(name, F_OK) == -1)
    {
        fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
            return (ft_error("open"), false);
        close(fd);
        return (true);
    }
    if (access(name, W_OK) == -1)
        return (ft_error("write access denied"), false); // enlever le false
    return (true);
}

// verifie si il existe et que tu a le droit de le lire
bool is_redir_in(t_token *token, char *name)
{
    int fd;

    if (!token)
        return (false);
    if (token->type_token != T_REDIR_IN)
        return (false);
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

// bool is_redir_heredoc(t_token *token, char *name)
// {
//     int fd;
//     char *name;

//     if (!token)
//         return (false);
//     if (token->type_token != T_REDIR_HEREDOC)
//         return (false);
//     // code will (implementer le heredoc)
//     return (true);
// }

bool update_redir(t_node *node, t_token *token)
{
    char *name;

    name = get_name_redir(token);
    if (is_file_redir(token))
    {
        if (is_redir_in(token, name))
        {
            node->redir_in = name;
            if (!node->redir_in)
                return (false);
            node->redir_heredoc = NULL;
        }
        if (is_redir_out(token, name))
        {
            node->redir_out = name;
            if (!node->redir_out)
                return (false);
            node->redir_append = NULL;
        }
        if (is_redir_append(token, name))
        {
            node->redir_append = name;
            if (!node->redir_append)
                return (false);
            node->redir_out = NULL;
        }
        // if (is_redir_heredoc(token, name))
        // {
        //     node->redir_heredoc = name;
        //     node->redir_in = NULL;
        // }
    }
    return (true);
}

bool init_redir(t_data *data, t_node *node, t_token *token)
{
    while (token && in_node(data, token))
    {
        // creer une fonction pour parcourir tous les tokens et verifier si heredoc ou non
        // on recupere directement le delimiter que l'on utilise dans la fonction
        // et cette fonction creer le heredoc et met a jour le node (attribut heredoc)
        update_redir(node, token);
        token = token->next;
    }
    return (true);
}