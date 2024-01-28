/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:04:42 by blax              #+#    #+#             */
/*   Updated: 2024/01/28 18:49:34 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int g_last_exit_status = 0;

bool is_expandable(t_token *token)
{
    if (!token)
        return (false);
    return (token->type_str == D_QUOTE || token->type_str == S_CHAR);
}

void expand_string(t_env *env, char *str)
{
    char *str_expand;

    if (!ft_strchr_bool(str, '$'))
        return ;
    str_expand = expand_variables(env, str);
    if (str_expand)
        replace_string(&str, str_expand);
}

void replace_string(char **original, const char *new_string)
{
    free(*original);
    *original = malloc(ft_strlen(new_string) + 1);
    if (!*original)
        return ;
    *original = ft_strcpy(*original, new_string);
}
