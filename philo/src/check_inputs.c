/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_inputs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 19:28:38 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/07/11 19:28:38 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/**
 * @brief 1st func to check if the inputs are valid,
 * if inputs are valid, run valid_inputs (to convert from char to int)
 * @param argc 
 * @param argv 
 * @param data 
 * @return true 
 * @return false 
 */

bool	check_inputs(int argc, char **argv, t_data *data)
{
	while ((argc - 1) > 1)
	{
		if (ft_is_all_digit(argv[argc - 1]) != 0)
		{
			printf("NO DIGIT\n");
			return (false);
		}
		argc--;
	}
	if (valid_inputs(data, argv) == false)
		return (false);
	return (true);
}
/**
 * @brief if all is digit in one arg
 * 
 * @param str one arg
 * @return int 0 success, 1 fails
 */

int	ft_is_all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}
/**
 * @brief convert all args to long
 * check if the inputs is valid: non of them < 0, 
 * @param data 
 * @param argv 
 * @return true all args are valid
 * @return false one of args not valid
 */

bool	valid_inputs(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->dead = false;
	data->finished = false;
	data->created_threads = 0;
	if (data->nb_philo > MAX_PHILO || data->nb_philo <= 0 || data->eat_time <= 0
		|| data->sleep_time <= 0 || data->death_time <= 0 || data->must_eat \
		< -1)
		return (false);
	return (true);
}
