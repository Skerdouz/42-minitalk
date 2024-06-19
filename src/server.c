#include "minitalk.h"

t_data	g_data;

void	reset_data(void)
{
	g_data.bit = 0;
	g_data.byte = 0;
	g_data.client_pid = 0;
}

static unsigned char	reverse_byte(unsigned char byte)
{
	unsigned char	result;
	int				i;

	result = 0;
	i = 0;
	while (i++ < 8)
	{
		result <<= 1;
		result |= (byte & 1);
		byte >>= 1;
	}
	return (result);
}

static void	sighandler(int signum, siginfo_t *info, void *context)
{
	(void)context; /*gcc error handler*/
	if (g_data.client_pid != info->si_pid)
	{
		reset_data();
		g_data.client_pid = info->si_pid;
	}
	if (signum == SIGUSR1)
		g_data.byte = (g_data.byte << 1) | 1;
	else if (signum == SIGUSR2)
	{
		g_data.byte <<= 1;
	}
	if (++g_data.bit == 8)
	{
		if (is_end(g_data.byte))
			printstash();
		g_data.byte = reverse_byte(g_data.byte);
		write(1, &g_data.byte, 1);
		reset_data();
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	pid = getpid();
	if (pid <= 0)
		return (ft_putstr_fd("error: invalid PID\n", 1), 1);
	reset_data();
	ft_printf("pid: %u\n", pid);
	while (1)
		usleep(1200);
	return (0);
}



