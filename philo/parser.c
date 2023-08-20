/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:16:20 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/20 14:39:43 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int check_argc(int argc)
{
	if (argc < 5 || argc > 6)
		return (-1);
	return (0);
}

int	parse_arg(int argc, char **argv)
{
	int	i;
	int	j;

	if (check_argc(argc) == -1)
	{
		printf("Error: wrong number of arguments\n");
		return (-1);

	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		if (ft_atoi(argv[i]) < 0)
			return (-1);
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
