/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:57:21 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/14 11:04:12 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void    destroy_mutex(t_table *table);
static void    join_threads(t_table *table);
static void     start_simulation(t_table *table);
void    philos_monitor(t_table *table);

//philosophers 8 800 100 100 [5]
// n_philos | t_2die | t_2eat | t_2sleep | number_of_time_each_philo_must_eat (Optional Argument)

int main(int ac, char **av)
{
    t_table     table;

    if (check_args(ac, av, &table) == true)
        return (false);
    pthread_mutex_init(&table.sync, NULL);
    start_simulation(&table);
    philos_monitor(&table);
    join_threads(&table);
    destroy_mutex(&table);
    return (0);
}

void    start_simulation(t_table *table)
{
    int x;

    x = 0;
    while (x < table->n_philos)
    {
        pthread_create(&table->philo[x].thread, NULL, philosophing, &table->philo[x]);
        x++;
    }
}

void    philos_monitor(t_table *table)
{
    int x;
    bool end_simulation;

    end_simulation = 0;
    while (!end_simulation)
    {
        x = 0;
        while (x < table->n_philos)
        {
            pthread_mutex_lock(&table->sync);
            if (ft_time_ms() - table->philo[x].last_meal > (uint64_t)table->t_2die)
            {
                table->philo_dead = true;
                printf("%lu [%d] died\n", ft_time_ms() - table->start_time, table->philo[x].philo_nbr);
                end_simulation = true;
                pthread_mutex_unlock(&table->sync);
                break ;
            }
            if (table->max_rounds != -1 && table->how_many_r_full >= table->n_philos)
            {
                table->philos_full = true;
                printf("Every Philosopher has eaten %d times\n", table->max_rounds);
                pthread_mutex_unlock(&table->sync);
            }
            pthread_mutex_unlock(&table->sync);
            x++;
        }
        usleep(1000);
    }
}

void    join_threads(t_table *table)
{
    (void)table;
    int     x;

    x = 0;
    while (x < table->n_philos)
    {
        pthread_join(table->philo[x].thread, NULL);
        x++;
    }
}

void    destroy_mutex(t_table *table)
{
    int x;

    x = 0;
    while (x < table->n_philos)
    {
        pthread_mutex_destroy(&table->philo[x].l_fork);
        x++;
    }
    pthread_mutex_destroy(&table->sync);
}

