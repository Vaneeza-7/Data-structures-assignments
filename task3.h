#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/imgcodecs.hpp>

#include<iostream>
#include <stdio.h>
#include<cmath>
#include"task1.h"

using namespace cv;
using namespace std;

void diceCof(Mat gt, Mat img)
{
    float fp=0, tp=0, fn=0, dice=0, num1=0, num2=0;
    int cols = img.cols;
    int rows = img.rows;


    int** image = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        image[i] = new int[cols];
    }

    int** truth = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        truth[i] = new int[cols];
    }
   
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            image[i][j] = (int)img.at<uchar>(i, j);
            truth[i][j] = (int)gt.at<uchar>(i, j);
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (image[i][j] == 255)
                if(truth[i][j]==255)
            {
                tp++;
            }

            if (image[i][j] ==255)
                if(truth[i][j]!=255)
            {
                fp++;
            }

        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (image[i][j] == 255)
            {
                num1++;
            }
            if (truth[i][j] == 255)
            {
                num2++;
            }

        }
    }
    if (num1 > num2) {
        fn = num1 - num2;
    }
    else
        fn = 0;

    dice = (2 * tp) / (fn + (2 * tp) + fp);

    cout << "The Dice Coefficient is : " << dice << endl;
    

}
