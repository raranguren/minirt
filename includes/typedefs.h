/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:21:09 by bduval            #+#    #+#             */
/*   Updated: 2025/06/04 12:30:00 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

typedef struct s_quadratic
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	solution_1;
	float	solution_2;

}	t_quadratic;

typedef struct s_coord
{
	float	x;
	float	y;
	float	z;
}	t_coord;

typedef struct s_col
{
	float	r;
	float	g;
	float	b;
}	t_col;

typedef struct s_color
{
	float	a;
	float	r;
	float	g;
	float	b;
}	t_color;

typedef t_coord			t_vector;
typedef t_coord			t_point;

typedef struct s_obj	t_obj;
typedef t_obj			t_light;
typedef t_obj			t_cam;
//typedef t_point			(*t_collision_fn)(t_obj*, t_ray*);
//typedef t_vector		(*t_normal_fn)(t_obj*, t_ray*);

typedef struct s_ray
{
	t_point		start;
	t_vector	direction;
	t_vector	bump;
	t_vector	normal;
	t_color		color;
	float		shortest_impact_dist;
	t_color		direct_light;
	t_color		specular_light;
	t_obj		*impact_object;
	int			from_cam;
}	t_ray;

typedef int				(*t_collision_fn)(t_obj *, t_ray *);
typedef t_vector		(*t_normal_fn)(t_obj *obj, t_point p);

typedef struct s_obj
{
	char			type;
	t_coord			pos;
	union
	{
		t_vector		orientation;
		t_vector		forward;
	};
	t_color			color;
	union
	{
		float		diameter;
		float		ratio;
	};
	union
	{
		float		height;
		float		radius;
		float		brightness;
		float		fov;
	};
	t_obj			*next;
	t_collision_fn	collision_fn;
	t_normal_fn		normal_fn;

	float			fov_scale;
	union
	{
		float			aspect_ratio;
		float			reflection;
	};
	t_vector		right;
	t_vector		up;
}	t_obj;

typedef struct s_scene
{
	t_obj		*obj;
	t_obj		*obj2;
	t_cam		*cam;
	t_light		*amb_light;
	t_light		*light;
	t_obj		*selected;
}	t_scene;

typedef struct s_image
{
	void	*id;
	char	*data;
	int		bits_per_pix;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_all
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_image	img;
	t_scene	scene;
}	t_all;

#endif
