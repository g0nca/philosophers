/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:57:21 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/13 11:55:10 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void     start_simulation(t_table *table);
static bool     check_args(int ac, char **av, t_table *table);
static bool     check_args_nbrs(char **av);

//philosophers 8 800 100 100 [5]
// n_philos | t_2die | t_2eat | t_2sleep | number_of_time_each_philo_must_eat (Optional Argument)

int main(int ac, char **av)
{
    t_table     table;

    if (check_args(ac, av, &table) == true)
        return (false);
    start_simulation(&table);
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
bool     check_args(int ac, char **av, t_table *table)
{
    if (ac != 5 && ac != 6)
        return (printf("%d -> Wrong Number of Args\n", ac), true);
    else if (check_args_nbrs(av) == true)
        return (printf("Only Numbers are Accept\n"), true);
    if (init_table(ac, av, table) == true)
        return (true);
     /* for (int i = 0; i < table->n_philos; i++)
        printf("Philo_ID:[%d]\n", table->philo[i].philo_nbr); */
    return (false);
}
bool    check_args_nbrs(char **av)
{
    int     i;
    int     j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] < '0' || av[i][j] > '9')
                return (true);
            else
                j++;
        }
        i++;
    }
    return (false);
}
