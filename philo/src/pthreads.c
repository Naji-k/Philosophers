/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pthreads.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 15:45:34 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/08/03 15:45:34 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->create);
	pthread_mutex_unlock(&philo->data->create);
	if (philo->id % 2 == 0)
		usleep(50);
	while (1)
	{
		if (print_msg(philo, THINKING))
			break ;
		if (!eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
	}
	return (NULL);
}

bool	thread_checker(t_data *data)
{
	if (data->created_threads != data->nb_philo)
	{
		death_status(data, 1);
		return (false);
	}
	return (true);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->create);
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->time);
		data->philos[i].last_meal_time = current_time();
		pthread_mutex_unlock(&data->time);
		if (pthread_create(&data->thread_id[i], NULL, &routine,
				(void *)&data->philos[i]))
			break ;
		i++;
		data->created_threads = i;
	}
	if (thread_checker(data) == false)
	{
		pthread_mutex_unlock(&data->create);
		printf("error thread_checker\n");
		return (1);
	}
	data->start_time = current_time();
	pthread_mutex_unlock(&data->create);
	return (0);
}

int	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->created_threads)
	{
		if (pthread_join(data->thread_id[i], NULL))
			return (1);
		i++;
	}
	return (0);
}
