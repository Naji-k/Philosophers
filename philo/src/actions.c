/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 14:07:47 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/08/02 14:07:47 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/**
 * @brief pickup the low id fork first and check if one of philo dies or not
 * 
 * @param philo 
 * @return true 
 * @return false if philo die drop the fork
 */

bool	pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (print_msg(philo, T_FORK))
	{
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	pthread_mutex_lock(philo->l_fork);
	if (print_msg(philo, T_FORK))
	{
		putdown_forks(philo);
		return (false);
	}
	return (true);
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

bool	eat(t_philo *philo)
{
	if (!pickup_forks(philo))
		return (false);
	if (print_msg(philo, EATING))
	{
		putdown_forks(philo);
		return (false);
	}
	pthread_mutex_lock(&philo->data->time);
	philo->last_meal_time = current_time();
	pthread_mutex_unlock(&philo->data->time);
	pthread_mutex_lock(&philo->mutex_meal);
	philo->meal_count--;
	pthread_mutex_unlock(&philo->mutex_meal);
	ft_sleep(philo->data->eat_time);
	putdown_forks(philo);
	return (true);
}

bool	philo_sleep(t_philo *philo)
{
	if (print_msg(philo, SLEEPING))
		return (false);
	ft_sleep(philo->data->sleep_time);
	return (true);
}
