/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:34:35 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/14 12:33:55 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static  void    *ft_one_philo(t_philo *philo);
static void     initial_delay(t_philo *philo);

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
    Delay inicial para dessincronizar filosofos
    Filosofos pares esperam 10ms antes de comecar
*/
static void     initial_delay(t_philo *philo)
{
    if (philo->philo_nbr % 2 == 0)
        ft_usleep_check(10, philo);
}
/*
    Caso especial : Apenas 1 filosofo
    Pega um garfo e aguarda ate morrer pois nao pode comer apenas com um garfo
*/
static  void    *ft_one_philo(t_philo *philo)
{
    pthread_mutex_lock(&philo->l_fork);
    ft_message(philo, "has taken a fork");
    ft_usleep_check(philo->table->t_2die, philo);
    pthread_mutex_unlock(&philo->l_fork);
    return (NULL);
}