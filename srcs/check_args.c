/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 09:41:57 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/30 09:56:00 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	check_args(int ac, char **av, t_table *table)
{
	if (ac != 5 && ac != 6)
		return (printf("%d -> Wrong Number of Args\n", ac), true);
	else if (check_args_nbrs(av) == true)
		return (printf("Only Numbers are Accept\n"), true);
	if (init_table(ac, av, table) == true)
		return (true);
	return (false);
}

bool	check_args_nbrs(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (true);
			else
				j++;
		}
		i++;
	}
	return (false);
}
