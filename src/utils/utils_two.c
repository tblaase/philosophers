/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:09:48 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/17 20:15:02 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inlcudes/philo.h"

/**
 * @brief  sleeps the thread for ms milliseconds
 * @note   it is more accurate than sleeping one long time
 * @param  ms: time in milliseconds to sleep
 * @retval None
 */
void	ft_sleep(long long ms)
{
	long	start_time;

	start_time = get_time();
	while (start_time + ms > get_time())
		usleep(100);
}

/**
 * @brief  prints the how to use message
 * @note   while it may not look pretty, it works as i want it to work
 *		   and it is norminette compliant
 * @retval only exists to save some lines
 */
int	print_error(void)
{
	printf("Wrong input!\nPlease use like: '\
./philo\033[0;31m a\033[0;32m b\033[0;33m c\033[0;34m d\033[0;35m e\033[0;37m'\
\n\033[0;31ma = [number_of_philosophers]\n\033[0;32mb = [time_to_die]\
\n\033[0;33mc = [time_to_eat]\n\033[0;34md = [time_to_sleep]\
\n\033[0;35me = [number_of_times_each_philosoppher_must_eat]\
\n\033[0;37mEvery value but \033[0;35me\033[0;37m is mandatory.\n");
	return (EXIT_FAILURE);
}

/**
 * @brief  will check if every philosopher is finished wih his task to eat
 * @note
 * @retval true or false
 */
bool	every_philo_finished(void)
{
	t_philo	**philos;
	t_input	*input;
	int		finished;
	int		i;

	finished = 0;
	i = 0;
	philos = get_philos();
	input = get_input();
	while (philos[i] != NULL)
	{
		pthread_mutex_lock(philos[i]->running_lock);
		if (philos[i]->running == false)
			finished++;
		pthread_mutex_unlock(philos[i]->running_lock);
		i++;
	}
	if (finished == input->n_philos)
		return (true);
	return (false);
}

/**
 * @brief  checks if c is an ascii digit
 * @note   altered version of libft's ft_isdigit
 * @param  c: value of the ascii to check
 * @retval true if c is a digit or '+' or '-', else false
 */
int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57) || c == '-' || c == '+')
		return (true);
	else
		return (false);
}

/**
 * @brief  is a part of the set_input function
 * @note   only exists because of norminette
 * @retval will pass or fail
 */
int	input_help(void)
{
	t_input	*input;

	input = get_input();
	input->state[is_eating] = "is eating\n";
	input->state[grabbed_fork] = "has taken a fork\n";
	input->state[is_sleeping] = "is sleeping\n";
	input->state[is_thinking] = "is thinking\n";
	input->state[is_dead] = "died\n";
	input->state[6] = NULL;
	input->print_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	input->death_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	input->wait_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	if (input->death_lock == NULL || input->wait_lock == NULL
		|| input->print_lock == NULL)
	{
		free_input();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
