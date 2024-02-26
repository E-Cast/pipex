/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:14:48 by ecast             #+#    #+#             */
/*   Updated: 2024/02/26 14:15:43 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*cmd_lst_last(t_cmd *cmd_lst)
{
	t_cmd	*index;

	if (!cmd_lst)
		return (0);
	index = cmd_lst;
	while (index->next)
		index = index->next;
	return (index);
}

void	cmd_lst_add(t_cmd **cmd_lst, t_cmd *node)
{
	t_cmd	*index;

	if (!node)
		return ;
	if (!*cmd_lst)
		*cmd_lst = node;
	else
	{
		index = cmd_lst_last(*cmd_lst);
		index->next = node;
	}
}
