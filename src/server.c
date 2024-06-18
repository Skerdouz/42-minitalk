#include "minitalk.h"

static void	sighandler1()
{
	ft_printf("Catched signal '1'");
}

static void	sighandler2()
{
	ft_printf("Catched signal '1'");
}

static int	server_loop()
{
	pid_t	pid;

	pid = getpid();
	if (pid <= 0)
		exit(0);
	ft_printf("pid: %u\n", pid);
	signal(SIGUSR1, sighandler1);
	signal(SIGUSR2, sighandler2);
	while (1)
		usleep(200);
	return (0);
}

int	main(void)
{
	server_loop();
	return (0);
}
