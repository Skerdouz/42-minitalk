#include "minitalk.h"

volatile int	last_signal;

static void	sighandler1(int signum)
{
	last_signal = signum;
}

static void	sighandler2(int signum)
{
	last_signal = signum;
}

static void	server_loop()
{
	pid_t		pid;
	int			bit;
	char		byte[9];

	last_signal = 0;
	bit = 0;
	pid = getpid();
	if (pid <= 0)
		exit(0);
	ft_printf("pid: %u\n", pid);
	signal(SIGUSR1, sighandler1);
	signal(SIGUSR2, sighandler2);
	while (1)
	{
		pause();
		if (last_signal == SIGUSR1)
			byte[bit++] = '1';
		else if (last_signal == SIGUSR2)
			byte[bit++] = '0';
		if (bit == 8)
		{
			byte[bit] = '\0';
			char_to_stash(byte);
			bit = 0;
		}
	}
}

int	main(void)
{
	server_loop();
	return (0);
}



