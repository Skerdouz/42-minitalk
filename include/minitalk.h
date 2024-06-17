#ifndef MINITALK_H
# define MINITALK_H

#include <unistd.h>		/* standard unix functions, like getpid()       */
#include <sys/types.h>	/* various type definitions, like pid_t         */
#include <signal.h>		/* signal name macros, and the kill() prototype */

#include "libft.h"

/*
*	client
*/
void	send_signal(pid_t pid, char *str);
/*
*	server
*/
int	server_loop(void);

#endif