/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrahins <lbrahins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:34:53 by lbrahins          #+#    #+#             */
/*   Updated: 2024/06/21 15:09:10 by lbrahins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
*	TODO
*	- Optimize stuff
*	- Add a timeout? maybe
*/

static void	sighandler(int signum)
{
	static int	c;
	static int	bit;

	if (signum == SIGUSR2)
		c |= (1 << bit);
	if (++bit == 8)
	{
		if (c == 0)
			return (ft_putstr_fd("[INFO] Message sent succesfuly.\n", 1)
				, (void) NULL);
		c = 0;
		bit = 0;
	}
}

static void	send_null_signal(pid_t pid)
{
	int	bit;

	bit = 0;
	while (bit++ < 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			exit(EXIT_FAILURE);
		usleep(USLEEP_T);
	}
}

static void	send_signal(pid_t pid, char *str)
{
	int	bit;

	bit = 0;
	while (*str)
	{
		bit = 0;
		while (bit < 8)
		{
			if (*str & (1 << bit++))
			{
				if (kill(pid, SIGUSR2) == -1)
					exit(EXIT_FAILURE);
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
					exit(EXIT_FAILURE);
			}
			usleep(USLEEP_T);
		}
		str++;
	}
	send_null_signal(pid);
}

int	main(int ac, char **av)
{
	pid_t				pid;
	struct sigaction	sa;

	if (--ac != 2)
	{
		ft_putstr_fd
		("[ERROR] Invalid args: ./client [(int)pid] [(string)message]\n", 1);
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		return (ft_putstr_fd("[ERROR] Invalid or unauthorized PID\n", 1), 1);
	if (!av[2])
		return (1);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sighandler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (ft_putstr_fd("[ERROR] sigaction error.\n", 1), 1);
	ft_putstr_fd("[INFO] Sending message, please wait...\n", 1);
	send_signal(pid, av[2]);
	return (0);
}
