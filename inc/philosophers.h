/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:58:47 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/09/26 15:49:21 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <ctype.h>
# include <stdint.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>

typedef struct s_philo
{
    int                 philo_nbr;
    int                 meal_nbr;
    uint64_t            last_meal;
    pthread_t           thread;
    pthread_mutex_t     l_fork;
    pthread_mutex_t     *r_fork;
    struct s_table       *table;
}   t_philo;

typedef struct s_table
{
    int             n_philos;
    int             t_2eat;
    int             t_2sleep;
    int             t_2die;
    int             max_rounds;
    int             how_many_r_full;
    bool            philo_dead;
    bool            philos_full;
    bool            args_error;
    uint64_t        start_time;
    pthread_mutex_t sync;
    t_philo         philo[200];
}   t_table;

bool    init_table(int ac, char **av, t_table *table);


int	ft_atoi(const char *str);
#endif