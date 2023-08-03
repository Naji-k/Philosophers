/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 14:58:25 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/07/13 14:58:25 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init(t_data *data)
{
	if (allocate_memory(data))
	{
		printf("error allocate\n");
		return (1);
	}
	if (!init_mutex(data))
	{
		printf("error init_mutexes\n");
		return (1);
	}
	if (init_philo(data))
		return (1);
	init_forks(data);
	return (0);
}

int	allocate_memory(t_data *data)
{
	data->thread_id = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->thread_id)
	{
		printf("error allocate threads\n");
		return (1);
	}
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
	{
		printf("Error malloc philo\n");
		free(data->thread_id);
		return (1);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		printf("Error malloc forks\n");
		free(data->thread_id);
		free(data->philos);
		return (1);
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (data->must_eat != -1)
			data->philos[i].meal_count = data->must_eat;
		else
			data->philos[i].meal_count = -1;
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		if (pthread_mutex_init(&data->philos[i].mutex_meal, NULL))
			return (1);
		data->philos[i].finish = false;
		i++;
	}
	return (0);
}

//this function to initialize forks for each philosopher ex: L_fork, R_fork
void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		// if (i == (data->nb_philo - 1))
		// {
		// 	data->philos[i].r_fork = &data->forks[0];
		// 	data->philos[i].l_fork = &data->forks[i];
		// }
		// else
		// {
			data->philos[i].r_fork = &data->forks[i];
			data->philos[i].l_fork = &data->forks[(i + 1) % data->nb_philo];
		// }
		i++;
	}
}

bool	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (false);
		i++;
	}
	if (pthread_mutex_init(&data->mutex_death, NULL))
		return (false);
	if (pthread_mutex_init(&data->create, NULL))
		return (false);
	if (pthread_mutex_init(&data->time, NULL))
		return (false);
	return (true);
}
