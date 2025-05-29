/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:21:14 by bduval            #+#    #+#             */
/*   Updated: 2025/05/29 19:00:41 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include "mlx_int.h"
# include "defines.h"
# include "typedefs.h"

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <errno.h>

//mlx
int	set_mlx(t_all *mlx);
int	free_mlx(t_all *mlx);
int	set_mlx_events(t_all *mlx);
int	start_mlx_loop(t_all *all);

//parsing
int	parse_map(int ac, char **av, t_all *all);
int	split_set(char ***dest, const char *line, const char *set);
int	parse_amb_light(char **param, t_scene *scene);
int	parse_light(char **param, t_scene *scene);
int	parse_cam(char **param, t_scene *scene);
int	parse_sphere(char **param, t_scene *scene);
int	parse_cylinder(char **param, t_scene *scene);
int	parse_plane(char **param, t_scene *scene);
int	ft_is_char(const char *str);
int	ft_is_double(const char *str);
int	ft_get_color(int *dest, char **param);
int	ft_atoi_double(double *dest, char *str);
int	is_normalized(double n);
int	ft_objclear(t_obj **lst);
int	ft_objadd_back(t_obj **lst, t_obj *new);
int	unique(char obj_type, int parse_err);
int	normalize(t_vector *vector);

//edit
int	edit_init(t_all *all);
int edit(t_all *all, int keycode);
int rotate(t_vector *vector, double horizontal_angle, double vertical_angle);

//error
int	error(char *str);
int	print_error2(char *err1, char *err2, const char *f, int l);
int	print_error(char *err, const char *file, int line, const char *func);
int error3(char *a, char *b, char *c);

//utils
int	free_strs(char **strs);
int	free_scene(t_all *all);
int	free_everything(t_all *all);

#endif
