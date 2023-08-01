/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 16:16:33 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/07/13 16:16:33 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_free_all(t_data *data)
{
	if (data->thread_id)
		free(data->thread_id);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	destroy_mutex(data);
}

long long	current_time(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
}

void	ft_sleep(long long time)
{
	long long	check;

	check = current_time();
	while (current_time() < check + time)
		usleep(300);
}

bool	print_msg(t_philo *philo, char *msg)
{
	long long p_time;

	pthread_mutex_lock(&philo->data->mutex_death);
	p_time = current_time() - philo->data->start_time;
	if (!philo->data->dead)
		printf("%lld %d %s\n", p_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->mutex_death);
	return (philo->data->dead);
}