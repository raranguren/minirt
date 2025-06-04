/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:21:14 by bduval            #+#    #+#             */
/*   Updated: 2025/06/04 09:25:10 by bduval           ###   ########.fr       */
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
# include <errno.h>

			//mlx
int			set_mlx(t_all *mlx);
int			free_mlx(t_all *mlx);
int			set_mlx_events(t_all *mlx);
int			start_mlx_loop(t_all *all);
int			quit_hook(void *param);

			//ray
int			send_rays(t_all *all);
int			sphere_collision(t_obj *sphere, t_ray *ray);
t_vector	sphere_normal(t_obj *sphere, t_point point);
float		ft_norm(t_vector *v);
t_vector	v_substract(t_vector v1, t_vector v2);
t_vector	v_multiply(t_vector v1, t_vector v2);
t_vector	v_cross(t_vector v1, t_vector v2);
t_vector	v_scale(t_vector v, float scalar);
float		v_dot(t_vector v1, t_vector v2);
t_vector	v_add(t_vector v1, t_vector v2);
t_vector	v_unit(t_vector v1);
float		v_magnitude(t_vector v1);
int			get_impact(t_scene *scene, t_ray *ray);
int			compute_light(t_scene *scene, t_ray *ray);
t_color		c_multiply(t_color a, t_color b);
t_color		c_normalize(t_color a);
t_color		c_set(float scale);
t_color		c_scale(t_color c, float scale);
t_color		c_add(t_color c, t_color c2);

			//parsing
int			parse_map(int ac, char **av, t_all *all);
int			split_set(char ***dest, const char *line, const char *set);
int			parse_amb_light(char **param, t_scene *scene);
int			parse_light(char **param, t_scene *scene);
int			parse_cam(char **param, t_scene *scene);
int			parse_sphere(char **param, t_scene *scene);
int			parse_cylinder(char **param, t_scene *scene);
int			parse_plane(char **param, t_scene *scene);
int			ft_is_char(const char *str);
int			ft_is_double(const char *str);
int			ft_get_color(t_obj *obj, char **param);
int			ft_atoi_double(float *dest, char *str);
int			is_normalized(float n);
int			ft_objclear(t_obj **lst);
int			ft_objadd_back(t_obj **lst, t_obj *new);
int			unique(char obj_type, int parse_err);
int			normalize(t_vector *vector);
int			init_scene(t_scene *scene);

			//edit
int			edit_init(t_all *all);
int			edit(t_all *all, int keycode);
int			rotate(t_vector *v, float hztl_angle, float vertical_angle);
int			ui_update(t_all *all);

			//error
int			error(char *str);
int			print_error2(char *err1, char *err2, const char *f, int l);
int			print_error(char *err, const char *fle, int lne, const char *func);
int			error3(char *a, char *b, char *c);

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
