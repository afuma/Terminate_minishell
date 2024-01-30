/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:02:01 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/30 18:10:11 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void    free_env_link(t_env_link *link)
{
    if (link)
    {
        free(link->name);
        link->name = NULL;
        free(link->content);
        link->content = NULL;
        free(link);
        link = NULL;
    }
}

void    free_env(t_env *env)
{
    t_env_link    *current;
    t_env_link    *tmp;

    if (env && env->first)
    {
        current = env->first;
        while (current)
        {
            tmp = current;
            current = current->next;
            free_env_link(tmp);
        }
        printf("env->first = %p", env->first);
        free(env);
        env = NULL;
    }
}