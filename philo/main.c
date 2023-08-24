/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:19:22 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/24 21:28:03 by sbouheni         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_data data;
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (parse_arg(argc, argv) == -1)
		return (-1);
	init_data(argc, argv, &data);
	create_philo(philo, &data);
	launch_philo_threads(philo);
	while (philo->data->simulation_running)
	{
		check_philo_health(philo);
		if (philo->data->nb_eat != -1)
		{
			if (has_finished_eat(philo))
				philo->data->simulation_running = 0;
		}
	}
	join_philo_threads(philo);
}