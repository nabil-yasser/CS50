#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE tmpAverage;
            if (round(((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0)) > 255)
            {
                tmpAverage = 255;
            }
            else
            {
                tmpAverage = round(((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0));
            }
            image[i][j].rgbtRed = tmpAverage;
            image[i][j].rgbtGreen = tmpAverage;
            image[i][j].rgbtBlue = tmpAverage;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE tmpRed = 0;
            BYTE tmpGreen = 0;
            BYTE tmpBlue = 0;
            if (round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue) > 255)
            {
                tmpRed = 255;
            }
            else
            {
                tmpRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            }
            if (round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue) > 255)
            {
                tmpGreen = 255;
            }
            else
            {
                tmpGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            }
            if (round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue) > 255)
            {
                tmpBlue = 255;
            }
            else
            {
                tmpBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            }
            image[i][j].rgbtRed = tmpRed;
            image[i][j].rgbtGreen = tmpGreen;
            image[i][j].rgbtBlue = tmpBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageTmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < width; j++, k--)
        {
            imageTmp[i][j] = image[i][k];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageTmp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    WORD AverageRed = 0, AverageGreen = 0, AverageBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average colors for top Row
            if (i == 0)
            {
                // Calculate average colors for corners
                if (j == 0)
                {
                    AverageRed = round(((image[i][j].rgbtRed + image[i][j + 1].rgbtRed
                                + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4.0));
                    AverageGreen = round(((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen
                                + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4.0));
                    AverageBlue = round(((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue
                                + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4.0));
                }
                else if (j == width - 1)
                {
                    AverageRed = round(((image[i][j].rgbtRed + image[i][j - 1].rgbtRed
                                + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4.0));
                    AverageGreen = round(((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen
                                + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4.0));
                    AverageBlue = round(((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue
                                + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4.0));
                }
                // Calculate average colors for top edge
                else
                {
                    AverageRed = round(((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed
                                + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0));
                    AverageGreen = round(((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen
                                + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0));
                    AverageBlue = round(((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue
                                + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0));
                }
            }
            // Calculate average colors for bottom Row
            else if (i == height - 1)
            {
                // Calculate average colors for corners
                if (j == 0)
                {
                    AverageRed = round(((image[i][j].rgbtRed + image[i][j + 1].rgbtRed
                                + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4.0));
                    AverageGreen = round(((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen
                                + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4.0));
                    AverageBlue = round(((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue
                                + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4.0));
                }
                else if (j == width - 1)
                {
                    AverageRed = round(((image[i][j].rgbtRed + image[i][j - 1].rgbtRed
                                + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4.0));
                    AverageGreen = round(((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen
                                + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4.0));
                    AverageBlue = round(((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue
                                + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4.0));
                }
                // Calculate average colors for bottom edge
                else
                {
                    AverageRed = round(((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed
                                + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0));
                    AverageGreen = round(((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen
                                + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0));
                    AverageBlue = round(((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue
                                + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0));
                }
            }
            // Calculate average colors for the whole image
            else
            {
                // Calculate average colors for left edge
                if (j == 0)
                {
                    AverageRed = round(((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed
                                + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0));
                    AverageGreen = round(((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen
                                + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0));
                    AverageBlue = round(((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue
                                + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0));
                }
                // Calculate average colors for right edge
                else if (j == width - 1)
                {
                    AverageRed = round(((image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j - 1].rgbtRed
                                + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0));
                    AverageGreen = round(((image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen
                                + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0));
                    AverageBlue = round(((image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue
                                + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0));
                }
                // Calculate average colors for middle of image
                else
                {
                    AverageRed = round(((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed
                                + image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed
                                + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0));
                    AverageGreen = round(((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen
                                + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen
                                + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0));
                    AverageBlue = round(((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue
                                + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue
                                + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0));
                }
            }
            if (AverageRed > 255)
            {
                AverageRed = 255;
            }
            if (AverageGreen > 255)
            {
                AverageGreen = 255;
            }
            if (AverageBlue > 255)
            {
                AverageBlue = 255;
            }
            copy[i][j].rgbtRed = AverageRed;
            copy[i][j].rgbtGreen = AverageGreen;
            copy[i][j].rgbtBlue = AverageBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy [i][j];
        }
    }
    return;
}
