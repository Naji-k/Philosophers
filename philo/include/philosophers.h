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

# define MAX_PHILO 200

//printing msgs
# define T_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "is died"
# define FINISH "finish"

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
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
	bool			finished;
	bool			dead;
	int				created_threads;
	t_philo			*philos;
	long long		death_time;
	long long		eat_time;
	long long		sleep_time;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_create;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	time;

}					t_data;

long				ft_atoi(const char *str);

//pthreads
int					create_threads(t_data *data);
int					join_thread(t_data *data);
bool				thread_checker(t_data *data);
void				*routine(void *arg);

//check_inputs
int					ft_is_all_digit(char *str);
bool				check_inputs(int argc, char **argv, t_data *data);
bool				valid_inputs(t_data *data, char **argv);

//actions
bool				eat(t_philo *philo);
bool				pickup_forks(t_philo *philo);
void				putdown_forks(t_philo *philo);
bool				philo_sleep(t_philo *philo);

//init
int					allocate_memory(t_data *data);
int					init(t_data *data);
int					init_philo(t_data *data);
void				init_forks(t_data *data);
bool				init_mutex(t_data *data);
void				destroy_mutex(t_data *data, int forks, int meals);

//utils
void				free_all_destroy(t_data *data, bool destroy, int forks,
						int meals);
long long			current_time(void);
void				ft_sleep(long long time);
bool				print_msg(t_philo *philo, char *msg);

//monitor
void				ft_monitor(t_data *data);
int					meal_counter(t_data *data, int i);
void				print_death_msg(t_data *data, int i, char *msg);
bool				death_checker(t_data *data, int i);
bool				death_status(t_data *data, int check);
#endif

/* 
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
 */