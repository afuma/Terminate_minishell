/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:25:56 by blax              #+#    #+#             */
/*   Updated: 2024/01/25 17:54:18 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_valid_varname_expand(char c)
{
    return (ft_isalpha(c) || c == '?');
}

// la decouper pour la rendre plus modulable
char* expand_variables(t_env *env, char *token_str)
{
    char *str;
    char *result;

    str = token_str;
    result = ft_strdup("");
    while (*str)
    {
        if (*str == '$')
        {
            if (*(str + 1) == '\0')
                return (result);
            if (is_valid_varname_expand(*(str + 1)))
                result = process_dollar_sign(env, &str, result);
        }
        else
            result = process_text_until_next_dollar(&str, result);
    }

    return (result);
}

char* process_dollar_sign(t_env *env, char **str, char *result)
{
    char *temp;
    char *varName;

    (*str)++; // Passer le symbole '$'
    varName = extract_var_name(str);
    temp = append_variable_value(env, result, varName);
    free(result);
    free(varName);

    return (temp);
}

char* process_text_until_next_dollar(char **str, char *result)
{
    char *nextDollar;
    char *temp;

    nextDollar = ft_strchr(*(str + 1), '$');
    if (!nextDollar)
        nextDollar = *str + ft_strlen(*str); // Si pas de '$', aller à la fin
    temp = copy_until_char(result, *str, *nextDollar);
    free(result);
    *str = nextDollar;

    return (temp);
}