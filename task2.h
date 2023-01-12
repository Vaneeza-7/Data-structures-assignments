#pragma once
//kmeans 

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/imgcodecs.hpp>
#include <iostream>
#include <stdio.h>
#include<cmath>
#include"task3.h"
//#include"source.cpp"

using namespace cv;
using namespace std;

class point {
    int x;
    int y;
    int pxl;

public:
    point()
    {
        x = 0;
        y = 0;
        pxl = 0;
    }
    point(int x1, int y1, int pixel)
    {
        x = x1;
        y = y1;
        pxl = pixel;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    int getPxl()
    {
        return pxl;
    }

    void setPxl(int P)
    {
        pxl = P;
    }

    void setX(int X)
    {
        x = X;
    }

    void setY(int Y)
    {
        y = Y;
    }

    bool operator==(const point other)
    {
        if (x == other.x && y == other.y)
            return true;
        else
            return false;
    }

    bool operator!=(const point other)
    {
        if (x == other.x && y == other.y)
            return false;
        else
            return true;
    }

    int EuclideanDistance(point P)
    {
        int x1 = P.x;
        int y1 = P.y;
        return (int)sqrt(pow(x1 - x, 2) + pow(y1 - y, 2) * 1.0);
    }

    /*point operator<(point other)
    {
        EuclideanDistance(x, y, other.x, other.y);
    }*/
};

int EuclideanDistance(point P1, point P2)
{
    int x1 = P1.getX();
    int x2 = P2.getX();
    int y1 = P1.getY();
    int y2 = P2.getY();
    return (int)sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

//int smaller(int a, int b)
//{
//    if (a < b)
//        return a;
//    else
//        return b;
//}

point calculateMeans(int** arr, int rows, int cols, int times)
{
    int centroid = 0;
    int size = rows * cols;
    size = size / 2;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            centroid += arr[i][j];
            //if (arr[i][j] == 0)
                //size--;
        }
    }

    centroid = centroid / size;
    /*point centroid;
    int x1 = 0;
    int y1 = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            x1 += i;
            y1 += j;
        }
    }
    x1 = x1 / rows;
    y1 = y1 / cols;
    centroid.setX(x1);
    centroid.setY(y1);

    return centroid;*/
    point centre;
    int xx = 0;
    int yy = 0;
    int** lesion = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        lesion[i] = new int[cols];
    }

    //int res = arr[0][0];
    int count = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (arr[i][j] != 0)
            {
                xx = xx + i;
                yy = yy + j;
                count++;
            }
            else {
                xx = xx + 0;
                rows--;
                yy = yy + 0;
                cols--;
            }
        }
    }
    xx = xx/size;
    yy = yy/size;
    centre.setX(xx);
    centre.setY(yy);
    centre.setPxl(centroid);

    return centre; 

}

