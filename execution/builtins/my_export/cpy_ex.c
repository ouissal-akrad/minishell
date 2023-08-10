/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_ex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:49:01 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/10 17:06:18 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*copy_env_list(const t_env *original_head)
{
	t_env	*copy_head;
	t_env	*original_curr;
	t_env	*copy_prev;
	t_env	*copy_curr;

	if (original_head == NULL)
		return (NULL);
	copy_head = create_new_env(original_head);
	if (copy_head == NULL)
		return (NULL);
	original_curr = original_head->next;
	copy_prev = copy_head;
	while (original_curr != NULL)
	{
		copy_curr = create_new_env(original_curr);
		if (copy_curr == NULL)
			return (NULL);
		copy_curr->prev = copy_prev;
		copy_prev->next = copy_curr;
		original_curr = original_curr->next;
		copy_prev = copy_curr;
	}
	return (copy_head);
}
