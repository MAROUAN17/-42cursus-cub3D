#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include "MLX42/include/MLX42/MLX42.h"

#define HEIGHT 1000
#define WIDTH 1800
#define FOV_ANGLE 60
#define UNIT 32.0
#define TILE_PX (HEIGHT / (int)UNIT)
#define MINIMAP_FACTOR (float)(((float)UNIT / (float)HEIGHT) + 0.2)

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
	int			p_isFacingDown;
	int			p_isFacingUp;
	int			p_isFacingRight;
	int			p_isFacingLeft;
	float		distance_to_wall;
	int			horizontal_wall;
	int			vertical_wall;
	mlx_image_t	*map_img;
}					t_ray;

typedef struct player_struct {
	mlx_t		*mlx;
	char		**map;
	int			map_height;
	int			map_width;
	mlx_image_t *map_img;
	mlx_image_t *white_img;
	mlx_image_t *player_img;
	mlx_image_t *view_img;
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
	mlx_texture_t	*walls_texture;
	mlx_texture_t	*door_texture;
	t_ray		*rays;
}					t_player;

void	*ft_memset(void *b, int c, size_t len);
char	*get_next_line(int fd); 
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
float	degrees2rad(float degrees);
float	find_closest_horizontal_yintersec(t_player *player);
float	find_closest_horizontal_xintersec(t_player *player, float yintersept, float ray_angle);
float	find_closest_vertical_yintersec(t_player *player, float xintersept, float ray_angle);
float	find_closest_vertical_xintersec(t_player *player);
float	calculate_xstep(float ray_angle);
float	calculate_ystep(float ray_angle);
float	calculate_smallest_distance(t_player *player, t_ray *ray, t_point *wall1, t_point *wall2);
void	cast_rays(t_player *player);
void	move_player(mlx_key_data_t keydata, void *player);
void	render_empty(void *player);
void	render_draw_line(void *v_player); 
void	render_2dmap(t_player *player, char **map);
void	render(void *v_player); 
void	draw_rectangle(mlx_image_t *img, float x, float y, int color, float p);
t_point	calculating_horizontal_intersections(t_player *player, t_ray *ray);
t_point	calculating_vertical_intersections(t_player *player, t_ray *ray);
t_point	finding_wall_horizontal(t_player *player, t_ray *ray, float xstep, float ystep);
t_point	finding_wall_vertical(t_player *player, t_ray *ray, float xstep, float ystep);
void	draw_walls(t_player *player, int x, int y);
void 	render_minimap(t_player *player);
void	draw_rectangle_3d(t_player *player, int x, float y, int w, int p, int textOffsetX);
void	draw_ceiling(mlx_image_t *img, int x, int y, int color, int w);
void	draw_floor(mlx_image_t *img, int x, int y, int color, int w);