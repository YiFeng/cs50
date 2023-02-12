#include "helpers.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i  = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           RGBTRIPLE temp_pixel = image[i][j];
           int sum = temp_pixel.rgbtBlue + temp_pixel.rgbtGreen + temp_pixel.rgbtRed;
           int avg_color = round(sum / 3.0);

           image[i][j].rgbtBlue = (BYTE) avg_color;
           image[i][j].rgbtGreen = (BYTE) avg_color;
           image[i][j].rgbtRed = (BYTE) avg_color;
        }
    }
    return;
}

// swap values from an array
void swap(RGBTRIPLE *temp_row, int index1, int index2)
{
    RGBTRIPLE temp_pixel = temp_row[index1];
    temp_row[index1] = temp_row[index2];
    temp_row[index2] = temp_pixel;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i  = 0; i < height; i++)
    {
        // create a temporary array of RGBTRIPLE to copy each row of pixels
        RGBTRIPLE *temp_row = image[i];

        // swap each row's first few elements and last few elements
        int swap_times = (width / 2) + 1;
        for (int j = 0; j < swap_times; j++)
        {
            swap(temp_row, j, width-1-j);
        }
    }
    return;
}

// Blur image
// create a function to get neighbor pixels'index of a target pixel
// save an array of index and array length to a struct
typedef struct
{
    RGBTRIPLE *pixs;
    int len;
}
PixelArray;

typedef struct
{
    int height;
    int width;
}
Coordinate;

int grid_size = 9;

PixelArray get_neighbor(Coordinate total_size, RGBTRIPLE image[total_size.height][total_size.width], Coordinate pix_curr)
{
    PixelArray neighbors;
    neighbors.pixs = calloc(grid_size, sizeof(RGBTRIPLE));

    int num_members = 0;
    int num_pix = 0;
    for (int i = pix_curr.height -1; i < pix_curr.height +2; i++)
    {
        for (int j = pix_curr.width -1; j < pix_curr.width +2; j++)
        {
            if (i > 0 && i < total_size.height && j > 0 && j < total_size.width)
            {
                neighbors.pixs[num_pix] = image[i][j];
                num_members++;
            }
            num_pix++;
        }
    }
    neighbors.len = num_members;

    return neighbors;
}

int* sum_array_multiply(PixelArray neighbors, int kernel[])
{
    int *sum_colors = calloc(3, sizeof(int));
    sum_colors[0] = 0; //Red
    sum_colors[1] = 0; //Green
    sum_colors[2] = 0; //Blue

    for (int i = 0; i < grid_size; i++)
    {
        RGBTRIPLE neighbor_pix = neighbors.pixs[i];
        int target = kernel[i];
        sum_colors[0] += round(neighbor_pix.rgbtRed * target);
        sum_colors[1] += round(neighbor_pix.rgbtGreen * target);
        sum_colors[2] += round(neighbor_pix.rgbtBlue * target);
    }
    return sum_colors;
}

// Create a function to caculate average color for one pixel one color
RGBTRIPLE cal_avg_color(PixelArray neighbors)
{
    RGBTRIPLE avg_color;

    // create an array of int, initialize acording to a pixels'weights
    int kernel[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

    int *sum_color = sum_array_multiply(neighbors, kernel);
    BYTE avg_red = (BYTE)(sum_color[0] / neighbors.len);
    BYTE avg_green = (BYTE)(sum_color[1] / neighbors.len);
    BYTE avg_blue = (BYTE)(sum_color[2] / neighbors.len);
    free(sum_color);

    avg_color.rgbtRed = avg_red;
    avg_color.rgbtGreen = avg_green;
    avg_color.rgbtBlue = avg_blue;

    return avg_color;
}

RGBTRIPLE cal_sobel_color(PixelArray neighbors)
{
    RGBTRIPLE sobel_color;
    // create an array, initialize acording to a pixels'weights
    int kernel_x[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int kernel_y[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    int *gx = sum_array_multiply(neighbors, kernel_x);
    int *gy = sum_array_multiply(neighbors, kernel_y);

    BYTE sobel_red = (BYTE)(sqrt(gx[0]*gx[0] + gy[0]*gy[0]));
    BYTE sobel_green = (BYTE)(sqrt(gx[1]*gx[1] + gy[1]*gy[1]));
    BYTE sobel_blue = (BYTE)(sqrt(gx[2]*gx[2] + gy[2]*gy[2]));
    free(gx);
    free(gy);

    sobel_color.rgbtRed = sobel_red;
    sobel_color.rgbtGreen = sobel_green;
    sobel_color.rgbtBlue = sobel_blue;

    return sobel_color;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // info of whole image
    Coordinate total_size;
    total_size.height = height;
    total_size.width = width;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get each pixel's coordinate
            Coordinate pix_curr;
            pix_curr.height = i;
            pix_curr.width = j;

            PixelArray neighbors = get_neighbor(total_size, image, pix_curr);

            // caculate average colors of all neighbors
            RGBTRIPLE avg_color = cal_avg_color(neighbors);
            free(neighbors.pixs);

            // assign new color to current pixel
            image[i][j] = avg_color;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // info of whole image
    Coordinate total_size;
    total_size.height = height;
    total_size.width = width;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get each pixel's coordinate
            Coordinate pix_curr;
            pix_curr.height = i;
            pix_curr.width = j;

            PixelArray neighbors = get_neighbor(total_size, image, pix_curr);

            // caculate average colors of all neighbors
            RGBTRIPLE sobel_color = cal_sobel_color(neighbors);
            free(neighbors.pixs);

            // assign new color to current pixel
            image[i][j] = sobel_color;
        }
    }

    return;
}
