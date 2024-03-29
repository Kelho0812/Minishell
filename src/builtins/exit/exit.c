/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:38:09 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/21 13:38:09 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_exit(t_pipes *head, int exit_type)
{
	free_heardoc(head);
	free_env_list(head->init.envs);
	free_env_list(head->init.sorted_envs);
	free_args(head->data.command_n_args);
	free_list(&head);
	rl_clear_history();
	if (exit_type == 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
