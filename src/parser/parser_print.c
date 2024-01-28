/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:31:59 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/26 12:51:13 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_tab_exec(t_node *node)
{
    int i;

    i = 0;
    if (!node->tab_exec || !node->tab_exec[0])
        return ;
    printf("Cmd: %s\n", node->tab_exec[0]);
    while (node->tab_exec[i])
    {
        printf("    ");
        printf("arg %d: %s\n", i, node->tab_exec[i]);
        i++;
    }
    printf("\n");
}

void print_redir(t_node *node)
{
    printf("redir_in: %s\n", node->redir_in);
    printf("redir_out: %s\n", node->redir_out);
    printf("redir_append: %s\n", node->redir_append);
    printf("redir_heredoc: %s\n", node->redir_heredoc);
    printf("\n");
}

// Fonction pour afficher le contenu de tous les nodes
void print_nodes(t_data *data)
{
    t_node *node;

    node = data->node;
    if (!node)
        ft_error_2(data, "Il n'y a pas de node !");
    while (node != NULL)
	{
        printf("Node %d:\n", node->id);
        printf("type %d:\n", node->type);
        print_tab_exec(node);
        print_redir(node);
        node = node->next;
    }
}