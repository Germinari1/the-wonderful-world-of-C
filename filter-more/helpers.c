#include "helpers.h"
#include <math.h>

// Convert image to grayscale / OK
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avgp;
    for (int i=0; i<height; i++){
        for (int j=0; j < width; j++){
            RGBTRIPLE pixel = image[i][j];
            avgp = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed)/3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = avgp;
        }
    }
    return;
}

// Reflect image horizontally / OK
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //tmep var to store pixel bf transfering to "new image"
    RGBTRIPLE temp;
    for (int i=0; i<height; i++){
        for (int j=0; j < width/2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j -1];
            image[i][width - j -1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //copy image
    RGBTRIPLE temp[height][width];
    for (int i=0; i<height; i++){
        for (int j=0;j<width; j++){
            temp[i][j] = image[i][j];
        }
    }
    //calculate neghbor pixels
    for (int i=0; i<height; i++){
        for(int j=0; j<width; j++)
        {
            //define RBG couters vars. (find avgs)
            int totalr, totalg, totalb;
            totalr= totalg= totalb=0;
            float counter = 0.00;
            //get sorrounding pixels coords. by using relative positions
            for (int x= -1; x<2; x++)
            {
                for(int y=-1; y<2; y++)
                {
                    int cx = i + x;
                    int cy = j + y;
                    //chack validity
                    if (cx<0 || cx>(width-1) || cy<0 || cy>(height-1))
                    {
                        continue;
                    }
                    //get pixel values
                    totalr += image[cx][cy].rgbtRed;
                    totalg += image[cx][cy].rgbtGreen;
                    totalb += image[cx][cy].rgbtBlue;
                    counter ++;
                }
                //avg
                temp[i][j].rgbtRed=round(totalr/counter);
                temp[i][j].rgbtGreen=round(totalg/counter);
                temp[i][j].rgbtBlue=round(totalb/counter);
            }
        }
    }
    //transfer temp pixels into original image
    for (int i=0; i<height;i++)
    {
        for (int j=0; j< width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    //sobel operators
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxBlue = 0;
            int gyBlue = 0;
            int gxGreen = 0;
            int gyGreen = 0;
            int gxRed = 0;
            int gyRed = 0;

            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    if (i + r < 0 || i + r > height - 1)
                    {
                        continue;
                    }
                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }

                    gxBlue += image[i + r][j + c].rgbtBlue * gx[r + 1][c + 1];
                    gyBlue += image[i + r][j + c].rgbtBlue * gy[r + 1][c + 1];
                    gxGreen += image[i + r][j + c].rgbtGreen * gx[r + 1][c + 1];
                    gyGreen += image[i + r][j + c].rgbtGreen * gy[r + 1][c + 1];
                    gxRed += image[i + r][j + c].rgbtRed * gx[r + 1][c + 1];
                    gyRed += image[i + r][j + c].rgbtRed * gy[r + 1][c + 1];
                }
            }

            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));

            //cap pixel values to 255 if this value is exceeded
            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
        }
    }

    //transfer 'new pixels' to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
