#include "minitalk.h"

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

static void	sighandler(int signum)
{
	static int				bit;
	static unsigned char	byte;

	if (!bit)
		bit = 0;
	if (!byte)
		byte = 0;
	if (signum == SIGUSR1)
		byte = (byte << 1) | 1;
	else if (signum == SIGUSR2)
		byte <<= 1;
	if (++bit == 8)
	{
		ft_printf("%c", reverse_byte(byte));
		bit = 0;
		byte = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	pid = getpid();
	if (pid <= 0)
		return (1);
	ft_printf("pid: %u\n", pid);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sighandler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (1)
		pause();
	return (0);
}



