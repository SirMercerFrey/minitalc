#ifndef SMALLTALK_H
# define SMALLTALK_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <stdio.h>

extern volatile int		g_bit_received;

void    write_pid(int pid);
void    receive_morse(int signum, siginfo_t *info, void *context);
char	*get_length(int *c, int *bit, int *flag);
void    print_buf(char *buf, int* i, int *flag, int *bit, int *c);
void	*ft_memset(void *s, int c, size_t n);

void	confirmation_signals(int signum);
void	send_char(char c, int pid);
void	send_length(int l, int pid);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);

#endif
