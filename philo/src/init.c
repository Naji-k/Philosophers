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

void	init(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->meals_nb = ft_atoi(argv[5]);
	else
		data->meals_nb = -1;
	if (allocate_memory(data))
		printf("error allocate\n");
	init_philo(data);
	init_forks(data);
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
		return (1);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		printf("Error malloc forks\n");
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
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		i++;
	}
	return (0);
}

//this function to initialize forks for each philosopher ex: L_fork, R_fork
int	init_forks(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (i == 0)
		{
			data->philos[i].l_fork = &data->forks[i];
			data->philos[i].r_fork = &data->forks[data->nb_philo - 1];
		}
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}