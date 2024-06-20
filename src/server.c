/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrahins <lbrahins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:34:49 by lbrahins          #+#    #+#             */
/*   Updated: 2024/06/21 00:43:35 by lbrahins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
*	TODO
*	- Add the ability to send signals to the client
*	- Try to optimize stuff
*/

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
	(void)info;/* don't forget to remove that stuff after handling the answer to the client */
	if (!msg)
		msg = init_msg();
	if (signum == SIGUSR2)
		c |= (1 << bit);
	if (++bit == 8)
	{
		msg = newchar_handler(msg, (unsigned char)c);
		c = 0;
		bit = 0;
	}
	// kill(info->si_pid, signum);
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
	if (sigaction(SIGUSR1, &sig, NULL) == -1 || sigaction(SIGUSR2, &sig, NULL) == -1)
		return (ft_putstr_fd("error: sigaction\n", 1), 1);
	while (1)
		usleep(USLEEP_T);
	return (0);
}
