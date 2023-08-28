/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:16:20 by sbouheni          #+#    #+#             */
/*   Updated: 2023/08/28 22:35:15 by sbouheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_zero(char *str)
{
	if ((str[0] && str[0] == '0') && str[1])
		return (1);
	return (0);
}

static int	is_convertible_to_int(char *argv)
{
	int		digit_count;
	char	*argv_ptr;

	argv_ptr = argv;
	digit_count = 0;
	if (*argv_ptr == '-' || *argv_ptr == '+')
		return (0);
	while (*argv_ptr)
	{
		if (digit_count > 10 || !ft_isdigit(*argv_ptr))
			return (0);
		digit_count++;
		argv_ptr++;
	}
	if (digit_count == 0)
		return (0);
	if (ft_atol(argv) < 1 || ft_atol(argv) > 2147483647)
		return (0);
	return (1);
}

static int	check_value(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i][0]))
		{
			printf("Error : Argument %d does not begin whith digit\n", i);
			return (0);
		}
		if (check_zero(argv[i]))
		{
			printf("Error : Arguments %d is invalid\n", i);
			return (0);
		}
		if (!is_convertible_to_int(argv[i]))
		{
			printf("Error : Arguments %d is invalid\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_arg(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error : Wrong number of arguments\n");
		return (0);
	}
	if (!check_value(argv))
		return (0);
	return (1);
}
