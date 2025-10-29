/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:36:11 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/29 13:55:49 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			neg *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * neg);
}
uint64_t	ft_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
void	error_exit(const char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}
/* Imprime a mensagem apenas se a simulacao nao terminou */
bool    ft_message(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->table->sync);
	if (philo->table->philo_dead == true || philo->table->philos_full == true)
	{
		pthread_mutex_unlock(&philo->table->sync);
		return (false);
	}
    printf(BOLD UNDERLINE BRIGHT_BLUE "%lu"RESET BOLD WHITE" [%d] %s\n", ft_time_ms() - philo->table->start_time, philo->philo_nbr, message);
    pthread_mutex_unlock(&philo->table->sync);
	return (true);
}

void	ft_usleep_check(uint64_t ms, t_philo *philo)
{
	uint64_t	start;

	start = ft_time_ms();
	while (ft_time_ms() - start < ms)
	{
		if (simulation_ended(philo))
			break ;
		usleep(500);
	}
}

bool		simulation_ended(t_philo *philo)
{
	bool	ended;

	pthread_mutex_lock(&philo->table->sync);
	ended = philo->table->philo_dead || philo->table->philos_full;
	pthread_mutex_unlock(&philo->table->sync);
	return (ended);
}

