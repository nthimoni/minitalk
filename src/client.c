/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthimoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:17:46 by nthimoni          #+#    #+#             */
/*   Updated: 2022/01/23 00:23:09 by nthimoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h" 

#define BYTE_SIZE 8


void	handler(int signum)
{
	if (signum == SIGUSR2)
		exit(ft_printf("C FINI\n"));
}

static int	sendlen(int pid, size_t len)
{
	int	i;

	i = 8 * sizeof(size_t) - 1;
	while (i >= 0)
	{
		if (len & ((size_t)1 << i))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		if (!usleep(100000))
			exit(ft_printf("ERROR: Server isn't responding\n"));
		i--;
		usleep(100);
	}
	return (1);
}

static int	sendstr(int pid, char *str)
{
	int	i;
	int	a;

	i = 0;
	while (i == 0 || str[i - 1])
	{
		a = 7;
		while (a >= 0)
		{
			if (str[i] & ((char)1 << a))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			if (!usleep(100000))
				exit(ft_printf("ERROR: Server isn't responding\n"));
			a--;
			usleep(100);
		}
		i++;
	}
	return (1);
}

int main(int argc, char *argv[])
{
	int		pid;
	size_t	len;
	struct sigaction	sa;

	if (argc != 3)
		return (0);
	pid = ft_atoi(argv[1]);
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (!sendlen(pid, ft_strlen(argv[2])))
		return (ft_printf("Plus de reponse du serveur !\n"));
	if (!sendstr(pid, argv[2]))
		return (ft_printf("Plus de reponse du serveur !\n"));
	ft_printf("Le message a etait correctement transmis !\n");
	return (0);
}
