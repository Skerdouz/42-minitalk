#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>		/* getpid() */
# include <sys/types.h>		/* pid_t */
# include <signal.h>		/* kill() */
# include <stdlib.h>		/* malloc() */

# include "libft.h"

/*
*	client
*/
/*
*	server
*/
typedef struct s_data
{
	int				bit;
	unsigned char	byte;
	pid_t			client_pid;
}	t_data;

#endif