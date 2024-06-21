/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrahins <lbrahins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:34:49 by lbrahins          #+#    #+#             */
/*   Updated: 2024/06/21 16:48:34 by lbrahins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*init_msg(void)
{
	char	*msg;

	msg = (char *)malloc(1 * sizeof(char));
	if (!msg)
		exit(EXIT_FAILURE);
	return (msg[0] = '\0', msg);
}

static char	*msg_realloc(char *old, unsigned char c)
{
	int		len;
	int		i;
	char	*new;

	len = ft_strlen(old);
	new = (char *)malloc((len + 2) * sizeof(char));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = old[i];
	new[i++] = c;
	new[i] = '\0';
	return (free(old), new);
}

static char	*newchar_handler(char *msg, unsigned char c)
{
	if (!c)
		return (ft_printf("<client> %s\n", msg), free(msg), NULL);
	return (msg_realloc(msg, c));
}

static void	sighandler(int signum, siginfo_t *info, void *context)
{
	static int		c;
	static int		bit;
	static char		*msg;

	(void)context;
	if (!msg)
		msg = init_msg();
	if (!msg)
		exit(EXIT_FAILURE);
	if (signum == SIGUSR2)
		c |= (1 << bit);
	if (++bit == 8)
	{
		msg = newchar_handler(msg, (unsigned char)c);
		c = 0;
		bit = 0;
	}
	if (kill(info->si_pid, signum) == -1)
	{
		ft_putstr_fd("[ERROR] Unable to send signal to client.\n", 1);
		free(msg);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	struct sigaction	sig;
	pid_t				pid;

	pid = getpid();
	ft_printf("<server> Server's PID: %d\n", pid);
	sig.sa_sigaction = sighandler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig, NULL) == -1
		|| sigaction(SIGUSR2, &sig, NULL) == -1)
		return (ft_putstr_fd("[ERROR] Sigaction error.\n", 1), 1);
	while (1)
		usleep(USLEEP_T);
	return (0);
}
