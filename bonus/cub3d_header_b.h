#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include "../MLX42/include/MLX42/MLX42.h"
// (HEIGHT / (int)UNIT) (past formula)

#define HEIGHT 1000
#define WIDTH 1800
#define FOV_ANGLE 60
#define TILE_PX 64
#define MINIMAP_FACTOR ((float)(HEIGHT / 100) / TILE_PX)

typedef struct s_point {
	float x;
	float y;
}			t_point;

typedef struct s_sprite {
	float	x;
	float	y;
	int		visible;
	float	angle;
	float	distance;
	int	    start_a;
	int	    open_door;
	mlx_texture_t *texture;
	mlx_texture_t **an_textures;
	int		collected;
	float	pSpriteWidth;
	float	pSpriteHeight;
	float	spriteXstart;
	float	spriteXend;
}				t_sprite;

typedef struct s_ray {
	float		x;
	float		y;
	float		d_x;
	float		d_y;
	float		angle;
	float		*d_h_xintersept;
	float		*d_h_yintersept;
	float		*d_v_xintersept;
	float		*d_v_yintersept;
	float		h_xintersept;
	float		h_yintersept;
	float		v_xintersept;
	float		v_yintersept;
	int			p_isFacingDown;
	int			p_isFacingUp;
	int			p_isFacingRight;
	int			p_isFacingLeft;
	float		distance_to_wall;
	float		distance_to_door;
	int			horizontal_wall;
	int			vertical_wall;
	float		wall_height;
	mlx_texture_t	*texture;
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
	mlx_texture_t	*curr_door_tex;
	int				doors_count;
	int		        open_door;
	int		        start_door_a;
	int			total_sprites;
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
void	render(void *v_player); 
void	draw_rectangle(mlx_image_t *img, float x, float y, int color, float p);
t_point	calculating_horizontal_intersections(t_player *player, t_ray *ray);
t_point	calculating_vertical_intersections(t_player *player, t_ray *ray);
t_point	finding_wall_horizontal(t_player *player, t_ray *ray, float xstep, float ystep);
t_point	finding_wall_vertical(t_player *player, t_ray *ray, float xstep, float ystep);
void	draw_walls(t_player *player, int x, int y);
void 	render_minimap(t_player *player);
void	draw_rectangle_3d(t_player *player, int x, float y, int textOffsetX);
void	draw_ceiling(mlx_image_t *img, int x, int y, int color, int w);
void	draw_floor(mlx_image_t *img, int x, int y, int color, int w);
char	**store_2d_array(t_player *player, char *map_path, int *map_height, int *map_width);
void	*free_memory(char **map, int r);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		get_textures(t_player *player, char *map_path);
mlx_texture_t *get_texture(t_player *player, int is_vert, float x, float y);
char	**ft_split(char const *s, char c);
void	free_2d_array(char **array);
int		ft_atoi(const char *str);
int 	get_rgba(int r, int g, int b, int a);
void	print_err(char *line); 
int		translate_rgb(char **sep_str, int *color);
int		count_comma(char *line);
int		count_2d_len(char **sep_str);
int		set_color(int *color, char *line, int *flag);
int		get_textures(t_player *player, char *map_path);
char	*ft_strjoin(char const *s1, char const *s2);
int		check_map_valid(char **map, t_player *player);
void	visibleSprite(t_player *player, t_sprite *sprite, int index);
double	calculate_distance_sprites(t_player *player, t_sprite *sprite, int index);
void	calculate_sprite_projection_and_render(t_player *player, int index);
void	render_sprites(t_player *player, int texIndex);
void	check_change_position(t_player *player, float angle);
void	move_player(mlx_key_data_t keydata, void *v_player);
void	rotate_player(t_player *player, float rotationAngle);
float	normalize_rayAngle(float ray_angle);
int		check_corner(t_player *player, float new_x, float new_y);
void	mouse_rotation(t_player *player);
mlx_texture_t 	*resize_texture(mlx_texture_t *texture, int new_width, int new_height);
void	free_2d_arr(char **map);
void 	initialize_player_struct(t_player *player, char *map_path, int *map_width, int *map_height);
void	initialize_rays_struct(t_player *player, t_ray *rays);
void	initialize_sprites_struct(t_player *player, t_sprite *sprite, mlx_texture_t **textures);
int 	is_door(t_player *player, int x, int y);
void 	render_door(t_player *player);
void	change_sprite_index(t_player *player, int texIndex);
void	render_sprites_minimap(t_player *player, int sprIndex);
void	calculating_sprite_x(t_player *player, t_sprite *sprite, float d_projection, float pSpriteWidth);
void	free_allocated_memory(t_player *player, mlx_texture_t **textures, mlx_texture_t **d_textures);
int		calculate_number_sprites(t_player *player);
int		is_open_door(t_player *player, int check_x, int check_y);
void	check_door_intersections(t_player *player, int i);
void	draw_door(t_player *player, float x, float y, int i);
float	get_smallest_door_distance(t_player *player, t_ray *ray, int j);
float	calculate_correct_wall_distance(t_player *player, int i);
float 	calculate_correct_door_distance(t_player *player, int i);
float	calculate_door_height(t_player *player, int i);
float	calculate_wall_height(t_player *player, int i);

// void	draw_door(t_player *player, float x, float y, t_ray *ray, int i);
