#include "raycast.h"

char map[mapY][mapX] = {
    {'1', '1', '1', '1', '1','1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '1','1', '0', '1', '1', '1'},
    {'1', '0', '0', '0', '0','0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0','0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '1','0', '0', '1', '0', '1'},
    {'1', '0', '0', '1', '0','0', '0', '1', '0', '1'},
    {'1', '0', '0', '1', '0','0', '1', '1', '0', '1'},
    {'1', '0', '0', '1', '0','0', '0', '1', '0', '1'},
    {'1', 'P', '0', '0', '0','0', '0', '0', '0', '1'},
    {'0', '1', '1', '1', '1','1', '1', '1', '1', '1'}
};

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static int is_wall(t_data *data, float x, float y)
{
    int map_x = (int)x / PIXEL;
    int map_y = (int)y / PIXEL;

    if (map_x < 0 || map_x >= mapX || map_y < 0 || map_y >= mapY)
        return 1;
    if ((int)data->player->posY/PIXEL != map_y || (int)data->player->posX/PIXEL != map_x)
        if (map[map_y][map_x] != '1')
            if (map[map_y][(int)data->player->posX/PIXEL] == '1' || map[(int)data->player->posY/PIXEL][map_x] == '1')
                return (1);
    return map[map_y][map_x] == '1';
}

static void get_player_pos(t_data *data)
{
    for (int i = 0; i < mapY; i++)
    {
        for (int j = 0; j < mapX; j++)
        {
            if (map[i][j] == 'P')
            {
                data->player->posY = i * PIXEL + PIXEL / 2; 
                data->player->posX = j * PIXEL + PIXEL / 2;
            }
        }
    }
}

static void init(t_data *data)
{
    mlx_texture_t *texture;

    data->player = malloc(sizeof(t_player));
    data->mlx = mlx_init(WIDTH, HEIGHT, "Raycasting with MLX42", false);
    get_player_pos(data);
    data->player->rotation = 0;
    data->wall_dir = 0;
    data->img = NULL;

    texture = mlx_load_png("../rsrcs/wall/wall1.png");
    if (!texture)
    {
        printf(RED "texture failed\n" RESET);
        exit(1);
    }
    data->wall = mlx_texture_to_image(data->mlx, texture);
    if (!data->wall)
    {
        printf(RED "image failed\n" RESET);
        exit(1);
    }
    mlx_delete_texture(texture);

    texture = mlx_load_png("../rsrcs/wall/wall2.png");
    if (!texture)
    {
        printf(RED "texture failed\n" RESET);
        exit(1);
    }
    data->wall1 = mlx_texture_to_image(data->mlx, texture);
    if (!data->wall1)
    {
        printf(RED "image failed\n" RESET);
        exit(1);
    }
    mlx_delete_texture(texture);

    texture = mlx_load_png("../rsrcs/wall/wall3.png");
    if (!texture)
    {
        printf(RED "texture failed\n" RESET);
        exit(1);
    }
    data->wall2 = mlx_texture_to_image(data->mlx, texture);
    if (!data->wall2)
    {
        printf(RED "image failed\n" RESET);
        exit(1);
    }
    mlx_delete_texture(texture);

    texture = mlx_load_png("../rsrcs/wall/wall4.png");
    if (!texture)
    {
        printf(RED "texture failed\n" RESET);
        exit(1);
    }
    data->wall3 = mlx_texture_to_image(data->mlx, texture);
    if (!data->wall3)
    {
        printf(RED "image failed\n" RESET);
        exit(1);
    }
    mlx_delete_texture(texture);
}

static void rotate(t_data *data, char c)
{
    if (c == 'r')
        data->player->rotation += SPEED_ROTATION;
    else
        data->player->rotation -= SPEED_ROTATION;
    if (data->player->rotation >= 360)
        data->player->rotation -= 360;
    else if (data->player->rotation < 0)
        data->player->rotation += 360;
    printf(BLUE "\nPlayer Rotation:\n\t%d°\n" RESET, data->player->rotation);
}

static float calculate_distance_to_wall(t_data *data, float rotation, int player_rotation, float *hitX, float *hitY) {
    float x = data->player->posX;
    float y = data->player->posY;
    float angle_rad = rotation * RADIANT;
    float prev_x;
    float prev_y;

    while ((int)y / PIXEL < mapY && (int)x / PIXEL < mapX && map[(int)y / PIXEL][(int)x / PIXEL] != '1') {
        prev_x = x;
        prev_y = y;

        x += cos(angle_rad);
        y += sin(angle_rad);
    }
    *hitX = x;
    *hitY = y;
    if ((int)prev_y / PIXEL != (int)y / PIXEL) {
        if (prev_y < y)
            data->wall_dir = 'S';
        else
            data->wall_dir = 'N';
    } else if ((int)prev_x / PIXEL != (int)x / PIXEL) {
        if (prev_x < x)
            data->wall_dir = 'E';
        else
            data->wall_dir = 'W';
    }
    return sqrt(pow(x - data->player->posX, 2) + pow(y - data->player->posY, 2));
}

static int	get_correct_color(u_int8_t *pixel)
{
	int	rgba;

	rgba = 0;
	rgba += pixel[0] << 24;
	rgba += pixel[1] << 16;
	rgba += pixel[2] << 8;
	rgba += pixel[3];
	return (rgba);
}

static void draw_rays(t_data *data)
{
    float distance;
    float rotation;
    float wall_height;
    int x, y, texture_x, texture_y;
    float hitX, hitY;
    int color;
    mlx_image_t *wall_img;

    if (data->img)
        mlx_delete_image(data->mlx, data->img);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);

    rotation = data->player->rotation - 90 - (WIDTH / 2) * DEGREE;
    for (int x = 0; x < WIDTH; x++) {
        distance = calculate_distance_to_wall(data, rotation, data->player->rotation, &hitX, &hitY);
        wall_height = (PIXEL / distance) * (PIXEL * 5);
        if (wall_height - (int)wall_height > 0.5)
            wall_height += 1;

        float hitPos;
        if (data->wall_dir == 'E' || data->wall_dir == 'W')
            hitPos = hitY / PIXEL;
        else
            hitPos = hitX / PIXEL;

        if (data->wall_dir == 'N')
            wall_img = data->wall;
        else if (data->wall_dir == 'S')
            wall_img = data->wall1;
        else if (data->wall_dir == 'E')
            wall_img = data->wall2;
        else if (data->wall_dir == 'W')
            wall_img = data->wall3;

        texture_x = (int)(hitPos * wall_img->width) % wall_img->width;

        for (y = 0; y < (int)wall_height; y++) {
            texture_y = (y * wall_img->height) / (int)wall_height;
            if (y + (HEIGHT - (int)wall_height) / 2 < data->img->height) {
                color = get_correct_color(&((u_int8_t *)wall_img->pixels)[(texture_y * wall_img->width + texture_x) * 4]);
                mlx_put_pixel(data->img, x, (float)y + ((float)HEIGHT - wall_height) / 2, color);
            }
        }

        rotation += DEGREE;
    }

    mlx_image_to_window(data->mlx, data->img, 0, 0);
}


static void event_mlx(mlx_key_data_t keydata, void *param)
{
    t_data *data = (t_data *)param;
    float temp_x;
    float temp_y;

    //ft_printf("%d\n", keydata.key);
    if (keydata.key == 256) // ESCAP
        exit(0);
    if (keydata.key == 262 && (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS))) // RIGHT
        rotate(data, 'r');
    if (keydata.key == 263 && (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS))) //LEFT
        rotate(data, 'l');
    if (keydata.key == 87 && (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS)))
    {
        temp_x = data->player->posX + SPEED * sin(data->player->rotation * RADIANT);
        temp_y = data->player->posY + SPEED * -1 * cos(data->player->rotation * RADIANT);
        if (!is_wall(data, temp_x, temp_y))
        {
            data->player->posX = temp_x;
            data->player->posY = temp_y;
        }
    }
    if (keydata.key == 83 && (keydata.action == (MLX_REPEAT) || keydata.action == (MLX_PRESS)))
    {
        temp_x = data->player->posX + SPEED * -1 * sin(data->player->rotation * RADIANT);
        temp_y = data->player->posY + SPEED * cos(data->player->rotation * RADIANT);
        if (!is_wall(data, temp_x, temp_y))
        {
            data->player->posX = temp_x;
            data->player->posY = temp_y;
        }
    }
    draw_rays(data);
}

