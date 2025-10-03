/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:57:21 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/09/26 15:49:46 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static bool     check_args(int ac, char **av, t_table *table);
static bool     check_args_nbrs(char **av);

int main(int ac, char **av)
{
    t_table     table;

    if (check_args(ac, av, &table) == true)
        return (false);
    
    return (0);
}
bool     check_args(int ac, char **av, t_table *table)
{
    if (ac != 5 && ac != 6)
        return (printf("%d -> Wrong Number of Args\n", ac), true);
    else if (check_args_nbrs(av) == true)
        return (printf("Only Numbers are Accept\n"), true);
    if (init_table(ac, av, table) == true)
        return (printf("Fail, Init Table Struct") ,true);
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
