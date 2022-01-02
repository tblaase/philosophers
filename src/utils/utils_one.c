/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:58:34 by tblaase           #+#    #+#             */
/*   Updated: 2022/01/02 19:35:31 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inlcudes/philo.h"

/**
 * @brief  recreation of systems atol function
 * @note   has no error handling, if no long long found 0 is returned
 * @param  *str: the string to convert
 * @retval the long long converted from the input
 */
long long	ft_atol(char *str)
{
	int			c;
	int			i;
	long long	x;

	i = 0;
	c = 1;
	x = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			c = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		x = x * 10 + (str[i] - 48);
		i++;
	}
	return (x * c);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*buf;

	buf = s;
	while (n > 0)
	{
		*buf = c;
		buf++;
		n--;
	}
	return (s);
}

/**
 * @brief  recreation of the systems calloc
 * @note
 * @param  nelem: number of elements
 * @param  elsize: the size of each element
 * @retval the pointer to the allocated memory or NULL if allocation failed
 */
void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*ptr;

	ptr = malloc(nelem * elsize);
	if (!ptr)
		return (NULL);
	return (ft_memset(ptr, 0, nelem * elsize));
}

/**
 * @brief  gets the time in ms
 * @note   uses gettimeofday
 * @retval timeofday in ms
 */
long	get_time(void)
{
	long			time_ms;
	struct timeval	te;

	gettimeofday(&te, NULL);
	time_ms = (te.tv_sec * 1000);
	time_ms += (te.tv_usec / 1000);
	return (time_ms);
}

/**
 * @brief  will print the state of a philosopher
 * @note   this is mutex protected so only one message gets printed at a time
 * @param  *input: the input struct
 * @param  *philo: the philosopher who's state should be printed
 * @param  state: the state that should be printed
 * @param  time: the timestamp
 * @retval None
 */
void	print_state(t_input *input, t_philo *philo, int state, long time)
{
	if (input->death == false)
	{
		pthread_mutex_lock(&input->print_lock);
		printf("%ld	%d %s", time, philo->philo_n, input->state[state]);
		pthread_mutex_unlock(&input->print_lock);
	}
}
