/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_header_b.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:41:39 by maglagal          #+#    #+#             */
/*   Updated: 2024/10/06 17:33:46 by maglagal         ###   ########.fr       */
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
#define TILE_PX 64

typedef struct s_point
{
	float	x;
	float	y;
}			t_point;

typedef struct s_sprite
{
	float			x;
	float			y;
	int				visible;
	float			angle;
	float			distance;
	int				start_a;
	int				open_door;
	int				collected;
	float			psprite_width;
	float			psprite_height;
	float			sprite_xstart;
	float			sprite_xend;
	mlx_texture_t	*texture;
	mlx_texture_t	**an_textures;
}				t_sprite;

typedef struct s_ray
{
	float			x;
	float			y;
	float			d_x;
	float			d_y;
	float			angle;
	float			*d_h_xintersept;
	float			*d_h_yintersept;
	float			*d_v_xintersept;
	float			*d_v_yintersept;
	float			h_xintersept;
	float			h_yintersept;
	float			v_xintersept;
	float			v_yintersept;
	int				p_is_facing_down;
	int				p_is_facing_up;
	int				p_is_facing_right;
	int				p_is_facing_left;
	float			distance_to_wall;
	float			distance_to_door;
	int				horizontal_wall;
	int				vertical_wall;
	float			wall_height;
	mlx_texture_t	*texture;
	mlx_image_t		*map_img;
}					t_ray;

typedef struct player_struct
{
	mlx_t			*mlx;
	char			**map;
	int				map_height;
	int				map_width;
	int				map_x_offset;
	int				map_y_offset;
	mlx_image_t		*map_img;
	mlx_image_t		*white_img;
	mlx_image_t		*player_img;
	mlx_image_t		*view_img;
	char			w_key;
	char			s_key;
	char			d_key;
	char			a_key;
	float			p_fov_angle;
	float			player_x;
	float			player_y;
	float			turn_left;
	float			turn_right;
	float			player_angle;
	float			move_speed;
	float			rotation_speed;
	xpm_t			*no_t;
	xpm_t			*so_t;
	xpm_t			*we_t;
	xpm_t			*ea_t;
	mlx_texture_t	*walls_texture;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	int				floor_color;
	int				ceiling_color;
	t_ray			*rays;
	t_sprite		*sprite;
	t_sprite		*door_sprite;
	int				nbr_collected;
	mlx_texture_t	*door_textures[4];
	int				door_index;
	int				doors_count;
	int				open_door;
	int				start_door_a;
	int				total_sprites;
	int				color;
	float			minimap_factor;
}					t_player;

char			*get_next_line(int fd);
size_t			ft_strlen(const char *s);
float			degrees2rad(float degrees);
float			find_closest_horizontal_yintersec(t_player *player);
float			find_closest_horizontal_xintersec(t_player *player,
					float yintersept, float ray_angle);
float			find_closest_vertical_yintersec(t_player *player,
					float xintersept, float ray_angle);
float			find_closest_vertical_xintersec(t_player *player);
float			calculate_xstep(float ray_angle);
float			calculate_ystep(float ray_angle);
float			calculate_smallest_distance(t_player *player,
					t_ray *ray, t_point *wall1, t_point *wall2);
void			cast_rays(t_player *player);
void			move_player(t_player *player);
void			render(void *v_player);
void			draw_rectangle(t_player *player, float x,
					float y, float p);
void			draw_rectangle_3d(t_player *player, int x,
					float y, int textOffsetX);
t_point			calculating_horizontal_intersections(t_player *player,
					t_ray *ray);
t_point			calculating_vertical_intersections(t_player *player,
					t_ray *ray);
t_point			finding_wall_horizontal(t_player *player, t_ray *ray,
					float xstep, float ystep);
t_point			finding_wall_vertical(t_player *player, t_ray *ray,
					float xstep, float ystep);
void			draw_walls(t_player *player, int x, int y);
void			render_minimap(t_player *player);
void			draw_ceiling(mlx_image_t *img, int x,
					int y, int color);
void			draw_floor(mlx_image_t *img, int x,
					int y, int color);
char			**store_2d_array(t_player *player,
					char *map_path, int *map_height, int *map_width);
void			*free_memory(char **map, int r);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				get_textures(t_player *player, char *map_path);
mlx_texture_t	*get_texture(t_player *player, int is_vert, float x, float y);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
int				get_rgba(int r, int g, int b, int a);
void			print_err(char *line);
int				translate_rgb(char **sep_str, int *color);
int				count_comma(char *line);
int				count_2d_len(char **sep_str);
int				set_color(int *color, char *line, int *flag);
int				get_textures(t_player *player, char *map_path);
char			*ft_strjoin(char const *s1, char const *s2);
int				check_map_valid(char **map, t_player *player);
void			visible_sprite_c(t_player *player, t_sprite *sprite, int index);
void			calculate_distance_coins(t_player *player);
void			calculate_sprite_projection_and_render(t_player *player,
					int index);