static bool get_background(t_data *data)
{
    int y;
    int x;
    int color = 255 << 24 | 65 << 16 | 216 << 8 | 0;
    int color2 = 255 << 24 | 176 << 16 | 123 << 8 | 26;

    data->floor = mlx_new_image(data->mlx, WIDTH, HEIGHT/2);
    if (!data->floor)
        return (mlx_terminate(data->mlx), mlx_strerror(mlx_errno), true);
    y = -1;
    while (++y < data->floor->height)
    {
        x = -1;
        while (++x < data->floor->width)
            ((int32_t*)data->floor->pixels)[y * data->floor->width + x] = color;
    }
    data->ceiling = mlx_new_image(data->mlx, WIDTH, HEIGHT/2);
    if (!data->ceiling)
        return (mlx_terminate(data->mlx), mlx_strerror(mlx_errno), true);
    y = -1;
    while (++y < data->ceiling->height)
    {
        x = -1;
        while (++x < data->ceiling->width)
            ((int32_t*)data->ceiling->pixels)[y * data->ceiling->width + x] = color2;
    }
    mlx_image_to_window(data->mlx, data->ceiling, 0, 0);
    mlx_image_to_window(data->mlx, data->floor, 0, HEIGHT/2);
    return (false);    
}

int main(void)
{
    t_data data;
    
    init(&data);

    mlx_key_hook(data.mlx, event_mlx, &data);
    get_background(&data);
    draw_rays(&data);
    mlx_loop(data.mlx);
    mlx_terminate(data.mlx);
    return EXIT_SUCCESS;
}