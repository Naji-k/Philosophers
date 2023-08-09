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

void	check_leaks(void)
{
	system("leaks -q philo");
}
/**
 * @brief this is the main func in Philo
 * 1st check if the inputs are valid, then convert them to long,
 * 2nd init (allocate memory, init_mutexes, init_forks...)
 * create threads (if created successfully run the ft_monitor,
 * otherwise join(created_threads) and destroy
 * @param argc 
 * @param argv 
 * @return int 
 */

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
		{
			return (1);
		}
		if (create_threads(&data) == 0)
			ft_monitor(&data);
		join_thread(&data);
		free_all_destroy(&data, true, data.nb_philo,
			data.nb_philo);
	}
	return (0);
}
