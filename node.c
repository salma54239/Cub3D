/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 04:58:31 by ssaadaou          #+#    #+#             */
/*   Updated: 2024/01/30 01:05:44 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*new_node(char *str)
{
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head->data = str;
	head->next = NULL;
	return (head);
}

t_list	*last_n(t_list	*stack)
{
	while (stack->next)
		stack = stack->next;
	return (stack);
}

void	add_node_end(t_list **head, t_list *newnode)
{
	t_list	*temp;

	temp = *head;
	if (!*head)
	{
		*head = newnode;
		return ;
	}
	last_n(temp)->next = newnode;
}

void	add_node_top(t_list **head, t_list *new_node)
{
	if (!new_node)
		return ;
	new_node->next = *head;
	*head = new_node;
}

void	free_stack(t_list *stack)
{
	t_list	*tmp;

	while (stack)
	{
		tmp = stack;
		free(stack->data);
		stack = stack->next;
		free(tmp);
	}
}
