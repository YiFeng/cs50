#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i  = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           BYTE avg_color = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
           image[i][j].rgbtBlue = avg_color;
           image[i][j].rgbtGreen = avg_color;
           image[i][j].rgbtRed = avg_color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i  = 0; i < height; i++)
    {
        // create a temporary array of RGBTRIPLE to copy each row of pixels
        RGBTRIPLE *temp = calloc(width * sizeof(RGBTRIPLE));
        for (int j = 0; j < width; j++)
        {
            temp[j] = image[i][j];
        }
        // copy tem to image from the last element to first element
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[(width-1) - j];
        }
        free(temp);
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
