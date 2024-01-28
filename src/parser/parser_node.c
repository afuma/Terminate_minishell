/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:04:42 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/28 14:48:34 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node *create_node(t_data *data)
{
    t_node *node;
    
    node = malloc(sizeof(t_node));
    if (!node)
        return (NULL);
    node->id = data->nb_nodes;
    node->type = 1;
    node->tab_exec = NULL;
    node->redir_in = NULL;
    node->redir_out = NULL;
    node->redir_append = NULL;
    node->redir_heredoc = NULL;
    node->next = NULL;
    return (node);
}

void add_node(t_data *data)
{
    t_node *new_node;
    t_node *temp;

    new_node = create_node(data);
    if (new_node)
    {
        if (data->node == NULL)
            data->node = new_node;
        else
        {
            temp = data->node;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = new_node;
        }
    }
}

// c'est le premier token ou le premier token apres un pipe
bool delimit_node(t_data *data, t_token *token)
{
    if (token == NULL)
        return (false);
    data->start = token->id;
    while (token->next != NULL)
    {
        if (token->next->type_token == T_PIPE)
        {
            data->end = token->id;
            return (true);
        }
        token = token->next;
    }
    if (!token->next)
    {
        data->end = token->id;
        return (true);
    }
    return (true);
}

void init_nodes(t_data *data)
{
    int nb_nodes;
    int i;

    i = 0;
    data->start = 0;
    data->end = 0;
    nb_nodes = compt_nodes(data);
    if (nb_nodes < 0)
        ft_error("Il n'y a pas de pipes..");
    while (i < nb_nodes)
    {
        add_node(data);
        data->nb_nodes++;
        i++;
    }
}

bool fill_nodes(t_data *data)
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
        node->tab_exec = init_tab_exec(data, token);
        if (!init_redir(data, node, token))
            return ("erreur");
        node = node->next;
    }
    return (true);
}
