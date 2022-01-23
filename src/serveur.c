/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 00:37:01 by nthimoni          #+#    #+#             */
/*   Updated: 2022/01/23 02:43:22 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static void	fill_len(int signum, char **str, int bits)
{
	static size_t len = 0;

	if (signum == SIGUSR2)
		len += ((size_t)1 << (64 - bits));
	if (bits == sizeof(size_t) * 8)
	{
		*str = calloc(len + 1, sizeof(size_t));
		len = 0;
	}
}

static int	fill_str(int signum, int bits, char *str)
{
	int	index;

	bits -= 65;
	index = bits / 8;
	if (signum == SIGUSR2)
		str[index] += (1 << (7 - bits % 8));
	if (bits % 8 == 7 && str[index] == '\0')
		return (1);
	return (0);
}

void	handler(int signum, siginfo_t *info, void *context)
{
	int			pid;
	static int	bits_received = 0;
	static char	*str;

	pid = info->si_pid;
	bits_received++;
	if (bits_received <= sizeof(size_t) * 8)
		fill_len(signum, &str, bits_received);
	else
	{
		if (fill_str(signum, bits_received, str))
		{
			ft_printf("%s\n", str);
			ft_printf("size = %d \n", ft_strlen(str));
			free(str);
			bits_received = 0;
		}
	}
	usleep(200);
	kill(pid, SIGUSR1);
	return ;
}

int	main()
{
	struct	sigaction sa;

	ft_printf(" pid : %d \n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
