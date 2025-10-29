/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:58:47 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/29 12:58:55 by ggomes-v         ###   ########.fr       */
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

/* ========================== TEXT STYLES ========================== */
# define RESET        "\033[0m"
# define BOLD         "\033[1m"
# define DIM          "\033[2m"
# define ITALIC       "\033[3m"
# define UNDERLINE    "\033[4m"
# define BLINK        "\033[5m"
# define REVERSE      "\033[7m"
# define HIDDEN       "\033[8m"

/* ========================== BASIC COLORS ========================== */
# define BLACK        "\033[30m"
# define RED          "\033[31m"
# define GREEN        "\033[32m"
# define YELLOW       "\033[33m"
# define BLUE         "\033[34m"
# define MAGENTA      "\033[35m"
# define CYAN         "\033[36m"
# define WHITE        "\033[37m"

/* ====================== BRIGHT (INTENSE) COLORS ===================== */
# define BRIGHT_BLACK   "\033[90m"
# define BRIGHT_RED     "\033[91m"
# define BRIGHT_GREEN   "\033[92m"
# define BRIGHT_YELLOW  "\033[93m"
# define BRIGHT_BLUE    "\033[94m"
# define BRIGHT_MAGENTA "\033[95m"
# define BRIGHT_CYAN    "\033[96m"
# define BRIGHT_WHITE   "\033[97m"

/* ============================ BACKGROUNDS =========================== */
# define BG_BLACK       "\033[40m"
# define BG_RED         "\033[41m"
# define BG_GREEN       "\033[42m"
# define BG_YELLOW      "\033[43m"
# define BG_BLUE        "\033[44m"
# define BG_MAGENTA     "\033[45m"
# define BG_CYAN        "\033[46m"
# define BG_WHITE       "\033[47m"

/* ======================= BRIGHT BACKGROUNDS ======================== */
# define BG_BRIGHT_BLACK   "\033[100m"
# define BG_BRIGHT_RED     "\033[101m"
# define BG_BRIGHT_GREEN   "\033[102m"
# define BG_BRIGHT_YELLOW  "\033[103m"
# define BG_BRIGHT_BLUE    "\033[104m"
# define BG_BRIGHT_MAGENTA "\033[105m"
# define BG_BRIGHT_CYAN    "\033[106m"
# define BG_BRIGHT_WHITE   "\033[107m"

/* ===================== 256 COLOR MODE (ADVANCED) ===================== */
/* Example: "\033[38;5;196m" → Red, "\033[48;5;21m" → Blue background */

# define COLOR_256(x)      "\033[38;5;"x"m"
# define BG_COLOR_256(x)   "\033[48;5;"x"m"

/* ===================== COMMON COMBINATIONS ===================== */
# define SUCCESS_COLOR   "\033[1;32m"   /* bold green */
# define WARNING_COLOR   "\033[1;33m"   /* bold yellow */
# define ERROR_COLOR     "\033[1;31m"   /* bold red */
# define INFO_COLOR      "\033[1;36m"   /* bold cyan */
# define ACTION_COLOR    "\033[1;35m"   /* bold magenta */
# define TIME_COLOR      "\033[90m"     /* gray */

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
    uint64_t        start_time;
    pthread_mutex_t sync;
    t_philo         philo[200];
}   t_table;

bool    init_table(int ac, char **av, t_table *table);


void    *philosophing(void  *philo);

bool     check_args(int ac, char **av, t_table *table);
bool    check_args_nbrs(char **av);

int	ft_atoi(const char *str);
uint64_t	ft_time_ms(void);
void	error_exit(const char *str);
bool    ft_message(t_philo *philo, const char *message);
void	ft_usleep_check(uint64_t ms, t_philo *philo);
bool		simulation_ended(t_philo *philo);

void     initial_delay(t_philo *philo);
void    *ft_one_philo(t_philo *philo);

void            philos_monitor(t_table *table);

#endif