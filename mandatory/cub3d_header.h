/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:37:54 by maglagal          #+#    #+#             */
/*   Updated: 2024/09/28 15:37:55 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include "../MLX42/include/MLX42/MLX42.h"

#define HEIGHT 1000
#define WIDTH 1800
#define FOV_ANGLE 60
#define TILE_PX 640

typedef struct s_point {
	float x;
	float y;
}			t_point;

typedef struct s_ray {
	float		x;
	float		y;
	float		angle;
	float		h_xintersept;
	float		h_yintersept;
	float		v_xintersept;
	float		v_yintersept;
	float		xstep;
	float		ystep;
	int			p_isFacingDown;
	int			p_isFacingUp;
	int			p_isFacingRight;
	int			p_isFacingLeft;
	float		distance_to_wall;
	int			horizontal_wall;
	int			vertical_wall;
	mlx_texture_t	*texture;
	mlx_image_t	*map_img;
}					t_ray;

typedef struct player_struct {
	mlx_t		*mlx;
	char		**map;
	int			map_height;
	int			map_width;
	mlx_image_t *map_img;
	char		w_key;
	char		s_key;
	char		d_key;
	char		a_key;
	float		p_fov_angle;
	float		player_x;
	float		player_y;
	float		turnLeft;
	float		turnRight;
	float		playerAngle;
	float		moveSpeed;
	float		rotationSpeed;
	xpm_t			*no_t;
	xpm_t			*so_t;
	xpm_t			*we_t;
	xpm_t			*ea_t;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	int				floor_color;
	int				ceiling_color;
	t_ray			*rays;
}					t_player;

char			*get_next_line(int fd); 
size_t			ft_strlen(const char *s);
float			degrees2rad(float degrees);
float			find_closest_horizontal_yintersec(t_player *player);
float			find_closest_horizontal_xintersec(t_player *player, float yintersept, float ray_angle);
float			find_closest_vertical_yintersec(t_player *player, float xintersept, float ray_angle);
float			find_closest_vertical_xintersec(t_player *player);
float			calculate_xstep(float ray_angle);
float			calculate_ystep(float ray_angle);
float			calculate_smallest_distance(t_player *player, t_ray *ray, t_point *wall1, t_point *wall2);
void			cast_rays(t_player *player);
void			move_player(mlx_key_data_t keydata, void *player);
void			render(void *v_player); 
void			draw_rectangle(mlx_image_t *img, float x, float y, int color, float p);
t_point			calculating_horizontal_intersections(t_player *player, t_ray *ray);
t_point			calculating_vertical_intersections(t_player *player, t_ray *ray);
t_point			finding_wall_horizontal(t_player *player, t_ray *ray, float xstep, float ystep);
t_point			finding_wall_vertical(t_player *player, t_ray *ray, float xstep, float ystep);
void			draw_walls(t_player *player, int x, double y, int w, int p, int textOffsetX, mlx_texture_t *texture);
void			draw_ceiling(mlx_image_t *img, int x, int y, int color, int w);
void			draw_floor(mlx_image_t *img, int x, int y, int color, int w);
char			**store_2d_array(t_player *player, char *map_path, int *map_height, int *map_width);
void			*free_memory(char **map, int r);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				get_textures(t_player *player, char *map_path);
mlx_texture_t 	*get_texture(t_player *player, int is_vert, double x, double y);
char			**ft_split(char const *s, char c);
void			free_2d_array(char **array);
int				ft_atoi(const char *str);
int 			get_rgba(int r, int g, int b, int a);
void			print_err(char *line);
int				translate_rgb(char **sep_str, int *color);
int				count_comma(char *line);
int				count_2d_len(char **sep_str);
int				set_color(int *color, char *line, int *flag);
int				get_textures(t_player *player, char *map_path);
char			*ft_strjoin(char const *s1, char const *s2);
int				check_map_valid(char **map, t_player *player);
mlx_texture_t 	*resize_texture(mlx_texture_t *texture, int new_width, int new_height);
int 			is_wall(t_player *player, int x, int y);
void			initialize_player_struct(t_player *player, char *map_path, int *map_width, int *map_height);
void			initialize_rays_struct(t_player *player, t_ray *rays);
void			free_2d_arr(char **map);
void			save_player_coordinates(t_player *player);
float			calculate_correct_wall_distance(t_player *player, int i);
int				calculate_offsetx_walls(t_player *player, int i);
void			key_press(t_player *player, mlx_key_data_t keydata);
void			key_release(t_player *player, mlx_key_data_t keydata);
void			destroy_textures(t_player *player);