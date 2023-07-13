/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 16:16:33 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/07/13 16:16:33 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_data *data)
{
	free(data->thread_id);
	free(data->philos);
	free(data->forks);
}

u_int64_t	current_time(t_data *data)
{
	struct timeval start_time;
	u_int64_t start_t;

	gettimeofday(&start_time, NULL);
	start_t = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
	data->start_time = start_t;
	return (start_t);
}