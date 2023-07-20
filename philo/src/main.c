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
	printf("num_of_meals= %d\n", data->must_eat);
}


void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->create);
	pthread_mutex_unlock(&philo->data->create);
	if (philo->id % 2 == 0)
		usleep(300);
	while (1)
	{
		philo_think(philo);
		eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_msg(philo, T_FORK);
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, T_FORK);
}

void	eat(t_philo *philo)
{
	philo->status = EAT;
	pickup_forks(philo);
	philo->last_meal_time = current_time() + philo->data->eat_time;
	pthread_mutex_lock(&philo->mutex_meal);
	philo->meal_count--;
	print_msg(philo, EATING);
	ft_sleep(philo->data->eat_time);
	pthread_mutex_unlock(&philo->mutex_meal);
	putdown_forks(philo);
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	philo_sleep(t_philo *philo)
{
	philo->status = SLEEP;
	print_msg(philo, SLEEPING);
	ft_sleep(philo->data->sleep_time);
}

void	philo_think(t_philo *philo)
{
	philo->status = THINK;
	print_msg(philo, THINKING);
}
bool	thread_checker(t_data *data)
{
	if (data->created_threads != data->nb_philo)
		return (false);
	return (true);
}
int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->create);
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->thread_id[i], NULL, &routine,
				(void *)&data->philos[i]))
			break ;
		i++;
		data->created_threads = i;
	}
	if (thread_checker(data) == false)
	{
		pthread_mutex_unlock(&data->create);
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
	while (i > data->nb_philo)
	{
		if (pthread_join(data->thread_id[i], NULL))
			return (1);
		i++;
	}
	return (0);
}
int	ft_monitor(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i <= data->nb_philo)
		{
			pthread_mutex_lock(&data->philos[i].mutex_meal);
			if (data->philos[i].last_meal_time >= data->start_time
				+ data->death_time)
			{
				data->philos[i].status = DIE;
				print_msg(&data->philos[i], DIED);
				pthread_mutex_unlock(&data->philos[i].mutex_meal);
				return (1);
			}
			pthread_mutex_unlock(&data->philos[i].mutex_meal);
			// if (data->philos[i].meal_count == 0)
			// {
			// 	printf("finish\n");
			// 	return (1);
			// }
			i++;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || check_inputs(argc, argv, &data) == false)
	{
		printf("invalid inputs\n");
		return (1);
	}
	else
	{
		if (init(&data) == 1)
			return (1);
		// print_inputs(&data);
		if (create_threads(&data) == 0)
			ft_monitor(&data);
		join_thread(&data);
		destroy_free_all(&data);
	}
	return (0);
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