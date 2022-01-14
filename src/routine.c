/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:59:25 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/14 16:25:22 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

void	*routine(void *arg)
{
	t_input	*input;
	t_philo	*philo;
	int		eat;

	(void)arg;
	eat = 0;
	input = get_input();
	pthread_mutex_lock(input->i_p_lock);
	philo = get_philos()[input->i_p];
	pthread_mutex_unlock(input->i_p_lock);
	pthread_mutex_lock(input->running_lock);
	philo->running = true;
	pthread_mutex_unlock(input->running_lock);
	pthread_mutex_lock(input->wait_lock);
	while (input->wait == true)
	{
		pthread_mutex_unlock(input->wait_lock);
		usleep(1);
		pthread_mutex_lock(input->wait_lock);
	}
	pthread_mutex_lock(philo->time_lock);
	philo->time_philo = get_time();
	pthread_mutex_unlock(philo->time_lock);
	pthread_mutex_unlock(input->wait_lock);
	if (philo->philo_n % 2 == 0)
	{
		// if (input->tt_eat / 2 < 2)
		// 	usleep(1500);
		// else
			ft_sleep(input->tt_eat / 2);
	}
	while ((input->n_must_eat[0] == true && eat < input->n_must_eat[1]
		&& eat < INT_MAX - 1) || (input->n_must_eat[0] == false && eat < INT_MAX)) //test with MAX_INT
	{
		pthread_mutex_lock(&input->forks[philo->fork_r]);
		print_state(input, philo, grabbed_fork);
		if (input->n_philos == 1)
		{
			pthread_mutex_unlock(&input->forks[philo->fork_r]);
			ft_sleep(input->tt_die + 1);
			break ;
		}
		pthread_mutex_lock(&input->forks[philo->fork_l]);
		print_state(input, philo, grabbed_fork);
		pthread_mutex_lock(input->death_lock);
		if (input->death == false)
		{
			pthread_mutex_unlock(input->death_lock);
			// eat
			print_state(input, philo, is_eating);
			pthread_mutex_lock(philo->eat_lock);
			philo->eating = true;
			pthread_mutex_unlock(philo->eat_lock);
			pthread_mutex_lock(philo->time_lock);
			philo->time_philo = get_time();
			pthread_mutex_unlock(philo->time_lock);
			ft_sleep(input->tt_eat);
			pthread_mutex_unlock(&input->forks[philo->fork_l]);
			pthread_mutex_unlock(&input->forks[philo->fork_r]);
			eat++;
			pthread_mutex_lock(philo->eat_lock);
			philo->eating = false;
			pthread_mutex_unlock(philo->eat_lock);
			// sleep
			print_state(input, philo, is_sleeping);
			ft_sleep(input->tt_sleep);
			// think
			print_state(input, philo, is_thinking);
		}
		else
		{
			pthread_mutex_unlock(input->death_lock);
			pthread_mutex_unlock(&input->forks[philo->fork_l]);
			pthread_mutex_unlock(&input->forks[philo->fork_r]);
			break ;
		}
	}
	pthread_mutex_lock(input->running_lock);
	philo->running = false;
	pthread_mutex_unlock(input->running_lock);
	return (NULL);
}
