/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:34:35 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/13 11:55:28 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void     ft_one_philo(t_philo *philo);

void    *philosophing(void  *philo)
{
    t_philo     *philo_x;

    philo_x = (t_philo *)philo;
    printf("NBR:%d\n", philo_x->table->n_philos);
    while(1)
    {
        if (philo_x->table->n_philos == 1)
            ft_one_philo(philo_x);
    }
}

static void     ft_one_philo(t_philo *philo)
{
    pthread_mutex_lock(&philo->l_fork);
    printf("[%d] has taken a fork\n", philo->philo_nbr);
    pthread_mutex_unlock(&philo->l_fork);
}