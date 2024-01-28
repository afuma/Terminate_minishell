/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 01:13:29 by wnguyen           #+#    #+#             */
/*   Updated: 2023/11/15 21:12:28 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newlist)
{
	t_list	*l;

	if (!lst || !newlist)
		return ;
	if (*lst)
	{
		l = ft_lstlast(*lst);
		l -> next = newlist;
	}
	else
		*lst = newlist;
}
