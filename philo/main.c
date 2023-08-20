/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:19:22 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/20 15:12:13 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (parse_arg(argc, argv) == -1)
		return (-1);
	data = init_data(argc, argv);
	if (!data)
		return (-1);
	if (init_philo(data) == -1)
		return (-1);
	if (create_philo(data) == -1)
		return (-1);
	if(!pthread_create(&data->check_health, NULL, health_routine, data))
		return (-1);
	if(!pthread_join(data->check_health, NULL))
	{
		printf("A philosopher died\n");
		return (0);
	}
	return (0);
}
