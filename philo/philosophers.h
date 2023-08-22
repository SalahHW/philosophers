/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:21:36 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/23 00:30:31 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				dead;
	int				simulation_running;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_eat;
	int 			nb_eat_done;
	size_t			last_meal;
	pthread_mutex_t	fork;
	pthread_t		thread;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

typedef struct s_data
{
	int				simulation_running;
	size_t			start_time;
	int				nb_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_eat;
	t_philo			*first_philo;
	t_philo			*last_philo;
	pthread_t		health;
}					t_data;

// parser.c
int					parse_arg(int argc, char **argv);
// error.c
int					print_error(char *str);
// init.c
int					add_new_philo(t_data *data);
t_data				*init_data(int argc, char **argv);
void				init_philo_data(t_data *data);
// utils.c
int					ft_atoi(const char *str);
// time.c
size_t				get_time_stamp(void);
size_t				get_program_time(size_t start_time);
void				my_usleep(size_t time);
// routine.c
void				*philo_routine(void *arg);
void				*health_routine(void *arg);
// state.c
int					eating(t_philo *philo);
int					sleeping(t_philo *philo);
int					thinking(t_philo *philo);
int					check_philo_health(t_philo *philo);

#endif