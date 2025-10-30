/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:21:13 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/30 09:48:16 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static	bool	check_death(t_table *table, int x)
{
	if (ft_time_ms() - table->philo[x].last_meal > (uint64_t)table->t_2die)
	{
		table->philo_dead = true;
		printf(BOLD UNDERLINE BRIGHT_BLUE "%lu"RESET BOLD" [%d]"
			BOLD MAGENTA" died\n"RESET, ft_time_ms() - table->start_time,
			table->philo[x].philo_nbr);
		table->end_simulation = true;
		pthread_mutex_unlock(&table->sync);
		return (true);
	}
	return (false);
}

static bool	check_philo_full(t_table *table)
{
	if (table->max_rounds != -1 && table->how_many_r_full >= table->n_philos)
	{
		table->philos_full = true;
		printf(BOLD BRIGHT_CYAN "Every Philosopher has eaten %d times\n" RESET,
			table->max_rounds);
		table->end_simulation = true;
		pthread_mutex_unlock(&table->sync);
		return (true);
	}
	return (false);
}

void	philos_monitor(t_table *table)
{
	int	x;

	while (!table->end_simulation)
	{
		x = 0;
		while (x < table->n_philos)
		{
			pthread_mutex_lock(&table->sync);
			if (check_death(table, x) == true)
				break ;
			if (check_philo_full(table) == true)
				break ;
			pthread_mutex_unlock(&table->sync);
			x++;
		}
		usleep(500);
	}
}
