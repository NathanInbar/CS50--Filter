#include "helpers.h"
#include "math.h"
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loop through the image
    //get the average of the RGB for each pixel
    //set all of the RGB values to that average

    //loop thru rows
    for (int i = 0; i < height; i++)
    {
        //loop thru cols
        for (int j = 0; j < width; j++)
        {
            //store the current pixels RGB data
            RGBTRIPLE px = image[i][j];

            //get the average of the 3
            int avg = round((px.rgbtRed + px.rgbtGreen + px.rgbtBlue) / 3.0);

            //assign the pixels RGB values to the Avg
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //loop through image
    //for each row, swap pixels horizonatally

    //create a reference 'buffer' to store the row's pixel data
    RGBTRIPLE buffer[width];

    for (int i = 0; i < height; i++)
    {

        //loop thru cols
        for (int j = 0; j < width; j++)
        {
            //save this rows pixel data into buffer
            buffer[j] = image[i][j];
        }

        //after that row has been saved...
        //go back through the row,
        //sphaghettios

        for (int j = 0; j < width; j++)
        {
            //overwrite the row in reverse
            image[i][j] = buffer[(width - 1) - j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //set pixels rgb to the average of the **OLD** 9 pixels around it inclusively
    //if its on the edge, do the same thing just dont count the pixels that dont exist

    //create copy of old image values
    RGBTRIPLE buffer[height][width];

    //copy image into buffer
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            buffer[y][x] = image[y][x];
        }
    }

    for (int x = 0; x < width; x++)
    {
        //loop thru cols
        for (int y = 0; y < height; y++)
        {
            int validPixels = 0;//used to track valid surrounding pixels (so we know how much to divide by for the average)
            double totalRed = 0, totalGreen = 0, totalBlue = 0;

            for (int k = -1; k <= 1; k++)
            {
                // i + (-1 , 0 , 1)

                for (int l = -1; l <= 1; l++)
                {
                    // l + (-1, 0, 1)
                    //x-coordinate = x + l. must be between 0 and width
                    //y-coordinate = y + k. must be between 0 and height
                    int xCoord = x + l;
                    int yCoord = y + k;

                    //if          VALID X POSITION         AND         VALID Y POSITION
                    if ((xCoord >= 0 && xCoord <= width - 1) && (yCoord >= 0 && yCoord <= height - 1))
                    {
                        //image and buffer are mapped as height to width for some dumb reason
                        totalRed += buffer[yCoord][xCoord].rgbtRed;
                        totalGreen += buffer[yCoord][xCoord].rgbtGreen;
                        totalBlue += buffer[yCoord][xCoord].rgbtBlue;

                        validPixels++;
                    }

                }//end for (l)
            }//end for(k)

            RGBTRIPLE pxAvg = {0, 0, 0};

            pxAvg.rgbtRed = round(totalRed / validPixels);
            pxAvg.rgbtGreen = round(totalGreen / validPixels);
            pxAvg.rgbtBlue = round(totalBlue / validPixels);

            image[y][x] = pxAvg;

        }//end for (y)
    }//end for (x)
    return;

}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    /**
    - get old pixel values in 3x3 around target pixel
    - treat out of bounds pixels as 0,0,0
    - compute Gx and Gy for each channel (multiple by matrix then sum)
    - compute Gx^2 + Gy^2, then round and cap at 255
    - set channel to that value

    Gx:
    -1,0,1
    -2,0,2
    -1,0,1

    Gy:
    -1,-2,-1
    0,0,0
    1,2,1
    **/
    RGBTRIPLE buffer[height][width];


    int gxMatrix[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int gyMatrix[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            buffer[y][x] = image[y][x];
        }
    }

    for (int x = 0; x < width; x++)
    {
        //loop thru cols
        for (int y = 0; y < height; y++)
        {
            int indexCounter = 0;

            double gxRed = 0, gxGreen = 0, gxBlue = 0;
            double gyRed = 0, gyGreen = 0, gyBlue = 0;
            double gRed = 0.0, gGreen = 0.0, gBlue = 0.0;

            for (int k = -1; k <= 1; k++)
            {

                for (int l = -1; l <= 1; l++)
                {

                    int xCoord = x + l;
                    int yCoord = y + k;

                    RGBTRIPLE px = {0, 0, 0};//out of bounds = black

                    if ((xCoord >= 0 && xCoord <= width - 1) && (yCoord >= 0 && yCoord <= height - 1))
                    {
                        px = buffer[yCoord][xCoord];
                    }

                    gxRed += px.rgbtRed * gxMatrix[indexCounter];
                    gxGreen += px.rgbtGreen * gxMatrix[indexCounter];
                    gxBlue += px.rgbtBlue * gxMatrix[indexCounter];

                    gyRed += px.rgbtRed * gyMatrix[indexCounter];
                    gyGreen += px.rgbtGreen * gyMatrix[indexCounter];
                    gyBlue += px.rgbtBlue * gyMatrix[indexCounter];

                    indexCounter++;

                }//end for (l)
            }//end for(k)

            gRed = sqrt((pow(gxRed, 2.0)) + (pow(gyRed, 2.0)));
            gGreen = sqrt((pow(gxGreen, 2.0)) + (pow(gyGreen, 2.0)));
            gBlue = sqrt((pow(gxBlue, 2.0)) + (pow(gyBlue, 2.0)));

            if (gRed > 255)
            {
                gRed = 255;
            }
            if (gGreen > 255)
            {
                gGreen = 255;
            }
            if (gBlue > 255)
            {
                gBlue = 255;
            }

            image[y][x].rgbtRed = round(gRed);
            image[y][x].rgbtGreen = round(gGreen);
            image[y][x].rgbtBlue = round(gBlue);

        }//end for (y)
    }//end for (x)
    return;
}
