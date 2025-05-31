/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:21:14 by bduval            #+#    #+#             */
/*   Updated: 2025/05/31 13:51:21 by bduval           ###   ########.fr       */
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
# include <float.h>

			//mlx
int			set_mlx(t_all *mlx);
int			free_mlx(t_all *mlx);
int			set_mlx_events(t_all *mlx);
int			start_mlx_loop(t_all *all);
int			quit_hook(void *param);

			//parsing
int			parse_map(int ac, char **av, t_all *all);
int			split_set(char ***dest, const char *line, const char *set);
int			parse_amb_light(char **param, t_scene *scene, char *unique);
int			parse_light(char **param, t_scene *scene, char *unique);
int			parse_cam(char **param, t_scene *scene, char *unique);
int			parse_sphere(char **param, t_scene *scene);
int			parse_cylinder(char **param, t_scene *scene);
int			parse_plane(char **param, t_scene *scene);
int			ft_is_char(const char *str);
int			ft_is_double(const char *str);
int			ft_get_color(t_obj *obj, char **param);
int			ft_atoi_double(double *dest, char *str);
int			is_normalized(double n);
int			ft_objclear(t_obj **lst);
int			ft_objadd_back(t_obj **lst, t_obj *new);

			//ray
int			send_rays(t_all *all);
int			sphere_collision(t_obj *sphere, t_ray *ray);
t_vector	sphere_normal(t_obj *sphere, t_point point);
double		ft_norm(t_vector *v);
t_vector	v_substract(t_vector v1, t_vector v2);
t_vector	v_multiply(t_vector v1, t_vector v2);
t_vector	v_cross(t_vector v1, t_vector v2);
t_vector	v_scale(t_vector v, double scalar);
double		v_dot(t_vector v1, t_vector v2);
t_vector	v_add(t_vector v1, t_vector v2);
t_vector	v_unit(t_vector v1);
double		v_magnitude(t_vector v1);
t_color		c_scale(t_color c, double scale);

			//error
int			error(char *str);
int			print_error2(char *err1, char *err2, const char *f, int l);
int			print_error(char *err, const char *file, int line, const char *func);

			//utils
int			free_strs(char **strs);
int			free_scene(t_all *all);
int			free_everything(t_all *all);

			//debug
int			print_vector(char *s, t_vector v);
int			print_ray(t_ray r);
int			print_scene(t_all *all);
int			print_color(char *s, t_color c);

#endif
