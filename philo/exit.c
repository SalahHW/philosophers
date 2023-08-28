/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:20:56 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/28 22:16:47 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

static void	destroy_mutex(t_philo *philo)
{
	pthread_mutex_destroy(&philo->fork);
	pthread_mutex_destroy(&philo->nb_eat_done_mutex);
	pthread_mutex_destroy(&philo->last_meal_mutex);
}

void	clear_all(t_philo *philo)
{
	t_philo	*tmp_philo;
	int		nb_philo;
	int		i;

	i = 0;
	nb_philo = philo->data->nb_philo;
	while (i < nb_philo)
	{
		destroy_mutex(philo);
		tmp_philo = philo->next;
		if (i == nb_philo - 1)
			pthread_mutex_destroy(&philo->data->sim_running_mutex);
		free(philo);
		philo = tmp_philo;
		i++;
	}
}
