#include "minitalk.h"

static void	sighandler(int signum)
{
	(void)signum;
}

static void	send_signal(pid_t pid, char *str)
{
	int					bit;

	bit = 0;
	while (*str)
	{
		bit = 0;
		while (bit < 8)
		{
			if (*str & (1 << bit++))
			{
				if (kill(pid, SIGUSR1) == -1)
					exit(1);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					exit(1);
			}
			usleep(1200);
		}
		str++;
	}
}

int	main(int ac, char **av)
{
	pid_t				pid;
	struct sigaction	sa;


	if (--ac != 2)
	{
		ft_printf("Invalid arguments, expected: arg1:<pid> arg2:<string>\n");
		exit(0);
	}
	pid = ft_atoi(av[1]);
	if (pid <= 0)
	{
		ft_printf("Invalid PID\n");
		exit(0);
	}
	if (!av[2])
		return (1);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sighandler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	send_signal(pid, av[2]);
	return (0);
}
