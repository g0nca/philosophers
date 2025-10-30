/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:52:55 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/30 09:55:45 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/*
    Delay inicial para dessincronizar filosofos
    Filosofos pares esperam 10ms antes de comecar
*/
void	initial_delay(t_philo *philo)
{
	if (philo->philo_nbr % 2 == 0)
		ft_usleep_check(10, philo);
}

/*
    Caso especial : Apenas 1 filosofo
    Pega um garfo e aguarda ate morrer pois nao pode comer apenas com um garfo
*/
void	*ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	ft_message(philo, BOLD GREEN "has taken a fork" RESET);
	ft_usleep_check(philo->table->t_2die, philo);
	pthread_mutex_unlock(&philo->l_fork);
	return (NULL);
}

bool	simulation_ended(t_philo *philo)
{
	bool	ended;

	pthread_mutex_lock(&philo->table->sync);
	ended = philo->table->philo_dead || philo->table->philos_full;
	pthread_mutex_unlock(&philo->table->sync);
	return (ended);
}
