/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:21:14 by bduval            #+#    #+#             */
/*   Updated: 2025/06/15 16:41:17 by rarangur         ###   ########.fr       */
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
t_vector	sphere_normal(t_obj *sphere, t_ray *ray);
int			plane_collision(t_obj *plane, t_ray *ray);
float		plane_colision_dist(t_obj *plane, t_ray *ray);
t_vector	plane_normal(t_obj *obj, t_ray *ray);
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
int			solve_quadratic(t_quadratic *quad);
int			bind_ray_if_nearest(t_quadratic *res, t_ray *ray, t_obj *obj);
int			cylinder_collision(t_obj *cyl, t_ray *ray);
t_vector	cylinder_normal(t_obj *obj, t_ray *ray);
int			get_positiv_min(float *f1, float *f2);
float		caps_collision(t_obj *caps, t_ray *ray);
int 		is_within_cap(t_obj *caps, t_ray *ray, float dist);
int			cone_collision(t_obj *cone, t_ray *ray);
t_vector	cone_normal(t_obj *obj, t_ray *ray);

			//parsing
int			parse_map(int ac, char **av, t_all *all);
int			split_set(char ***dest, const char *line, const char *set);
int			parse_amb_light(char **param, t_scene *scene);
int			parse_light(char **param, t_scene *scene);
int			parse_cam(char **param, t_scene *scene);
int			parse_sphere(char **param, t_scene *scene);
int			parse_cylinder(char **param, t_scene *scene);
int			parse_cone(char **param, t_scene *scene);
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
int			init_scene(t_all *all);
int			init_scene_bonus(t_all *all);
int			ft_get_map_name(char **dest, char *param);

			//edit
int			edit_init(t_all *all);
int			edit(t_all *all, int keycode);
int			edit_select_next(t_all *all);
int			edit_select_previous(t_all *all);
int			edit_select(t_all *all, t_obj *target);
int			rotate(t_vector *v, float hztl_angle, float vertical_angle);
int			ui_update(t_all *all);
int			gui_update(t_all *all);
int			gui_numbers(t_all *all, t_obj *obj);
int			gui_labels(t_all *all, t_obj *obj);
int			save_scene(t_all *all, char *filename);
void		put_obj_fd(t_obj *obj, int fd);
void		ft_putfloat_fd(float n, int fd);

			//error
int			error(char *str);
int			print_error2(char *err1, char *err2, const char *f, int l);
int			print_error(char *err, const char *fle, int lne, const char *func);
int			error3(char *a, char *b, char *c);

			//utils
int			free_strs(char **strs);
int			free_scene(t_all *all);
int			free_everything(t_all *all);
t_obj		*find_next_obj_in_scene(t_scene *scene, t_obj *current);

			//debug
int			print_vector(char *s, t_vector v);
int			print_ray(t_ray r);
int			print_scene(t_all *all);
int			print_color(char *s, t_color c);

#endif
