#include "minitalk.h"

volatile int	g_bit_received;

void	confirmation_signals(int signum)
{
	if (signum == SIGUSR1)
		g_bit_received = 1;
	if (signum == SIGUSR2)
	{
		g_bit_received = 2;
		write(1, "\033[1;31m", 7);
		write(STDOUT_FILENO, "⚠️  Message has been received by server!\n", 45);
		write(1, "\033[0m", 4);
	}
}

void	send_char(char c, int pid)
{
	int		bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(EXIT_FAILURE);
		}
		while (!g_bit_received)
			pause();
		g_bit_received = 0;
		++bit;
	}
}

void	send_length(int l, int pid)
{
	int		bit;

	bit = 0;
	while (bit < 22)
	{
		if ((l >> bit) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR1))
				exit(EXIT_FAILURE);
		}
		while (!g_bit_received)
			pause();
		g_bit_received = 0;
		++bit;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	int		length;
	int		i;

	if (argc != 3)
		return (write(STDERR_FILENO, "./client \"PID\" \"message\"\n", 25));
	pid = (pid_t)ft_atoi(argv[1]);
	if (pid <= 0 || pid > 4194304)
		return (write(STDERR_FILENO, "Invalid PID bruh.\n", 18));
	signal(SIGUSR1, confirmation_signals);
	signal(SIGUSR2, confirmation_signals);
	length = ft_strlen(argv[2]);
	send_length(length, pid);
	i = 0;
	while(i < length)
		send_char(argv[2][i++], pid);
	send_char('\0', pid);
	return (0);
}
