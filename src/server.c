#include "minitalk.h"

static void	sighandler(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("Caught signal %d | SIGUSR1\n", signum);
	else if (signum == SIGUSR2)
		ft_printf("Caught signal %d | SIGUSR2\n", signum);
	else
		ft_printf("Caught unknown signal\n");
	exit (1);
}

int	server_loop()
{
	pid_t	pid;

	pid = getpid();
	ft_printf("pid: %u\n", pid);
	signal(SIGUSR1, sighandler);
	signal(SIGUSR2, sighandler);

	while (1)
	{
		ft_printf("Waiting for signal..\n");
		sleep(1);
		kill(pid, SIGUSR2);
	}
	return (0);
}

int	main(void)
{
	server_loop();
	return (0);
}
