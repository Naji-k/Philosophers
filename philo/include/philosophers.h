/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 23:33:58 by nakanoun      #+#    #+#                 */
/*   Updated: 2023/06/22 23:33:58 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
#include <sys/time.h>


struct	s_data;

typedef enum s_ph_status
{
	EAT,
	THINK,
	SLEEP,
	DIE,
}					t_ph_status;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	t_ph_status		status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	pthread_t		*thread_id;
	int				nb_philo;
	int				meals_nb;
	int				finished;
	t_philo			*philos;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;

}					t_data;

int					check_inputs(int argc, char **argv);
long				ft_atoi(const char *str);

//init
int					allocate_memory(t_data *data);
void				init(t_data *data, char **argv);
int					init_philo(t_data *data);
int					init_forks(t_data *data);

//utils
void				free_all(t_data *data);

#endif