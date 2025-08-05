#include "minitalk.h"

void	write_pid(int pid)
{
	char	buffer[42];
	int		i;

	i = 33;
	while (pid > 0)
	{
		buffer[i--] = (pid % 10) + '0';
		pid /= 10;
	}
	write(STDOUT_FILENO, "Server PID : ", 13);
	write(STDOUT_FILENO, &buffer[i + 1], 33 - i);
	write(STDOUT_FILENO, "\n", 1);
}

void	receive_morse(int signum, siginfo_t *info, void *context)
{
	static char		*buf;
	static int		bit;
	static int		c;
	static int		flag;
	static int		i;

	(void)context;
	if (signum == SIGUSR2)
		c |= (1 << bit);
	++bit;
	if (bit == 22 && !flag)
		buf = get_length(&c, &bit, &flag);
	if (bit == 8 && flag)
	{
		if (!c)
		{
			print_buf(buf, &i, &flag, &bit, &c);
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		buf[i++] = (char)c;
		bit = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

char	*get_length(int *c, int *bit, int *flag)
{
	char	*buf;

	if (!*c)
		*c = 1;
	buf = malloc(sizeof(char) * (*c));
	if (!buf)
		exit(EXIT_FAILURE);
	ft_memset(buf, 0, *c);
	*c = 0;
	*bit = 0;
	*flag = 1;
	return (buf);
}

void	print_buf(char *buf, int *i, int *flag, int *bit, int *c)
{
	write(STDOUT_FILENO, buf, *i);
	write(STDOUT_FILENO, "\n", 1);
	*i = 0;
	*flag = 0;
	*bit = 0;
	*c = 0;
	free(buf);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	write_pid(pid);
	sa.sa_sigaction = receive_morse;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
