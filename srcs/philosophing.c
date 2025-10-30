/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:34:35 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/30 09:49:04 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static bool	eat_check_message(t_philo *philo);
static void	eat_check_max_rounds(t_philo *philo);
static bool	eat(t_philo *philo);

/*
    Funcao principal de cada thread (filosofo)
    Implementa o ciclo : pegar garfos -> comer -> dormir -> pensar
*/
void	*philosophing(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->table->n_philos == 1)
		return (ft_one_philo(philo));
	initial_delay(p);
	while (!simulation_ended(p))
	{
		if (!take_forks(p))
			break ;
		if (!eat(p))
			break ;
		if (!sleep_and_think(p))
			break ;
	}
	return (NULL);
}

static bool	eat(t_philo *philo)
{
	if (simulation_ended(philo))
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	pthread_mutex_lock(&philo->table->sync);
	philo->meal_nbr++;
	philo->last_meal = ft_time_ms();
	pthread_mutex_unlock(&philo->table->sync);
	if (eat_check_message(philo) == true)
		return (false);
	eat_check_max_rounds(philo);
	ft_usleep_check(philo->table->t_2eat, philo);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (true);
}

static bool	eat_check_message(t_philo *philo)
{
	if (!ft_message(philo, BOLD RED "is eating" RESET))
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (true);
	}
	return (false);
}

static void	eat_check_max_rounds(t_philo *philo)
{
	if (philo->table->max_rounds != -1)
	{
		pthread_mutex_lock(&philo->table->sync);
		if (philo->meal_nbr >= philo->table->max_rounds)
			philo->table->how_many_r_full++;
		pthread_mutex_unlock(&philo->table->sync);
	}
}
