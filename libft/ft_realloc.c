/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:23:57 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/27 16:46:51 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void *ft_realloc(void *ptr, size_t new_size)
{
    void *new_ptr;
    
    if (!new_size)
    {
        free(ptr);
        return (NULL);
    }
    if (!ptr)
        return (malloc(new_size));
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return (NULL);
    ft_memcpy(new_ptr, ptr, ft_strlen(ptr) + 1);
    free(ptr);

    return (new_ptr);
}
