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

#include "../includes/minishell.h"

void	executer(t_envs *envs, t_pipes *head, char **heardocs)
{
	t_pipes	*current;

	current = head;
	while (current)
	{
		execute_command(heardocs, envs, current->data, head);
		current = current->next;
	}
}

void	execute_command(char **heardocs, t_envs *envs, t_data *data, t_pipes *head)
{
	t_data	*current;
	char	**args_array;
	int		cmd;

	current = data;
	args_array = current->command_n_args;
	cmd = current->command_type;
	if (cmd == ECHO)
		ft_echo(args_array);
	if (cmd == CD)
		ft_cd(envs, args_array);
	if (cmd == PWD)
		ft_pwd();
	if (cmd == EXPORT)
		ft_export(envs, args_array);
	if (cmd == UNSET)
		ft_unset(&envs, args_array);
	if (cmd == ENV)
		ft_env(envs);
	if (cmd == EXIT)
		ft_exit(heardocs, envs, head);
	if (cmd == NOT_BUILTIN)
		ft_execve(envs, args_array);
}
