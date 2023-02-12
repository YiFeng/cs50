#include "helpers.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void copy_image(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE temp[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i  = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           RGBTRIPLE temp_pixel = image[i][j];
           BYTE avg_color = (temp_pixel.rgbtBlue + temp_pixel.rgbtGreen + temp_pixel.rgbtRed) / 3;
           image[i][j].rgbtBlue = avg_color;
           image[i][j].rgbtGreen = avg_color;
           image[i][j].rgbtRed = avg_color;
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

        // copy tem to image from the last element to first element
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
    int indices[9][2];
    int num_members;
}
members;

void get_neighbor(members *neighbors, int height_index, int width_index, int height, int width)
{
    int num_members = 0;
    for (int i = height_index -1; i < height_index +2; i++)
    {
        for (int j = width_index -1; j < width_index +2; j++)
        {
            if (i > 0 && i < height && j > 0 && j < width)
            {
                neighbors->indices[num_members][0] = i;
                neighbors->indices[num_members][1] = j;
                num_members++;
            }
        }
    }
    neighbors->num_members = num_members;
}

// Create a function to caculate average color for one pixel one color
void cal_avg_color(RGBTRIPLE *avg_color, members *neighbors, int height, int width, RGBTRIPLE image[height][width])
{
    BYTE sum_red = 0x00;
    BYTE sum_green = 0x00;
    BYTE sum_blue = 0x00;

    for (int i = 0; i < neighbors->num_members; i++)
    {
        int height_index = neighbors->indices[i][0];
        int width_index = neighbors->indices[i][1];
        sum_red += round(image[height_index][width_index].rgbtRed / neighbors->num_members);
        sum_green += round(image[height_index][width_index].rgbtGreen / neighbors->num_members);
        sum_blue += round(image[height_index][width_index].rgbtBlue / neighbors->num_members);
    }
    avg_color->rgbtRed = sum_red;
    avg_color->rgbtGreen = sum_green;
    avg_color->rgbtBlue = sum_blue;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    copy_image(height, width, image, temp);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get each pixel's neighbors
            members *neighbors = calloc(1, sizeof(members));
            get_neighbor(neighbors, i, j, height, width);

            // caculate average colors of all neighbors
            RGBTRIPLE *avg_color = calloc(1, sizeof(RGBTRIPLE));
            cal_avg_color(avg_color, neighbors, height, width, image);
            free(neighbors);

            // assign new color to current pixel
            temp[i][j].rgbtRed = avg_color->rgbtRed;
            temp[i][j].rgbtGreen = avg_color->rgbtGreen;
            temp[i][j].rgbtBlue = avg_color->rgbtGreen;
            free(avg_color);
        }
    }
    copy_image(height, width, temp, image);
    free(temp);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
