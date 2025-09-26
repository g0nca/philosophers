/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:51:06 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/09/26 16:01:52 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool    init_table(int ac, char **av, t_table *table)
{
    table->n_philos = ft_atoi(av[1]);
    table->t_2die = ft_atoi(av[2]);
    table->t_2eat = ft_atoi(av[3]);
    table->t_2sleep = ft_atoi(av[4]);
    table->start_time = ft_time_ms();
    table->how_many_r_full = 0;
    table->philo_dead = false;
    table->philos_full = false;
    if (ac == 6)
        table->max_rounds = ft_atoi(av[5]);
    else
        table->max_rounds = -1;
    return (false);
}
