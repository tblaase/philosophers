/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:59:25 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/02 20:13:36 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

void	*routine(void *arg)
{
	t_input	*input;
	t_philo	*philo;
	long	start_time;
	int		eat;

	philo = (t_philo *)arg;
	input = get_input();
	start_time = get_time();
	while ((input->n_must_eat[0] == true && eat < input->n_must_eat[1])
		|| eat < INT_MAX)
	{
		pthread_mutex_lock(philo->fork_l);
		print_state(input, philo, grabbed_fork, get_time());
		pthread_mutex_lock(philo->fork_r);
		print_state(input, philo, grabbed_fork, get_time());
		if ((start_time - get_time()) >= input->tt_die)
			death_routine(philo);
		else
		{
			// eat
			print_state(input, philo, is_eating, get_time());
			ft_sleep(input->tt_eat);
			eat++;
			// unlock
			pthread_mutex_unlock(philo->fork_l);
			pthread_mutex_unlock(philo->fork_r);
			start_time = get_time();
			// sleep
			print_state(input, philo, is_sleeping, get_time());
			ft_sleep(input->tt_sleep);
			print_state(input, philo, is_thinking, get_time());
		}
	}
	return (EXIT_SUCCESS);
}
