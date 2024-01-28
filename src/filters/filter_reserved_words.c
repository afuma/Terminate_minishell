/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_reserved_words.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:47:33 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/25 19:44:30 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool filter_authorized_word(char *str)
{
    return (!filter_reserved_word(str));
}

bool filter_reserved_word(char *str)
{
    return (
        ft_strcmp(str, "if") == 0 || 
        ft_strcmp(str, "then") == 0 || 
        ft_strcmp(str, "elif") == 0 || 
        ft_strcmp(str, "else") == 0 || 
        ft_strcmp(str, "time") == 0 || 
        ft_strcmp(str, "for") == 0 || 
        ft_strcmp(str, "in") == 0 || 
        ft_strcmp(str, "until") == 0 || 
        ft_strcmp(str, "while") == 0 || 
        ft_strcmp(str, "done") == 0 || 
        ft_strcmp(str, "case") == 0 || 
        ft_strcmp(str, "esac") == 0 || 
        ft_strcmp(str, "coproc") == 0 || 
        ft_strcmp(str, "select") == 0 || 
        ft_strcmp(str, "{") == 0 || 
        ft_strcmp(str, "}") == 0 || 
        ft_strcmp(str, "[[") == 0 || 
        ft_strcmp(str, "]]") == 0 || 
        ft_strcmp(str, "!") == 0);
}