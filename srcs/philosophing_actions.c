/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing_sleep_think.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:17:02 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/30 09:50:00 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static bool	take_right_then_left(t_philo *philo);
static bool	take_left_then_right(t_philo *philo);

bool	sleep_and_think(t_philo *philo)
{
	if (!ft_message(philo, BOLD BLUE "is sleeping" RESET))
		return (false);
	ft_usleep_check(philo->table->t_2sleep, philo);
	if (!ft_message(philo, BOLD BRIGHT_YELLOW "is thinking" RESET))
		return (false);
	return (true);
}

/*
    Decide a Ordem de pegar os garfos baseado no ID (par u impar)
    Prevenindo deadlock
*/
bool	take_forks(t_philo *p)
{
	if (p->philo_nbr % 2 == 0)
		return (take_right_then_left(p));
	else
		return (take_left_then_right(p));
}

static bool	take_right_then_left(t_philo *philo)
{
	if (simulation_ended(philo))
		return (false);
	pthread_mutex_lock(philo->r_fork);
	if (!ft_message(philo, BOLD GREEN "has taken a fork" RESET))
	{
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	if (simulation_ended(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	pthread_mutex_lock(&philo->l_fork);
	if (!ft_message(philo, BOLD GREEN "has taken a fork" RESET))
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	return (true);
}

static bool	take_left_then_right(t_philo *philo)
{
	if (simulation_ended(philo))
		return (false);
	pthread_mutex_lock(&philo->l_fork);
	if (!ft_message(philo, BOLD GREEN "has taken a fork" RESET))
	{
		pthread_mutex_unlock(&philo->l_fork);
		return (false);
	}
	if (simulation_ended(philo))
	{
		pthread_mutex_unlock(&philo->l_fork);
		return (false);
	}
	pthread_mutex_lock(philo->r_fork);
	if (!ft_message(philo, BOLD GREEN "has taken a fork" RESET))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
		return (false);
	}
	return (true);
}
