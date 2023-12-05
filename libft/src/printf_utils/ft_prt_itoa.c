/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:37:20 by orezek            #+#    #+#             */
/*   Updated: 2023/11/22 10:33:21 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nlength(long long n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		counter++;
		n /= 10;
	}
	return (counter);
}

static char	*ft_nconvert(long long n, char *ptr, int is_negative, int length)
{
	char	*nptr;
	int		len;

	len = length;
	nptr = ptr;
	if (is_negative)
		*ptr++ = '-';
	while (n != 0)
	{
		*(ptr + length - 1) = ((n % 10) + 48);
		n /= 10;
		length--;
	}
	*(nptr + len + is_negative) = '\0';
	return (nptr);
}

char	*ft_prt_itoa(int n)
{
	long long	number;
	int			is_negative;
	char		*ptr;

	is_negative = 0;
	number = (long long)n;
	if (number < 0)
	{
		number *= -1;
		is_negative = 1;
	}
	if (is_negative)
		ptr = malloc((ft_nlength(number) + 2) * sizeof(char));
	else
		ptr = malloc((ft_nlength(number) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (number == 0)
	{
		*(ptr++) = '0';
		*(ptr) = '\0';
		return (ptr - 1);
	}
	return (ft_nconvert(number, ptr, is_negative, ft_nlength(number)));
}
