/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:48:43 by jorteixe          #+#    #+#             */
/*   Updated: 2024/04/01 11:57:10 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig);

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint(int sig)
{
	char	*prompt;

	(void)sig;
	prompt = creat_cwd();
	rl_on_new_line();
	rl_redisplay();
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	free(prompt);
}
