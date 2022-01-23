#include <stdlib.h>
#include <signal.h>

static void	fill_len(int signum, char **str, int bits)
{
	static size_t len = 0;

	if (signum == SIGUSR2)
		len = len + ((size_t)1 << (64 - bits));
	if (bits == 64)
	{
		printf("size = %zu \n", len);
		*str = malloc(sizeof(char) * (len + 1));
		len = 0;
	}
}

static int	fill_str(int signum, int bits, char *str)
{
	int	index;

	bits -= 64;
	index = (bits - 1) / 8;
	if (signum == SIGUSR2)
		str[index] += (1 << (8 - (bits % 8 )));
	if (bits % 8 == 0 && str[index] == '\0')
		return (1);
	return (0);
}
int main()
{
	char *str = "01100001011000010110000100000000";
	char u[4];
	int 	i = 0;
	while (str[i++])
	{
		if (str[i - 1] == '0')
			fill_str(SIGUSR1, i+64, u);
		else
			fill_str(SIGUSR2, i+64, u);
	}
}
