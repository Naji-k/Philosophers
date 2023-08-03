/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 17:52:13 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/07/31 17:52:13 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_death_msg(t_data *data, int i, char *msg)
{
	long long	p_time;

	pthread_mutex_lock(&data->mutex_death);
	p_time = current_time() - data->start_time;
	data->dead = true;
	printf("%lld %d %s\n", p_time, i, msg);
	pthread_mutex_unlock(&data->mutex_death);
}

int	meal_counter(t_data *data, int i)
{
	pthread_mutex_lock(&data->philos[i].mutex_meal);
	if (data->philos[i].meal_count <= 0)
	{
		pthread_mutex_unlock(&data->philos[i].mutex_meal);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].mutex_meal);
	return (0);
}

bool	death_checker(t_data *data, int i)
{
	long long	time_since_eat;
	long long	now;

	now = current_time();
	pthread_mutex_lock(&data->time);
	time_since_eat = now - data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->time);
	if (time_since_eat > data->death_time)
		return (true);
	return (false);
}

bool	death_status(t_data *data, int check)
{
	bool	status;

	if (check == 0)
	{
		pthread_mutex_lock(&data->mutex_death);
		status = data->dead;
		pthread_mutex_unlock(&data->mutex_death);
	}
	else
	{
		pthread_mutex_lock(&data->mutex_death);
		data->dead = true;
		status = data->dead;
		pthread_mutex_unlock(&data->mutex_death);
	}
	return (status);
}

void	ft_monitor(t_data *data)
{
	int	i;
	int	done_eating;

	while (1)
	{
		i = 0;
		done_eating = 0;
		while (i < data->nb_philo)
		{
			if (data->must_eat > 0)
				done_eating += meal_counter(data, i);
			if (done_eating == data->nb_philo)
			{
				death_status(data, 1);
				printf("finish\n");
				return ;
			}
			if (death_checker(data, i) == true)
				return (print_death_msg(data, i, DIED));
			i++;
		}
	}
	return ;
}
