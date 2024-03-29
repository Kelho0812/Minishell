/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:17:21 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/22 15:17:21 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	recursive_executer(t_pipes *head, int recursive)
{
	int	status;

	status = 0;
	while (head)
	{
		status = recursive_down(head);
		if (status == 1 && head->pipe_type == D_PIPE)
		{
			while (head && head->pipe_type != AMPER)
				head = head->next;
		}
		if (head)
			head = head->next;
	}
	if (status == 0 && recursive == 1)
		return (0);
	return (1);
}

int	recursive_down(t_pipes *head)
{
	int	status;

	if (!head)
		return (2);
	if (check_for_dbpipe_dbamper(head->input_string))
		return (recursive_executer(head->down, 1));
	status = recursive_down(head->down);
	if (status == 0)
		return (0);
	else if (status == 1)
		return (1);
	return (list_iterator_executer(head));
}

int	list_iterator_executer(t_pipes *head)
{
	int	status;
	int	save_stdout;

	status = 0;
	save_stdout = 0;
	while (head)
	{
		init_data(head);
		if (head->in_out.output_type == REDIRECT_OUTPUT || \
			head->in_out.output_type == APPEND_OUTPUT)
			return (execute_to_file(head, status, save_stdout));
		else
			return (execute_to_stdout(head, status));
		head = head->next;
	}
	return (1);
}

int	execute_command(t_pipes *node)
{
	char	**args_array;
	int		cmd;

	args_array = node->data.command_n_args;
	cmd = node->data.command_type;
	if (cmd == ECHO)
		ft_echo(args_array);
	if (cmd == CD)
		return (ft_cd(node, args_array));
	if (cmd == PWD)
		ft_pwd();
	if (cmd == EXPORT)
		return (ft_export(node, args_array), 1);
	if (cmd == UNSET)
		return (ft_unset(&node->init.envs, &node->init.sorted_envs, args_array), 1);
	if (cmd == ENV)
		return (ft_env(node->init.envs), 1);
	if (cmd == EXIT)
		ft_exit(node, 1);
	if (cmd == NOT_BUILTIN)
		return (ft_execve(node));
	return (1);
}
