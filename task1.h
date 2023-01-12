#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/imgcodecs.hpp>
#include <iostream>
#include <stdio.h>
#include"task3.h"

using namespace cv;
using namespace std;
//
//class Equivalent
//{
//    int L1;
//    int L2;
//public:
//    Equivalent()
//    {
//        L1 = 0;
//        L2 = 0;
//    }
//
//    Equivalent(int label1, int label2)
//    {
//        L1 = label1;
//        L2 = label2;
//    }
//
//    int getLabel1()
//    {
//        return L1;
//    }
//
//    int getLabel2()
//    {
//        return L2;
//    }
//
//};

int smaller(int a, int b)
{
    if (a <= b)
        return a;
    else
        return b;

}

int larger(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

int** sort2D(int** arr, int n, int m)
{
    cout << "Im inside sorting" << endl;
    int i, j, temp;

    for (i = 0; i < n * m - 1; ++i) {
        for (j = 0; j < n * m - 1 - i; ++j) {
            // row = j/m
            // column = j%m
            if (arr[j / m][j % m] > arr[(j + 1) / m][(j + 1) % m]) {

                temp = arr[(j + 1) / m][(j + 1) % m];
                arr[(j + 1) / m][(j + 1) % m] = arr[j / m][j % m];
                arr[j / m][j % m] = temp;

            }
        }
    }
    return arr;
}

int frequency(int** arr, int rows, int cols)
{
    int maxCount = 1;
    int count = 1;
    int freq = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 1; j < cols; j++)
        {

            if (arr[i][j] == arr[i][j - 1] && arr[i][j] != 0)
                count++;
            else
                count = 1;

            if (count > maxCount) {
                maxCount = count;
                freq = arr[i][j - 1];
            }
        }
    }

    return freq;
}

//int frequency(int** Label, int rows, int cols) {
//    int  frequency = 0, label = 0;
//
//    int** freq = new int* [rows];
//    int maj_lesion = 0, maj_lesion_freq = 0;
//    int* lesion = new int[cols];
//    for (int i = 0; i < rows; i++) {
//        freq[i] = new int[cols];
//    }
//    for (int i = 0; i < rows-1; i++) {
//        for (int j = 0; j < cols-1; j++) {
//            frequency = 1;
//
//            label = Label[i][j];
//
//            if (freq[i][j] != 0) {
//
//                if (Label[i][j] != 0) {
//                    for (int x = 0; x < rows; x++) {
//                        for (int y = 0; y < cols; y++) {
//
//
//                            if ((i == x) && (j == y)) {
//                                continue;
//                            }
//                            if (Label[i][j] == Label[x][y]) {
//                                freq[x][y] = 0;
//                                frequency++;
//                            }
//
//                        }
//
//                    }
//                    lesion[label] = frequency;
//                }
//            }
//        }
//    }
//
//    for (int i = 0; i < cols; i++) {
//        if (lesion[i] > maj_lesion_freq) {
//            maj_lesion_freq = lesion[i];
//            maj_lesion = i;
//        }
//    }
//
//    return maj_lesion;
//
//}

