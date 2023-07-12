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
	printf("num_philo= %d\n", data->n_philo);
	printf("time_to_die= %llu\n", data->death_time);
	printf("time_to_eat= %llu\n", data->eat_time);
	printf("time_to_sleep= %llu\n", data->sleep_time);
	printf("num_of_meals= %d\n", data->meals_nb);
}

void	init_data(t_data *data, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->meals_nb = ft_atoi(argv[5]);
	else
		data->meals_nb = 0;
}

int	main(int argc, char **argv)
{
	t_data data;
	// t_philo *philo;

	// philo = NULL;
	printf("number of argc=%d\n", argc);
	if (argc > 4)
	{
		if (check_inputs(argc, argv) == 0)
		{
			printf("========\n");
			init_data(&data, argv);
			print_inputs(&data);
		}
	}
	else
		printf("invalid inputs\n");
}