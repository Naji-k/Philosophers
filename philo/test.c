/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 18:15:26 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/07/18 18:15:26 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

long long	start;
long long	current_time(struct timeval *tv);
void		ft_usleep(struct timeval *tv, long long ms);

void	ft_usleep(struct timeval *tv, long long ms)
{
	long long	placeholder;

	placeholder = current_time(tv);
	while (current_time(tv) < placeholder + ms)
		usleep(300);
}

long long	current_time(struct timeval *tv)
{
	long long	curtime;

	gettimeofday(tv, NULL);
	curtime = tv->tv_sec * 1000 + tv->tv_usec / 1000;
	return (curtime - start);
}

int	main(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("%lld\n", current_time(&tv));
	ft_usleep(&tv, 5000);
	printf("%lld\n", current_time(&tv));
}
