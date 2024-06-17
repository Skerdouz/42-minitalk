#include "minitalk.h"

static void	showpid()
{
	pid_t	pid;

	pid = getpid();
	ft_printf("pid: %u\n", pid);
}

static void	sighandler(int signum)
{
	ft_printf("Caught signal %d\n", signum);
	exit (1);
}

int	server_loop()
{
	showpid();
	signal(SIGINT, sighandler);

	while (1)
	{
		ft_printf("Waiting for signal..\n");
		sleep(1);
	}
	return (0);
}
