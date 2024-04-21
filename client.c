/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Natalia <Natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:49:44 by nandreev          #+#    #+#             */
/*   Updated: 2024/04/21 23:28:10 by Natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char_as_binary(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (((c >> bit) & 1) == 1)
		{
			kill (pid, SIGUSR1);
		}
		else
		{
			kill (pid, SIGUSR2);
		}
		bit --;
		usleep(100);
	}
}

// Send SIGUSR1 for a bit of 1
// Send SIGUSR2 for a bit of 0
// Wait a short interval
// Move to the next bit

void	send_int_as_binary(int pid, unsigned int len)
{
	int	bit;

	bit = sizeof(unsigned int) * 8 - 1;
	while (bit >= 0)
	{
		if ((len >> bit) & 1)
		{
			kill(pid, SIGUSR1);
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		usleep(100);
		bit--;
	}
}

void	send_string(int pid, char *string)
{
	int				i;
	unsigned int	len;

	len = ft_strlen(string);
	i = 0;
	send_int_as_binary (pid, len);
	while (string[i] != '\0')
	{
		send_char_as_binary(pid, string[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
	{
		exit (write (1, "error", 5));
	}
	while (argv[1][i] != '\0')
	{
		if (argv[1][i] > '9' || argv[1][i] < '0')
			exit (write (1, "error", 5));
		i++;
	}
	send_string(ft_atoi(argv[1]), argv[2]);
	return (0);
}
