/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:19:22 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/29 14:49:23 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	create_philo(t_philo *philo, t_data *data)
{
	t_philo	*first_philo;
	int		i;

	first_philo = philo;
	i = 0;
	while (i < data->nb_philo)
	{
		philo->next = NULL;
		philo->id = i + 1;
		philo->nb_eat_done = 0;
		philo->data = data;
		philo->last_meal = get_time_stamp();
		pthread_mutex_init(&philo->fork, NULL);
		pthread_mutex_init(&philo->nb_eat_done_mutex, NULL);
		pthread_mutex_init(&philo->last_meal_mutex, NULL);
		if (i == data->nb_philo - 1)
			break ;
		philo->next = malloc(sizeof(t_philo));
		philo = philo->next;
		i++;
	}
	philo->next = first_philo;
	philo = first_philo;
}

static void	launch_philo_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_create(&philo->thread, NULL, philo_routine, philo);
		philo = philo->next;
		i++;
	}
}

static void	join_philo_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
	philo = philo->next;
}

void	simulation_monitor(t_philo *philo)
{
	int	sim_running;

	pthread_mutex_lock(&philo->data->sim_running_mutex);
	sim_running = philo->data->simulation_running;
	pthread_mutex_unlock(&philo->data->sim_running_mutex);
	while (sim_running)
	{
		pthread_mutex_lock(&philo->data->sim_running_mutex);
		sim_running = philo->data->simulation_running;
		pthread_mutex_unlock(&philo->data->sim_running_mutex);
		check_philo_health(philo);
		if (philo->data->nb_eat != -1)
		{
			if (has_finished_eat(philo))
			{
				pthread_mutex_lock(&philo->data->sim_running_mutex);
				philo->data->simulation_running = 0;
				pthread_mutex_unlock(&philo->data->sim_running_mutex);
			}
		}
		pthread_mutex_lock(&philo->data->sim_running_mutex);
		sim_running = philo->data->simulation_running;
		pthread_mutex_unlock(&philo->data->sim_running_mutex);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (!parse_arg(argc, argv))
		return (-1);
	if (ft_atoi(argv[1]) == 1)
	{
		printf("1 1 has taken a fork\n");
		usleep(ft_atoi(argv[2]) * 1000);
		printf("%d 1 died\n", ft_atoi(argv[2]) + 1);
		return (0);
	}
	philo = malloc(sizeof(t_philo));
	init_data(argc, argv, &data);
	create_philo(philo, &data);
	launch_philo_threads(philo);
	simulation_monitor(philo);
	join_philo_threads(philo);
	clear_all(philo);
}
