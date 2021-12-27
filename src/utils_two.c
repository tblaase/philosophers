/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:09:48 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/27 16:18:24 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/philo.h"

long	get_time(void)
{
	long			time_ms;
	struct timeval	*te;

	gettimeofday(&te, NULL);
	time_ms = (te->tv_sec * 1000);
	time_ms += (te->tv_usec / 1000);
	return (time_ms);
}
