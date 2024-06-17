#include "minitalk.h"

char	**strtobin(char *str)
{
	int		ascii_value;
	char	**binary;

	binary = malloc(sizeof(char *) * ft_strlen(str));
	if (!binary)
		exit(0);
	while (*str)
	{
		*binary = malloc(sizeof(char) * 8);
		if (!*binary)
		{
			freedom(); // TODO freedom function
			exit(0);
		}
		ascii_value = int(*str);
		i = 8;
		*binary[i--] = '\0';
		while (i >= 0)
		{
			ascii_value /= 2;
			if (ascii_value % 2)
				*binary[i] = '1';
			else
				*binary[i] = '0';
			i--;
		}
	}
	return (result);
}

void	send_signal(pid_t pid, char *str)
{

}

int	main(int ac, char **av)
{
	pid_t	pid;

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
	send_signal(av[1], av[2]);
	return (0);
}