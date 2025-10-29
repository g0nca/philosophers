/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:51:06 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/29 12:10:15 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static bool    check_limits(t_table *table);
static void philos_start(t_table *table);

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
    if (check_limits(table) == true)
        return (true);
    philos_start(table);
    return (false);
}
static void philos_start(t_table *table)
{
    int i;

    i = 0;
    while (i < table->n_philos)
    {
        table->philo[i].philo_nbr = i + 1;
        table->philo[i].last_meal = table->start_time;
        table->philo[i].table = table;
        table->philo[i].meal_nbr = 0;
        pthread_mutex_init(&table->philo[i].l_fork, NULL);
        if (i + 1 == table->n_philos)
            table->philo[i].r_fork = &table->philo[0].l_fork;
        else
            table->philo[i].r_fork = &table->philo[i + 1].l_fork;
        i++;
    }
}
static bool    check_limits(t_table *table)
{
    if (table->n_philos < 1 || table->n_philos > 200)
        error_exit("Error\nNumber of philosophers must be between 1 and 200 !!!");
    if ((table->t_2die < 60 || table->t_2eat < 60 || table->t_2sleep < 60) 
        || (table->t_2die > INT_MAX || table->t_2eat > INT_MAX || table->t_2sleep > INT_MAX))
        error_exit("Error\nTime to die, sleep or eat is Wrong !!!");
    if (table->max_rounds < -1 || table->max_rounds > INT_MAX)
        error_exit("Error\nAmount of Time to eat ir Wrong !!!");
    return (false);
}
