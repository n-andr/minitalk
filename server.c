/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:53:54 by nandreev          #+#    #+#             */
/*   Updated: 2024/04/10 13:39:32 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
// bits and chars  -int recieved ; 

void	recieve_signal(int signum)
{
	static int	bit_count = 7;
	static char	c = 0;
	static char *msg = NULL;
	static unsigned int	recieved = 0;
	static int	msg_len = 0;

	if (recieved < sizeof(unsigned int) * 8 && msg == NULL)
	{
		recieved++;
		if (signum == SIGUSR1)
			msg_len |= 1 << (sizeof(int) * 8 - recieved);
		return;
	}
	if (msg == NULL)
	{
		msg = malloc(sizeof(char) * (msg_len + 1));
		if (msg == NULL)
		{
			return;
		}
		msg[msg_len + 1] = '\0';
		recieved = 0;
	}
	
	if (signum == SIGUSR1)
	{
		c |= (1 << bit_count);
	}
	bit_count --;
	if (bit_count < 0)
	{
		if (c == 0)
		{
			write(1, msg, msg_len);
			write(1, "\n", 1);
			free(msg);
			msg = NULL;
			msg_len = 0;
			recieved = 0;
		}
		else
		{
			msg[recieved] = c;
			recieved++;
		}
		bit_count = 7;
		c = 0;
	}
	
}

int	main()
{
	struct sigaction sa;

	write (1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write (1, "\n", 1);
    sa.sa_handler = recieve_signal;
    sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
    sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
//pause() - do nothing before a signal arrives
//c |= (1 << bit_count); - |= a bitwise OR operation between c and the value on the right side of the operator (1 << bit_count), and then assigns the result back to c
// signal(SIGUSR1, recieve_signal);
// signal(SIGUSR2, recieve_signal);

// sa.sa_flags = SA_RESTART; /* Restart functions if interrupted by handler */