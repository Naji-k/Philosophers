/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 19:34:23 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/07/11 19:34:23 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_inputs(t_data *data)
{
	printf("num_philo= %d\n", data->nb_philo);
	printf("time_to_die= %llu\n", data->death_time);
	printf("time_to_eat= %llu\n", data->eat_time);
	printf("time_to_sleep= %llu\n", data->sleep_time);
	printf("num_of_meals= %d\n", data->meals_nb);
}

//just default func it's not correct
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	for (int i = 0; i < 10; i++)
	{
		philo->eating++;
	}
	return (NULL);
}

void	pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->data->print);
	printf("Philo %d has taken fork\n", philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	eat(t_philo *philo)
{
	philo->status = EAT;
	pthread_mutex_lock(&philo->data->print);
	printf("Philo %d is eating \n", philo->id);
	pthread_mutex_unlock(&philo->data->print);
	usleep(philo->data->eat_time * 1000);
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	philo_sleep(t_philo *philo)
{
	philo->status = SLEEP;
	pthread_mutex_lock(&philo->data->print);
	printf("Philo %d is sleeping \n", philo->id);
	pthread_mutex_unlock(&philo->data->print);
	usleep(philo->data->sleep_time * 1000);
}

void	philo_think(t_philo *philo)
{
	philo->status = THINK;
	pthread_mutex_lock(&philo->data->print);
	printf("Philo %d is thinking \n", philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}
int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->thread_id[i], NULL, &routine,
				(void *)&data->philos[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->thread_id[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	printf("number of argc=%d\n", argc);
	if (argc > 4)
	{
		if (check_inputs(argc, argv) == 0)
		{
			printf("========\n");
			init(&data, argv);
			print_inputs(&data);
			create_threads(&data);
			printf("nb_of_meals=%d\n", data.meals_nb);
			free_all(&data);
		}
	}
	else
		printf("invalid inputs\n");
}

/* 

each time before print you have to lock mutex_print for each thread then print,
after finish print, unlock mutex_print
eating() {

	pickup_forks()
	start eat (print)
	usleep(time_to_eat);
	release_forks()

}


sleep{
	usleep(time_to_sleep)
	print();
}
 */