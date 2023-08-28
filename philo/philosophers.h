/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:21:36 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/28 23:19:37 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				simulation_running;
	size_t			start_time;
	int				nb_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_eat;
	pthread_mutex_t	sim_running_mutex;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				nb_eat_done;
	size_t			last_meal;
	pthread_mutex_t	fork;
	pthread_mutex_t	nb_eat_done_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_t		thread;
	t_data			*data;
	struct s_philo	*next;
}					t_philo;

// parser.c
int					parse_arg(int argc, char **argv);
// exit.c
void				clear_all(t_philo *philo);
// init.c
void				init_data(int argc, char **argv, t_data *data);
// utils.c
int					ft_atoi(const char *str);
long				ft_atol(char *str);
int					ft_isdigit(int n);
// time.c
size_t				get_time_stamp(void);
int					my_msleep(size_t time, t_data *data);
// routine.c
void				*philo_routine(void *arg);
// routine_utils.c
int					check_philo_health(t_philo *philo);
int					has_finished_eat(t_philo *philo);
#endif
