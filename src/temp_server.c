#include "minitalk.h"

static char	*init_msg(void)
{
	char	*msg;

	msg = (char *)malloc(sizeof(char));
	if (!msg)
		return (NULL);
	msg[0] = '\0';
	return (msg);
}

static char	*msg_realloc(char *old, unsigned char c)
{
	size_t	len;
	long	i;
	char	*new;

	len = ft_strlen(old);
	new = (char *)malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = old[i];
	new[i] = c;
	new[i + 1] = '\0';
	return (free(old), new);
}

static char	*handle_character(char *msg, char c)
{
	if (!c)
	{
		ft_printf("%s", msg);
		free(msg);
		return (NULL);
	}
	return (msg_realloc(msg, (unsigned char)c));
}

static void	sighandler(int signal, siginfo_t *info, void *context)
{
	static int				c;
	static int				bit;
	static char				*msg;

	(void)context;
	if (!msg)
		msg = init_msg();
	if (!msg)
		return ;
	else if (signal == SIGUSR2)
		c |= (1 << bit);
	if (++bit == 8)
	{
		msg = handle_character(msg, (char)c);
		c = 0;
		bit = 0;
	}
	kill(info->si_pid, signal);
}

int	main(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = sighandler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		usleep(USLEEP_TIME);
	return (0);
}
