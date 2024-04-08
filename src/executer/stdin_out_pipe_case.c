/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_out_pipe_case.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:45:59 by ruiolive          #+#    #+#             */
/*   Updated: 2024/04/06 20:47:56 by ruiolive         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	list_size(t_pipes *head)
{
	int	i;

	if (!head)
		return (0);
	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

void	check_for_execution_to_file(t_pipes *node, int *status)
{
	int	stdout;

	if (node->in_out.output_type == REDIRECT_OUTPUT || \
		node->in_out.output_type == APPEND_OUTPUT)
	{
		stdout = dup(STDOUT_FILENO);
		dup2(node->in_out.fd, STDOUT_FILENO);
		close(node->in_out.fd);
	}
	*status = execute_command(node);
	if (node->in_out.output_type == REDIRECT_OUTPUT || \
		node->in_out.output_type == APPEND_OUTPUT)
	{
		dup2(stdout, STDOUT_FILENO);
		close(stdout);
	}
}