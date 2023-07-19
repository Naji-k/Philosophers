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

//check inputs if there is any characters

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
	if (data->nb_philo > MAX_PHILO || data->nb_philo <= 0 || data->eat_time <= 0
		|| data->sleep_time <= 0 || data->death_time <= 0 || data->must_eat <
		-1)
		return (false);
	return (true);
}
