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

void	free_all_destroy(t_data *data, bool destroy, int forks, int meals)
{
	if (destroy == true)
		destroy_mutex(data, forks, meals);
	if (data->thread_id)
		free(data->thread_id);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

void	destroy_mutex(t_data *data, int forks, int meals)
{
	int	i;

	i = 0;
	while (i < forks)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	i = 0;
	while (i < meals)
	{
		pthread_mutex_destroy(&data->philos[i].mutex_meal);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_death);
	pthread_mutex_destroy(&data->mutex_create);
	pthread_mutex_destroy(&data->time);
}

long long	current_time(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
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
	long long	p_time;
	bool		status;

	pthread_mutex_lock(&philo->data->mutex_death);
	status = philo->data->dead;
	p_time = current_time() - philo->data->start_time;
	if (!status)
		printf("%lld %d %s\n", p_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->mutex_death);
	return (status);
}
