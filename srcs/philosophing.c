/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:34:35 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/13 15:47:14 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static  void    ft_one_philo(t_philo *philo);
static  bool    ft_check_death(t_philo *philo);


void    *philosophing(void  *philo)
{
    t_philo     *philo_x;
    int         one_philo;

    one_philo = 0;
    philo_x = (t_philo *)philo;
    while(1)
    {
        if (philo_x->table->n_philos == 1 && one_philo == 0)
        {
            ft_one_philo(philo_x);
            one_philo = 1;
        }
        if (ft_check_death(philo_x) == true)
            break ;
    }
    return (false);
}

static  bool    ft_check_death(t_philo *philo)
{
    if ((int )(ft_time_ms() - philo->table->start_time) >= philo->table->t_2die)
    {
        printf("%lu [%d] died\n", ft_time_ms() - philo->table->start_time, philo->philo_nbr);
        philo->table->philo_dead = true;
        return (true);
    }
    return (false);
}    
static  void    ft_one_philo(t_philo *philo)
{
    pthread_mutex_lock(&philo->l_fork);
    printf("%lu [%d] has taken a fork\n", ft_time_ms() - philo->table->start_time, philo->philo_nbr);
    pthread_mutex_unlock(&philo->l_fork);
}