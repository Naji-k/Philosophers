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
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

struct s_data;

# define MAX_PHILO 200
//printing msgs
# define T_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

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
	int				meal_count;
	bool			finish;
	long long		last_meal_time;
	pthread_mutex_t	mutex_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	pthread_t		*thread_id;
	int				nb_philo;
	int				must_eat;
	int				finished;
	int				created_threads;
	t_philo			*philos;
	long long		death_time;
	long long		eat_time;
	long long		sleep_time;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	create;
	pthread_mutex_t	print;

}					t_data;

bool				check_inputs(int argc, char **argv, t_data *data);
long				ft_atoi(const char *str);
bool				valid_inputs(t_data *data, char **argv);
int					ft_monitor(t_data *data);
void				eat(t_philo *philo);
void				pickup_forks(t_philo *philo);
void				putdown_forks(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
//init
int					allocate_memory(t_data *data);
int					init(t_data *data);
void				init_philo(t_data *data);
void				init_forks(t_data *data);
bool				init_mutex(t_data *data);
void				destroy_mutex(t_data *data);

//utils
void				destroy_free_all(t_data *data);
long long			current_time(void);
void				ft_sleep(long long time);
void				print_msg(t_philo *philo, char *msg);
#endif

/* 
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
 */