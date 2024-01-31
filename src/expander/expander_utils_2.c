/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:27:15 by blax              #+#    #+#             */
/*   Updated: 2024/01/31 18:40:55 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char* copy_until_char(char *dest, char *src, char delimiter)
{
    size_t len_new_result;
    size_t len;
    size_t n;
    char *ptr;
    char *new_result;

    len = ft_strlen(dest);
    n = 0;
    ptr = src;
    while (*ptr && *ptr != delimiter)
    {
        n++;
        ptr++;
    }
    len_new_result = len + n + 1;
    new_result = malloc(sizeof(char) * len_new_result);
    ft_strlcpy(new_result, dest, len_new_result);
    ft_strlcat(new_result, src, len_new_result);

    return (new_result);
}

char* extract_var_name(char **str)
{
    const char *start;

    start = *str;
    while (ft_isalnum(**str) || **str == '_')
        (*str)++;
    return (ft_strndup(start, *str - start));
}

char* append_variable_value(t_env *env, char *result, char *var_name)
{
    char *var_value;
    size_t new_length;
    char *new_result;

    if (ft_strcmp(var_name, "?") == 0)
        var_value = ft_itoa(env->lst_exit);
    else
        var_value = get_env_name(env, var_name);
    if (var_value)
    {
        new_length = ft_strlen(result) + ft_strlen(var_value) + 1;
        new_result = malloc(sizeof(char) * new_length);
        ft_strlcpy(new_result, result, new_length);
        ft_strlcat(new_result, var_value, new_length);
        return (new_result);
    }

    return (ft_strdup(result));
}