void kMeans(Mat img)
{
    int width = img.cols;
    int height = img.rows;


    int** ImageArray = new int* [height];
    for (int i = 0; i < height; i++)
    {
        ImageArray[i] = new int[width];
    }

    //int x;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < img.channels(); k++) {
                ImageArray[i][j] = (int)img.at<Vec3b>(i, j)[k];
            }
            //x=(int)img.at<uchar>(i, j);


            //    cout << "Value of pixel" << "(" << i << "," << j << ")" << "=" << x << endl;
            ////showing the values in console window//
        }
    }
    //K=2, clusters are 2

    int** cluster1 = new int* [height];
    for (int i = 0; i < height; i++)
    {
        cluster1[i] = new int[width];
    }

    int** cluster2 = new int* [height];
    for (int i = 0; i < height; i++)
    {
        cluster2[i] = new int[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cluster1[i][j] = 0;
            cluster2[i][j] = 0;
        }
    }

    // picking two random cluster points

    point p1(0, 0, ImageArray[0][0]);
    point p2(15, 20, ImageArray[15][20]);
    int s = 0;
    int z = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            point every(i, j, ImageArray[i][j]);
           /* int dist1 = ImageArray[0][0] - ImageArray[i][j];
            int dist2 = ImageArray[15][20] - ImageArray[i][j];*/
            int dist1 = every.EuclideanDistance(p1);
            int dist2 = every.EuclideanDistance(p2);
            if (dist1 < dist2)
            {       cluster1[i][j] = every.getPxl();//Imagearray[i][j];
                     s++;
            }
            else {
                cluster2[i][j] = every.getPxl();
                z++;
            }
        }
    }
    point prevc1(0, 0, ImageArray[0][0]);
    point prevc2(15, 20, ImageArray[15][20]);

    point c1 = calculateMeans(cluster1, height, width, s);
    point c2 = calculateMeans(cluster2, height, width, z);

    //int times = 0;
  /*  int sum1 = 0;
    int sum2 = 0;
    int xx1 = 0;
    int yy1 = 0;
    int xx2 = 0;
    int yy2 = 0;*/
    int count1 = 0;
    int count2 = 0;
    while (c1!= prevc1&& c2 != prevc2) {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                point every(i, j, ImageArray[i][j]);/*
                int dist1 = c1.getPxl() - ImageArray[i][j];
                int dist2 = c2.getPxl() - ImageArray[i][j];*/
                int dist1 = every.EuclideanDistance(c1);
                int dist2 = every.EuclideanDistance(c2);
                if (dist1 < dist2)
                {
                    cluster1[i][j] = every.getPxl();
                    count1++;
                    /*sum1 = cluster1[i][j] + sum1;
                    xx1 = i + xx1;
                    yy1 = j + yy1;*/

                }//Imagearray[i][j];
                else
                {
                    cluster2[i][j] = every.getPxl();
                    count2++;
                    /*sum2 = sum2 + cluster2[i][j];
                    xx2 = i-xx1 + xx2;
                    yy2 = j-yy1 + yy2;
                }*/

                }
                /*  xx2 = xx2 / height;
                  xx1 = xx1 / height;
                  yy2 = yy2 / width;
                  yy2 = yy2 / width;*/
            }
            
        }
        prevc1 = c1;
        prevc2 = c2;
        //c1 = point(xx1, yy1, sum1);
        //c2 = point(xx2, yy2, sum2);
        c1 = calculateMeans(cluster1, height, width, count1);
        c2 = calculateMeans(cluster2, height, width, count2);
        count1 = 0;
        count2 = 0;

    }
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (ImageArray[i][j] == cluster1[i][j])
                    ImageArray[i][j] = 255;
                if (ImageArray[i][j] == cluster2[i][j])
                    ImageArray[i][j] = 0;
            }
        }


        /*for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                ImageArray[i][j] = cluster1[i][j] || cluster2[i][j];

            }
        }*/

        //for (int i = 0; i < height; i++)
        //{
        //    for (int j = 0; j < width; j++)
        //    {
        //        cluster1[i][j] = 0;
        //        cluster2[i][j] = 255;
        //        //ImageArray[i][j] = cluster1[i][j]+cluster2[i][j];
        //    }
        //}

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                for (int k = 0; k < img.channels(); k++)
                {
                    img.at<Vec3b>(i, j)[k] = ImageArray[i][j];
                }
                //x=(int)img.at<uchar>(i, j);
                //if (x == 255)
                //{
                //    cout << "Value of pixel" << "(" << i << "," << j << ")" << "=" << x << endl;
                //}//showing the values in console window//
            }
        }

        Mat gt;
        string image_path = samples::findFile("Ground Truths/IMD063_lesion.bmp");
        gt = imread(image_path, IMREAD_GRAYSCALE);
        if (gt.empty())
        {
            cout << "Could not read the image: " << image_path << endl;
        }

        diceCof(gt, img);

        imshow("Display window", img);
        int k = waitKey(0); // Wait for a keystroke in the window
        if (k == 's')
        {
            imwrite("Original Images/IMD002.bmp", img);
        }
    
}

//int main()
//{
//    Mat img;
//    string image_path = samples::findFile("Original Images/IMD002.bmp");
//    img = imread(image_path, IMREAD_COLOR);
//    if (img.empty())
//    {
//        cout << "Could not read the image: " << image_path << endl;
//        return 1;
//    }
//
//    
//
//    kMeans(img);
//    
//    return 0;
//}