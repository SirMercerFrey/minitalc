#include "minitalk.h"

static int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	sign = 1;
	while (*str && is_space(*str))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		++str;
	}
	return (sign * result);
}

size_t	ft_strlen(const char *str)
{
	const char	*end;

	end = str;
	while (*end)
		++end;
	return (end - str);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	q;

	ptr = (unsigned char *)s;
	q = c;
	while (n--)
		*ptr++ = q;
	return (s);
}