void			render_sprites(t_player *player, int texIndex);
void			check_change_position(t_player *player, float angle);
void			rotate_player(t_player *player, float rotationAngle);
float			normalize_ray_angle(float ray_angle);
int				check_corner(t_player *player, float new_x);
void			mouse_rotation(t_player *player);
mlx_texture_t	*resize_texture(mlx_texture_t *texture,
					int new_width, int new_height);
void			free_2d_arr(char **map);
void			initialize_player_struct(t_player *player,
					char *map_path, int *map_width, int *map_height);
int				initialize_rays_struct(t_player *player);
int				initialize_sprites_struct(t_player *player,
					mlx_texture_t **textures);
void			change_sprite_index(t_player *player, int i, int texIndex);
void			render_sprites_minimap(t_player *player, int sprIndex);
void			calculating_sprite_x(t_player *player,
					t_sprite *sprite, float d_projection, float psprite_width);
void			free_allocated_memory(t_player *player,
					mlx_texture_t **textures, mlx_texture_t **d_textures);
int				calculate_number_sprites(t_player *player);
int				is_open_door(t_player *player, int check_x, int check_y);
void			check_door_intersections(t_player *player);
void			draw_door(t_player *player, float x, float y, int i);
float			get_smallest_door_distance(t_player *player, t_ray *ray, int j);
float			calculate_correct_wall_distance(t_player *player, int i);
float			calculate_correct_door_distance(t_player *player, int i);
float			calculate_door_height(t_player *player, int i);
float			calculate_wall_height(t_player *player, int i);
double			calculate_distance_door(t_player *player,
					t_sprite *sprite, int index);
void			save_door_cord(t_player *player, int x, int y, int *d_index);
void			draw_map_background(t_player *player);
void			draw_map_elements(t_player *player, int x, int y);
int				initialize_animation_textures(mlx_texture_t **c_textures,
					mlx_texture_t **d_textures);
int				initialize_door_sprites(t_player *player,
					mlx_texture_t **textures);
int				initialize_all(t_player *player, char *map_path,
					mlx_texture_t **c_textures, mlx_texture_t **d_textures);
void			move_keys_handler(mlx_key_data_t keydata, void *v_player);
void			movement_key_pressing(mlx_key_data_t keydata, t_player *player);
void			render_coins(t_player *player, int texIndex);
void			handle_multi_d_intersects(t_player *player, int i, int j);
void			visible_sprite_d(t_player *player, t_sprite *sprite, int index);
int				check_corner2(t_player *player, float new_x, float new_y);
void			render_one_sprite2(t_player *player, t_sprite *sprite,
					int ystart, int yend);
int				ft_isdigit(int c);
int				compare_to_upper_line(char *line, char *top_line);
char			**fill_map(int fd, int *map_height, int *map_width);
int				fill_gaps(char **line, int width);
int				is_invalid_tex(t_player *player);
float			calculate_correct_distance(t_player *player, t_ray *ray,
					t_point *wall1, t_point *wall2);
void			cast_rays_draw(t_player *player);
void			handle_door(t_player *player);
void			handle_door_intersect(t_player *player, int i);
t_point			h_set_interse_wall(t_ray *ray, int *index);
void			h_set_interse_door(t_ray *ray, int *index);
t_point			v_set_interse_wall(t_ray *ray, int *index);
void			v_set_interse_door(t_ray *ray, int *index);
void			count_xcheck_ycheck(t_ray *ray,
					float *p_xcheck, float *p_ycheck);
void			h_initialize_inters_doors(t_player *player, t_ray *ray);
void			v_initialize_inters_doors(t_player *player, t_ray *ray);
int				initialize_door_sprites(t_player *player,
					mlx_texture_t **textures);
int				initialize_rays_struct(t_player *player);
int				initialize_sprites_struct(t_player *player,
					mlx_texture_t **textures);
void			free_old_rays(t_ray *rays, int i);
int				alloc_d_rays(t_player *player, t_ray *rays, int i);
void			movement_key_pressing(mlx_key_data_t keydata, t_player *player);
int				set_texture(mlx_texture_t **texture, xpm_t **xpm, char *line);
int				get_file_type(char *line);
int				calculate_pixel_index(t_sprite *sprite, int ystart,
					int textOffsetX);
void			calculating_sprite_width_height(t_sprite *sprite,
					float d_projection, int *ystart, int *yend);
