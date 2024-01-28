/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 23:46:52 by blax              #+#    #+#             */
/*   Updated: 2024/01/26 12:50:03 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool ft_error(char *str)
{
    perror(str);
    return (false);
}

void ft_error_2(t_data *data, char *str)
{
    perror(str);
    free_all(data);
    exit (FAILURE);
}