#include "minitalk.h"

// static void	freedom(char **array)
// {

// }

static char	**strtobin(char *str)
{
	int		ascii_value;
	int		i;
	char	**binary;

	binary = malloc(sizeof(char *) * ft_strlen(str));
	if (!binary)
		return (NULL);
	while (*str)
	{
		*binary = malloc(sizeof(char) * 9);
		if (!*binary)
			return (NULL); // TODO freedom function
		ascii_value = *str;
		i = 8;
		*binary[i] = '\0';
		while (--i >= 0)
		{
			if (ascii_value % 2)
				*binary[i] = '1';
			else
				*binary[i] = '0';
			ascii_value /= 2;
		}
		binary++;
		str++;
	}
	return (binary);
}

static void	send_signal(pid_t pid, char **binary)
{
	int	i;

	i = 0;
	while (*binary)
	{
		i = 0;
		while (*binary[i])
		{
			if (*binary[i] == '1')
				kill(pid, SIGUSR1);
			else if (*binary[i] == '0')
				kill(pid, SIGUSR2);
			i++;
		}
		binary++;
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;
	char	**binary;

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
	binary = strtobin(av[2]);
	if (!binary)
		return (1);
	send_signal(pid, binary);
	return (0);
}
