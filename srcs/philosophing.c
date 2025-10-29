/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:34:35 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/29 12:34:00 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static bool     take_forks(t_philo *p);
static bool     take_left_then_right(t_philo *philo);
static bool     take_right_then_left(t_philo *philo);
static bool     eat(t_philo *philo);
static bool     sleep_and_think(t_philo *philo);

/*
    Funcao principal de cada thread (filosofo)
    Implementa o ciclo : pegar garfos -> comer -> dormir -> pensar
*/
void    *philosophing(void  *philo)
{
    t_philo     *p;

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
/*
    Decide a Ordem de pegar os garfos baseado no ID (par u impar)
    Prevenindo deadlock
*/
static bool     take_forks(t_philo *p)
{
    if (p->philo_nbr % 2 == 0)
        return (take_right_then_left(p));
    else
        return (take_left_then_right(p));
}
static bool take_right_then_left(t_philo *philo)
{
    if (simulation_ended(philo))
        return (false);
    pthread_mutex_lock(philo->r_fork);
    if (!ft_message(philo, "has taken a fork"))
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
    if (!ft_message(philo, "has taken a fork"))
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
	if (!ft_message(philo, "has taken a fork"))
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
	if (!ft_message(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
		return (false);
	}
	return (true);
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
	if (!ft_message(philo, "is eating"))
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	ft_usleep_check(philo->table->t_2eat, philo);
	if (philo->table->max_rounds != -1)
	{
		pthread_mutex_lock(&philo->table->sync);
		if (philo->meal_nbr >= philo->table->max_rounds)
			philo->table->how_many_r_full++;
		pthread_mutex_unlock(&philo->table->sync);
	}
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (true);
}
static bool	sleep_and_think(t_philo *philo)
{
	if (!ft_message(philo, "is sleeping"))
		return (false);
	ft_usleep_check(philo->table->t_2sleep, philo);
	if (!ft_message(philo, "is thinking"))
		return (false);
	return (true);
}
