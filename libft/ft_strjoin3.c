/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:48:07 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/05/18 16:48:55 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char *tmp;
	char *res;

    tmp = ft_strjoin(s1, s2);
    res = ft_strjoin(tmp, s3);
	free(tmp);
	return res;
}