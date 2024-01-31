/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 22:31:24 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/31 22:43:25 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_tab_exec(char **tab_exec)
{
    int i;

    if (!tab_exec)
        return ;
    i = 0;
    while (tab_exec[i])
	{
		free(tab_exec[i]);
		tab_exec[i] = NULL;
        i++;
	}
	free(tab_exec);
    tab_exec = NULL;
}

void free_redirs(t_node *node)
{
    if (node->redir_in)
    {
        free(node->redir_in);
        node->redir_in = NULL;
    }
    if (node->redir_out)
    {
        free(node->redir_out);
        node->redir_out = NULL;
    }
    if (node->redir_append)
    {
        free(node->redir_append);
        node->redir_append = NULL;
    }
}

void free_nodes(t_node *node)
{
    t_node *tmp_node;

    if (!node)
        return ;
    while (node)
    {
        tmp_node = node;
        node = node->next;
        free_tab_exec(tmp_node->tab_exec);
        free_redirs(tmp_node);
        free(tmp_node);
        tmp_node = NULL;
    }
}

// void free_nodes(t_node *node)
// {
//     t_node *tmp_node;

//     if (!node)
//         return ;
//     tmp_node = node;
//     while (tmp_node)
//     {
//         free_tab_exec(tmp_node->tab_exec);
//         free_redirs(tmp_node);
//         tmp_node = tmp_node->next;
//     }
//     free(node);
//     node = NULL;
// }

void	ft_node_delone(t_node *node)
{
	if (!node)
		return ;
	if (node)
	{
		free_tab_exec(node->tab_exec);
        free_redirs(node);
		free(node);
        node = NULL;
	}
}

void	clear_single_node(t_node **node)
{
	t_node	*tmp;

	while (*node)
	{
		tmp = (*node)->next;
		ft_node_delone(*node);
		*node = tmp;
	}
	*node = NULL;
}

void	ft_free_tab(char **s, int i)
{
	while (i-- > 0)
	{
		if (s[i])
		{
			free(s[i]);
			s[i] = NULL;
		}
	}
	free(s);
}

void free_tokens(t_token *token)
{
    t_token *tmp_token;

    if (!token)
        return ;
    while (token)
    {
        tmp_token = token->next;
        if (token->str)
        {
            free(token->str);
            token->str = NULL;
        }
        free(token);
        token = tmp_token;
    }
}

void free_data(t_data *data)
{
    if (!data)
        return ;
    if (data->str)
    {
        free(data->str);
        data->str = NULL;
        // data->env = NULL; // il n'y a qu'un seul env dans minishell 
            // (le mettre a null empechera la structure data de le free je suppose donc a tester)
            // comme ca on enleve la reference vers la zone memoire sans la detruire
    }
    free(data);
    data = NULL;
}
