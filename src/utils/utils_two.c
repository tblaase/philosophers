/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:09:48 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/14 15:34:28 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inlcudes/philo.h"

void	ft_sleep(long long ms)
{
	long	start_time;

	start_time = get_time();
	while (start_time + ms > get_time())
		usleep(100);
}

int	print_error(void)
{
	printf("Wrong input!\nPlease use like: \
'./philo\033[0;31m a\033[0;32m b\033[0;33m c\033[0;34m d\033[0;35m e\033[0;37m'\
\n\033[0;31ma = [number_of_philosophers]\n\033[0;32mb = [time_to_die]\
\n\033[0;33mc = [time_to_eat]\n\033[0;34md = [time_to_sleep]\
\n\033[0;35me = [number_of_times_each_philosoppher_must_eat]\
\n\033[0;37mEvery value but \033[0;35me\033[0;37m is mandatory.\n");
	return (EXIT_FAILURE);
}

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
		pthread_mutex_lock(input->running_lock);
		if (philos[i]->running == false)
			finished++;
		pthread_mutex_unlock(input->running_lock);
		i++;
	}
	if (finished == input->n_philos)
		return (true);
	return (false);
}