void ConnectedComponentsLabelling(Mat img)
{
    cout << "Im in func ConnComp" << endl;
    //taking an image matrix//
    int cols = img.cols;
    int rows = img.rows;


    int** Image = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        Image[i] = new int[cols];
    }

    //int x;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Image[i][j] = (int)img.at<uchar>(i, j);

        }
    }

    int* equivalency = new int[cols];
    for (int i = 0; i < cols; i++)
    {
        equivalency[i] = 0;
    }

    int L = 0; //labelIndex
    int** LabelArray = new int* [rows];  //array for storing labels
    for (int i = 0; i < rows; i++)
    {
        LabelArray[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++)       //label for first pixel i.e. [0][0] index
    {
        for (int j = 0; j < cols; j++)
        {
            LabelArray[i][j] = 0;
        }
    }

    for (int i = 0; i < rows; i++)       //label for first pixel i.e. [0][0] index
    {
        for (int j = 0; j < cols; j++)
        {
            if (Image[0][0] > 0)
            {
                L++;
                LabelArray[0][0] = L;
            }
        }
    }
    //    //column-wise if labels are same then assign the previous label 
    //    for (int i = 1; i < cols - 1; i++)           //0th row and any column excluding 0th column
    //    {
    //        for (int j = 0; j < rows; j++)         //label pixels in row j = 0
    //        {
    //            if (Image[i][0] > 0)
    //            {
    //                if (Image[i][0] == Image[i - 1][0])
    //                {
    //                    LabelArray[i][0] = LabelArray[i - 1][0];
    //                }
    //                if (Image[i][0] != Image[i - 1][0])
    //                {
    //                    L++;
    //                    LabelArray[i][0] = L;
    //                }
    //            }
    //        }
    //    }
    //}
    //
    //row-wise if labels are same then assign the previous label 
    //for (int i = 0; i < cols; i++)              //label pixels in col i=0
    //{
    //    for (int j = 1; j < rows - 1; j++)        //0th column and any row excluding 0th row 
    //    {
    //        if (Image[0][j] > 0 && Image[0][j] == Image[0][j - 1])
    //        {
    //            LabelArray[0][j] = LabelArray[0][j - 1];
    //        }
    //        if (Image[0][j] > 0 && Image[0][j] != Image[0][j - 1])
    //        {
    //            L++;
    //            LabelArray[0][j] = L;
    //        }
    //    }
    //}
    cout << "Im now assigning neighbours" << endl;
    int sml, small, smal, lg, lag, larg;

    for (int i = 1; i < rows; i++)              //label pixels in col i=0
    {
        for (int j = 1; j < cols; j++)        //0th column and any row excluding 0th row 
        {
            //if no neighbours have 1
            if (Image[i][j] == 255)
                if (Image[i - 1][j] == 0)
                    if (Image[i][j - 1] == 0)
                        if (Image[i - 1][j - 1] == 0)
                            if (Image[i - 1][j + 1] == 0)
                            {
                                L++;
                                LabelArray[i][j] = L;
                            }
            //if only one of the 4 neighbours have one
        /*if (Image[i][j] == 255)
            if (Image[i - 1][j] == 255)
            {
                LabelArray[i][j] = LabelArray[i - 1][j];
            }
            else if (Image[i - 1][j - 1] == 255)
            {
                LabelArray[i][j] = LabelArray[i - 1][j - 1];
            }
            else if (Image[i-1][j + 1] == 255)
            {
                LabelArray[i][j] = LabelArray[i-1][j + 1];
            }
            else if (Image[i][j - 1] == 255) {
                LabelArray[i][j] = LabelArray[i][j - 1];
            }
            else
                L++;
                LabelArray[i][j] = L;
*/

            if (Image[i][j] == 255)
                if (Image[i - 1][j] == 255)
                    if (Image[i - 1][j - 1] != 255)
                        if (Image[i - 1][j + 1] != 255)
                            if (Image[i][j - 1] != 255)
                            {
                                LabelArray[i][j] = LabelArray[i - 1][j];
                            }

            if (Image[i][j] == 255)
                if (Image[i - 1][j] != 255)
                    if (Image[i - 1][j - 1] == 255)
                        if (Image[i - 1][j + 1] != 255)
                            if (Image[i][j - 1] != 255)
                            {
                                LabelArray[i][j] = LabelArray[i - 1][j - 1];
                            }

            if (Image[i][j] == 255)
                if (Image[i - 1][j] != 255)
                    if (Image[i - 1][j - 1] != 255)
                        if (Image[i - 1][j + 1] == 255)
                            if (Image[i][j - 1] != 255)
                            {
                                LabelArray[i][j] = LabelArray[i - 1][j + 1];
                            }

            if (Image[i][j] == 255)
                if (Image[i - 1][j] != 255)
                    if (Image[i - 1][j - 1] != 255)
                        if (Image[i - 1][j + 1] != 255)
                            if (Image[i][j - 1] == 255)
                            {
                                LabelArray[i][j] = LabelArray[i][j - 1];
                            }
            //more than one neighbour have 1, cases

            //case 1 : if all 4 neighbours have 1
            if (Image[i][j] == 255)
                if (Image[i - 1][j] == 255)
                    if (Image[i - 1][j - 1] == 255)
                        if (Image[i - 1][j + 1] == 255)
                            if (Image[i][j - 1] == 255)
                            {
                                sml = smaller(LabelArray[i - 1][j], LabelArray[i - 1][j - 1]);
                                lg = larger(LabelArray[i - 1][j], LabelArray[i - 1][j - 1]);
                                //equivalency[lg] = sml;
                                smal = smaller(sml, LabelArray[i - 1][j + 1]);
                                lag = larger(sml, LabelArray[i - 1][j + 1]);
                                //equivalency[lg] = smal;
                                small = smaller(smal, LabelArray[i][j - 1]);
                                larg = larger(smal, LabelArray[i][j - 1]);
                                equivalency[larg] = small;
                                equivalency[lg] = small;
                                equivalency[lag] = small;
                                LabelArray[i][j] = small;
                            }
            //case 2: if 3 neighbours have 1
            if (Image[i][j] == 255)
                if (Image[i - 1][j] == 255)
                    if (Image[i - 1][j - 1] == 255)
                        if (Image[i - 1][j + 1] == 255)
                            if (Image[i][j - 1] != 255)
                            {
                                sml = smaller(LabelArray[i - 1][j], LabelArray[i - 1][j - 1]);
                                lg = larger(LabelArray[i - 1][j], LabelArray[i - 1][j - 1]);
                                //equivalency[lg] = sml;
                                smal = smaller(sml, LabelArray[i - 1][j + 1]);
                                lag = larger(sml, LabelArray[i - 1][j + 1]);
                                equivalency[lg] = smal;
                                equivalency[lag] = smal;
                                LabelArray[i][j] = smal;
                            }

            if (Image[i][j] == 255)
                if (Image[i - 1][j] == 255)
                    if (Image[i - 1][j - 1] == 255)
                        if (Image[i - 1][j + 1] != 255)
                            if (Image[i][j - 1] == 255)
                            {
                                sml = smaller(LabelArray[i - 1][j], LabelArray[i - 1][j - 1]);
                                lg = larger(LabelArray[i - 1][j], LabelArray[i - 1][j - 1]);
                                //equivalency[lg] = sml;
                                smal = smaller(sml, LabelArray[i][j - 1]);
                                lag = larger(sml, LabelArray[i][j - 1]);
                                equivalency[lg] = smal;
                                equivalency[lag] = smal;
                                LabelArray[i][j] = smal;
                            }

            if (Image[i][j] == 255)
                if (Image[i - 1][j] == 255)
                    if (Image[i - 1][j - 1] != 255)
                        if (Image[i - 1][j + 1] == 255)
                            if (Image[i][j - 1] == 255)
                            {
                                sml = smaller(LabelArray[i - 1][j], LabelArray[i][j - 1]);
                                lg = larger(LabelArray[i - 1][j], LabelArray[i][j - 1]);
                                //equivalency[lg] = sml;
                                smal = smaller(sml, LabelArray[i - 1][j + 1]);
                                lag = larger(sml, LabelArray[i - 1][j + 1]);
                                equivalency[lg] = smal;
                                equivalency[lag] = smal;
                                LabelArray[i][j] = smal;
                            }

            if (Image[i][j] == 255)
                if (Image[i - 1][j] != 255)
                    if (Image[i - 1][j - 1] == 255)
                        if (Image[i - 1][j + 1] == 255)
                            if (Image[i][j - 1] == 255)
                            {
                                sml = smaller(LabelArray[i - 1][j - 1], LabelArray[i][j - 1]);
                                lg = larger(LabelArray[i - 1][j - 1], LabelArray[i][j - 1]);
                                //equivalency[lg] = sml;
                                smal = smaller(sml, LabelArray[i - 1][j + 1]);
                                lag = larger(sml, LabelArray[i - 1][j + 1]);
                                equivalency[lg] = smal;
                                equivalency[lag] = smal;
                                LabelArray[i][j] = smal;
                            }

            //case 3: if 2 neighbours have 1
            if (Image[i][j] == 255)
                if (Image[i - 1][j] == 255)
                    if (Image[i - 1][j - 1] == 255)
                        if (Image[i - 1][j + 1] != 255)
                            if (Image[i][j - 1] != 255)
                            {
                                int sml = smaller(LabelArray[i - 1][j], LabelArray[i - 1][j - 1]);
                                int lg = larger(LabelArray[i - 1][j], LabelArray[i - 1][j - 1]);
                                equivalency[lg] = sml;
                                LabelArray[i][j] = sml;
                            }

            if (Image[i][j] == 255)
                if (Image[i - 1][j] != 255)
                    if (Image[i - 1][j - 1] != 255)
                        if (Image[i - 1][j + 1] == 255)
                            if (Image[i][j - 1] == 255)
                            {
                                int sml = smaller(LabelArray[i][j - 1], LabelArray[i - 1][j + 1]);
                                int lg = larger(LabelArray[i][j - 1], LabelArray[i - 1][j + 1]);
                                equivalency[lg] = sml;
                                LabelArray[i][j] = sml;
                            }

            if (Image[i][j] == 255)
                if (Image[i - 1][j] != 255)
                    if (Image[i - 1][j - 1] == 255)
                        if (Image[i - 1][j + 1] != 255)
                            if (Image[i][j - 1] == 255)
                            {
                                int sml = smaller(LabelArray[i][j - 1], LabelArray[i - 1][j - 1]);
                                int lg = larger(LabelArray[i][j - 1], LabelArray[i - 1][j - 1]);
                                equivalency[lg] = sml;
                                LabelArray[i][j] = sml;
                            }

            if (Image[i][j] == 255)
                if (Image[i - 1][j] == 255)
                    if (Image[i - 1][j - 1] != 255)
                        if (Image[i - 1][j + 1] != 255)
                            if (Image[i][j - 1] == 255)
                            {
                                int sml = smaller(LabelArray[i][j - 1], LabelArray[i - 1][j]);
                                int lg = larger(LabelArray[i][j - 1], LabelArray[i - 1][j]);
                                equivalency[lg] = sml;
                                LabelArray[i][j] = sml;
                            }

            if (Image[i][j] == 255)
                if (Image[i - 1][j] != 255)
                    if (Image[i - 1][j - 1] == 255)
                        if (Image[i - 1][j + 1] == 255)
                            if (Image[i][j - 1] != 255)
                            {
                                int sml = smaller(LabelArray[i - 1][j - 1], LabelArray[i - 1][j + 1]);
                                int lg = larger(LabelArray[i - 1][j - 1], LabelArray[i - 1][j + 1]);
                                equivalency[lg] = sml;
                                LabelArray[i][j] = sml;
                            }

            if (Image[i][j] == 255)
                if (Image[i - 1][j] == 255)
                    if (Image[i - 1][j - 1] != 255)
                        if (Image[i - 1][j + 1] == 255)
                            if (Image[i][j - 1] != 255)
                            {
                                int sml = smaller(LabelArray[i - 1][j], LabelArray[i - 1][j + 1]);
                                int lg = larger(LabelArray[i - 1][j], LabelArray[i - 1][j + 1]);
                                equivalency[lg] = sml;
                                LabelArray[i][j] = sml;
                            }


        }
    }
    cout << "Ive completed 1st pass" << endl;

    //2nd pass
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (LabelArray[i][j] == i && equivalency[i] != 0)
            {
                //cout << "Equivalency b/w " << i << " and " << equivalency[i] << " has been resolved to label: " << equivalency[i] << endl;
                cout << "Label val: " << LabelArray[i][j];
                LabelArray[i][j] = equivalency[i];
                cout << " First label was " << i << " now its: " << equivalency[i];
            }

        }
    }


    cout << "Ive completed 2nd pass" << endl;
    //after assigning labels we consider the most number of labels as lesion

    int** sorted = sort2D(LabelArray, rows, cols);
    cout << "Ive sorted the array" << endl;

    int freqLabel = frequency(sorted, rows, cols);
    cout << "freq label is : " << freqLabel << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (LabelArray[i][j] == freqLabel)
            {
                Image[i][j] = 255;
            }
            else
                Image[i][j] = 0;
        }
    }
    cout << "Im going to display" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            img.at<uchar>(i, j) = Image[i][j];

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
    
    cout << "Im done" << endl;
    diceCof(gt, img);
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if (k == 's')
    {
        imwrite("Segmented Outputs/mIMD063.bmp", img);
    }
    
}
//
//int main()
//{
//    Mat img;
//    string image_path = samples::findFile("Segmented Outputs/mIMD063.bmp");
//    img = imread(image_path, IMREAD_GRAYSCALE);
//    if (img.empty())
//    {
//        cout << "Could not read the image: " << image_path << endl;
//        return 1;
//    }
//
//
//
//    ConnectedComponentsLabelling(img);
//
//
//    //int k = waitKey(0); // Wait for a keystroke in the window
//    //if (k == 's')
//    //{
//    //    imwrite("Segmented Outputs/mIMD002.bmp", img);
//    //}
//    return 0;
//}