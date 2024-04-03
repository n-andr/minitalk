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
				//write(1, "1", 1);
			}
		else
			{
				kill (pid, SIGUSR2);
				//write(1, "0", 1);
			}
		bit --;
		usleep(100);
	}
}

void send_int_as_binary(int pid, unsigned int len) 
{
    int	bit;

	bit = sizeof(unsigned int) * 8 - 1;
    while (bit >= 0) {
        if ((len >> bit) & 1) {
            kill(pid, SIGUSR1); // Send SIGUSR1 for a bit of 1
        } else {
            kill(pid, SIGUSR2); // Send SIGUSR2 for a bit of 0
        }
        usleep(100); // Wait a short interval
        bit--; // Move to the next bit
    }
}

void	send_string(int pid, char *string)
{
	int	i;
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
	send_char_as_binary(ft_atoi(argv[1]), '\0');
	
	

	return (0);
}