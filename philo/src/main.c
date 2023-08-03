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
			destroy_free_all(&data, 1);
			return (1);
		}
		if (create_threads(&data) == 0)
			ft_monitor(&data);
		join_thread(&data);
		destroy_free_all(&data, 1);
	}
	return (0);
}
