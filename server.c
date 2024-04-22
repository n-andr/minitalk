/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:53:54 by nandreev          #+#    #+#             */
/*   Updated: 2024/04/22 15:24:30 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
// bits and chars  -int received ;

// return 1 if signal is processed and 0 otherwise
int	maybe_receive_msg_len(int signum, unsigned int *bits_received,
	const char *msg, int *msg_len)
{
	if (*bits_received < sizeof(unsigned int) * 8 && msg == NULL)
	{
		(*bits_received)++;
		if (signum == SIGUSR1)
			*msg_len |= 1 << (sizeof(int) * 8 - *bits_received);
		return (1);
	}
	return (0);
}

// zeroing reeived if the message length 
// is fully received and memory was allocated
void	allocate_message_if_necessary(char **msg, unsigned int msg_len,
	unsigned int *received)
{
	if (*msg != NULL)
	{
		return ;
	}
	(*msg) = malloc(sizeof(char) * (msg_len + 1));
	if (*msg == NULL)
	{
		write(1, "memory allocation problem\n", 26);
		exit(1);
	}
	(*msg)[msg_len] = '\0';
	*received = 0;
	return ;
}

// return 1 if a new char of the message is ready and 0 otherwise
int	process_signal(int signum, char *c, int *bit_count)
{
	if (signum == SIGUSR1)
		*c |= (1 << *bit_count);
	(*bit_count)--;
	if (*bit_count < 0)
		return (1);
	else
		return (0);
}

void	receive_signal(int signum)
{
	static int			bit_count = 7;
	static char			c = 0;
	static char			*msg = NULL;
	static unsigned int	received = 0;
	static int			msg_len = 0;

	if (maybe_receive_msg_len(signum, &received, msg, &msg_len))
		return ;
	allocate_message_if_necessary(&msg, msg_len, &received);
	if (process_signal(signum, &c, &bit_count))
	{
		msg[received] = c;
		received ++;
		if ((int)received == msg_len)
		{
			write(1, msg, msg_len);
			write(1, "\n", 1);
			free(msg);
			msg = NULL;
			msg_len = 0;
			received = 0;
		}
		bit_count = 7;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	write (1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write (1, "\n", 1);
	sa.sa_handler = receive_signal;
	sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
//pause() - do nothing before a signal arrives
//c |= (1 << bit_count); - |= a bitwise OR operation between c 
//and the value on the right side of the operator (1 << bit_count), 
//and then assigns the result back to c
// signal(SIGUSR1, recieve_signal);
// signal(SIGUSR2, recieve_signal);

// sa.sa_flags = SA_RESTART; /* Restart functions if interrupted by handler */