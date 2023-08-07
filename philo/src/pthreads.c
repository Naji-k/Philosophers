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

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (print_msg(philo, T_FORK))
	{
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->mutex_create);
	pthread_mutex_unlock(&philo->data->mutex_create);
	if (philo->id % 2 == 0)
		ft_sleep(50);
	if (philo->data->nb_philo == 1)
	{
		one_philo(philo);
		return (NULL);
	}
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
/**
 * @brief to check if created_threads == number_of_philos
 * 
 * @param data 
 * @return true 
 * @return false 
 */

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
	pthread_mutex_lock(&data->mutex_create);
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
		pthread_mutex_unlock(&data->mutex_create);
		printf("error thread_checker\n");
		return (1);
	}
	data->start_time = current_time();
	pthread_mutex_unlock(&data->mutex_create);
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
