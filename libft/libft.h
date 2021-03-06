/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 17:09:16 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/16 16:45:57 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"

size_t  ft_strlen(char *s);
int		ft_strequ(char *s1, char *s2);
void	ft_ppdel(char ***sv);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, void *src, size_t n);
char	*ft_itoa(size_t v, size_t b);
char	*ft_strcat(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strcpy(char *dst, char *src);
char	*ft_strncpy(char *dst, char *src, size_t len);
char	*ft_strdup(char *s1);
char	*ft_strnew(size_t size);
char	**ft_strsplit(char *s, char c);


#endif