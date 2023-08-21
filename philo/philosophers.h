/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:21:36 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/21 20:49:45 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_state
{
	DEAD = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
}					e_state;

typedef struct s_philo
{
	int				id;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_eat;
	size_t			last_meal;
	e_state			state;
	pthread_mutex_t	fork;
	pthread_t		thread;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

typedef struct s_data
{
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
void					init_philo_data(t_data *data);
// utils.c
int					ft_atoi(const char *str);
size_t				get_time_stamp(void);
// routine.c
void				*philo_routine(void *arg);
void				*health_routine(void *arg);

#endif
