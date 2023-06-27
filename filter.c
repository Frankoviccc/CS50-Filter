#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Neem het gemiddelde van de drie kleuren en deel deze door 3.0 zodat je het getal achter
            // De komma kan rounden naar dichtsbijzijnde getal
            int red = round(((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0));
            int green = round(((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0));
            int blue = round(((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0));

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
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
            int sepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));
            printf("Red: %d, Green: %d, Blue: %d\n", sepiaRed, sepiaGreen, sepiaBlue);

            if (sepiaRed >= 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen >= 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue >= 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Store current index per colour in variable
            int redTemp = image[i][j].rgbtRed;
            int greenTemp = image[i][j].rgbtGreen;
            int blueTemp = image[i][j].rgbtBlue;
            // Change the index of your current index to last index
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            // Change the value of the last index to the value of the first index
            image[i][width - j - 1].rgbtRed = redTemp;
            image[i][width - j - 1].rgbtGreen = greenTemp;
            image[i][width - j - 1].rgbtBlue = blueTemp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Maak een kopie van de afbeeldingen zodat iedere keer wanneer je een berekening maakt
            // Van de pixels, je de niet-aangepaste pixels gebruikt //
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redAverage = 0;
            int greenAverage = 0;
            int blueAverage = 0;
            int counter = 0;
            // For loop to iterate trough surrounding pixels
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    // Hierdoor pakt hij altijd 9 cijfers mits niet negatief
                    int newRow = i + dx;
                    int newCol = j + dy;
                    // Take every pixels aslong as it doesnt exceed array
                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        redAverage += copy[newRow][newCol].rgbtRed;
                        greenAverage += copy[newRow][newCol].rgbtGreen;
                        blueAverage += copy[newRow][newCol].rgbtBlue;
                        // Counter++ so you know how many pixels have been counted
                        counter++;
                    }
                }
            }
            // Divide the average by the counter
            image[i][j].rgbtRed = round((float)redAverage / counter);
            image[i][j].rgbtGreen = round((float)greenAverage / counter);
            image[i][j].rgbtBlue = round((float)blueAverage / counter);
        }
    }
    return;
}
