#include "raycast.h"

char map[mapY][mapX] = {
    {'1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '1'},
    {'1', 'P', '1', '0', '1'},
    {'1', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '1'}
};

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static int is_wall(float x, float y)
{
    int map_x = (int)x / PIXEL;
    int map_y = (int)y / PIXEL;

    if (map_x < 0 || map_x >= mapX || map_y < 0 || map_y >= mapY) {
        return 1;
    }

    return map[map_y][map_x] == '1';
}

static void get_player_pos(t_data *data)
{
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            if (map[i][j] == 'P') {
                data->player->posY = i * PIXEL + PIXEL / 2; 
                data->player->posX = j * PIXEL + PIXEL / 2;
            }
        }
    }
}

static void init(t_data *data)
{
    data->player = malloc(sizeof(t_player));
    data->mlx = NULL;
    get_player_pos(data);
    data->player->rotation = 0;
    ft_printf(GREEN "\nPlayer pos:\n\tY: %d\n\tX: %d\n\n" RESET, data->player->posY, data->player->posX);
    data->red = get_rgba(255, 0, 0, 255);
    data->blue = get_rgba(0, 255, 0, 255);
    data->green = get_rgba(0, 0, 255, 255);
    data->pink = get_rgba(255, 255, 0, 255);
    data->wall_dir = 0;
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
}

static float calculate_distance_to_wall(t_data *data, float rotation) {
    float x = (float)data->player->posX;
    float y = (float)data->player->posY;
    float angle_rad = rotation * RADIANT;

    while (map[(int)y / PIXEL][(int)x / PIXEL] != '1') {
        float prev_x = x;
        float prev_y = y;
        
        x += cos(angle_rad);
        y += sin(angle_rad);
        
        if ((int)prev_y / PIXEL != (int)y / PIXEL) {
            if (prev_y < y) {
                data->wall_dir = 'S';
            } else {
                data->wall_dir = 'N';
            }
        } else if ((int)prev_x / PIXEL != (int)x / PIXEL) {
            if (prev_x < x) {
                data->wall_dir = 'E';
            } else {
                data->wall_dir = 'W';
            }
        }
    }
    return (sqrt(pow(x - data->player->posX, 2) + pow(y - data->player->posY, 2)));
}

static void draw_rays(t_data *data)
{
    float distance;
    float rotation;
    float wall_height;
    int x;
    int y;
    int wall_color;

    rotation = data->player->rotation - 90 - (WIDTH / 2) * DEGREE;
    for (int i = 0; i < WIDTH; i++) {
        if (i % 2 == 0)
            distance = calculate_distance_to_wall(data, rotation);
        wall_height = PIXEL / distance * 300;
        if (data->img[i])
            mlx_delete_image(data->mlx, data->img[i]);
        data->img[i] = mlx_new_image(data->mlx, 1, (int)wall_height);

        if (data->wall_dir == 'N')
            wall_color = data->red;
        if (data->wall_dir == 'S')
            wall_color = data->blue;
        if (data->wall_dir == 'W')
            wall_color = data->green;
        if (data->wall_dir == 'E')
            wall_color = data->pink;
        for (y = 0; y < (int)wall_height; y++) {
            mlx_put_pixel(data->img[i], 0, y, wall_color);
        }

        mlx_image_to_window(data->mlx, data->img[i], i, (HEIGHT - (int)wall_height) / 2);
        rotation += DEGREE;
    }
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
    if (keydata.key == 87 && (keydata.action == (MLX_PRESS))) {
        temp_x = data->player->posX + SPEED * sin(data->player->rotation * RADIANT);
        temp_y = data->player->posY + SPEED * -1 * cos(data->player->rotation * RADIANT);
        if (!is_wall(temp_x, temp_y)) {
            data->player->posX = temp_x;
            data->player->posY = temp_y;
        }
    }
    if (keydata.key == 83 && (keydata.action == (MLX_PRESS))) {
        temp_x = data->player->posX + SPEED * -1 * sin(data->player->rotation * RADIANT);
        temp_y = data->player->posY + SPEED * cos(data->player->rotation * RADIANT);
        if (!is_wall(temp_x, temp_y)) {
            data->player->posX = temp_x;
            data->player->posY = temp_y;
        }
    }
    printf(BLUE "\nPlayer Rotation:\n\t%d°\n" RESET, data->player->rotation);
    draw_rays(data);
}

int main(void) {
    t_data data;
    
    init(&data);
    data.mlx = mlx_init(WIDTH, HEIGHT, "Raycasting with MLX42", false);

    mlx_key_hook(data.mlx, event_mlx, &data);
    draw_rays(&data);
    mlx_loop(data.mlx);
    mlx_terminate(data.mlx);
    return EXIT_SUCCESS;
}
