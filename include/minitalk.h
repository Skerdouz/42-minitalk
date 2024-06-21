/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrahins <lbrahins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:35:07 by lbrahins          #+#    #+#             */
/*   Updated: 2024/06/21 15:14:30 by lbrahins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# ifndef USLEEP_T
#  define USLEEP_T 1800
# endif

# include <unistd.h>		/* getpid() */
# include <sys/types.h>		/* pid_t */
# include <signal.h>		/* kill(), sigaction() */
# include <stdlib.h>		/* malloc(), exit() */

# include "libft.h"

#endif