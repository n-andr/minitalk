#include "minitalk.h"

void	write_char(int n, int fd)
{
	char	ch;

	ch = n + '0';
	write (fd, &ch, 1);
}

void	conv_to_char(int nb, int fd)
{
	int	n;
	int	i;
	int	n2;

	n = nb;
	i = 1;
	while (n > 9)
	{
		n = n / 10;
		i = i * 10;
	}
	n = nb;
	n2 = nb;
	while (i != 1)
	{
		n = n2 / i;
		write_char(n, fd);
		n2 = n2 % i;
		i = i / 10;
	}
	write_char(n2, fd);
}

void	ft_putnbr_fd(unsigned int n, int fd)
{
	if (n >= 0)
		conv_to_char(n, fd);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_strlen(char *str)
{
	int	length;

	length = 0;
	while (*str != '\0')
	{
		str ++;
		length ++;
	}
	return (length);
}

// size_t	ft_strlcpy(char *dst, const char *src, size_t size)
// {
// 	size_t	i;

// 	i = 0;
// 	if (size > 0)
// 	{
// 		while (src[i] && i < (size - 1))
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = '\0';
// 	}
// 	while (src[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strjoin(char const *s1, char const s2)
// {
// 	char	*s_join;
// 	size_t	total_len;

// 	total_len = ft_strlen((char *)s1) + 1 + 1;
// 	s_join = malloc (total_len * sizeof(char));
// 	if (total_len == 0 || s_join == 0)
// 		return (NULL);
// 	ft_strlcpy(s_join, s1, ft_strlen((char *)s1) + 1);
// 	ft_strlcpy(s_join + ft_strlen((char *)s1), s2, 1 + 1);
// 	return (s_join);
// }