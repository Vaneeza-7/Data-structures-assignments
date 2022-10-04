#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/imgcodecs.hpp>
#include <iostream>
#include <stdio.h>
#include"source.cpp"

using namespace cv;
using namespace std;

class Equivalent
{
    int L1;
    int L2;
public:
    Equivalent()
    {
        L1 = 0;
        L2 = 0;
    }

    Equivalent(int label1, int label2)
    {
        L1 = label1;
        L2 = label2;
    }

    int getLabel1()
    {
        return L1;
    }

    int getLabel2()
    {
        return L2;
    }

};

int smaller(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int larger(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int* convertTo1D(int** arr, int cols, int rows)
{
    int index = 0;
    int n = rows * cols;
    int* oneD = new int[n];
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            oneD[index] = arr[i][j];
            index++;
        }
    }
    return oneD;
}

int** convertTo2D(int* arr, int rows, int cols)
{
    int index = 0;
    int n = rows * cols;
    int** twoD = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        twoD[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            twoD[i][j] = arr[index];
            index++;
        }
    }
    return twoD;
}

void bubbleSort(int* &arr, int size)
{
    int pass = 1;
    bool exchanges;
    do {
        exchanges = false;
        for (int i = 0; i < size - pass; i++)
            if (arr[i] > arr[i + 1]) {
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                exchanges = true;
            }
        pass++;
    } while (exchanges);

}

int mostFrequent(int* arr, int n)
{
    // code here
    int maxcount = 0;
    int element_having_max_freq;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j])
                count++;
        }

        if (count > maxcount) {
            maxcount = count;
            element_having_max_freq = arr[i];
        }
    }

    return element_having_max_freq;
}


int** ConnectedComponentsLabelling(int** Image, int rows, int cols)
{
    Equivalent* EQ = new Equivalent[cols];
    int L = 0; //labelIndex
    int** LabelArray = new int* [cols];  //array for storing labels
    for (int i = 0; i < cols; i++)
    {
        LabelArray[i] = new int[rows];
    }

    for (int i = 0; i < cols; i++)       //label for first pixel i.e. [0][0] index
    {
        for (int j = 0; j < rows; j++)
        {
            if (Image[0][0] > 0)
            {
                L++;
                LabelArray[0][0] = L;
            }
        }
    }
    try {
        //column-wise if labels are same then assign the previous label 
        for (int i = 1; i < cols-1; i++)           //0th row and any column excluding 0th column
        {
            for (int j = 0; j < rows; j++)         //label pixels in row j = 0
            {
                if (Image[i][0] > 0)
                {
                    if (Image[i][0] == Image[i - 1][0])
                    {
                        LabelArray[i][0] = LabelArray[i - 1][0];
                    }
                    if (Image[i][0] != Image[i - 1][0])
                    {
                        L++;
                        LabelArray[i][0] = L;
                    }
                }
            }
        }
    }
    catch (...)
    {
        cout << "Default Exception";
    }
    //row-wise if labels are same then assign the previous label 
    for (int i = 0; i < cols; i++)              //label pixels in col i=0
    {
        for (int j = 1; j < rows-1; j++)        //0th column and any row excluding 0th row 
        {
            if (Image[0][j] > 0 && Image[0][j] == Image[0][j-1])
            {
                LabelArray[0][j] = LabelArray[0][j-1];
            }
            if (Image[0][j] > 0 && Image[0][j] != Image[0][j-1])
            {
                L++;
                LabelArray[0][j] = L;
            }
        }
    }

    for (int i = 1; i < cols-1; i++)              //label pixels in col i=0
    {
        for (int j = 1; j < rows - 1; j++)        //0th column and any row excluding 0th row 
        {
            if (Image[i][j] > 0 )                   //if its a valid pixel
            {
                //if left pixel has same label but above pixel doesn't, then assign same label as left pixel
                if (Image[i][j] == Image[i - 1][j] && Image[i][j] != Image[i][j - 1])   
                {
                    LabelArray[i][j] = LabelArray[i - 1][j];
                }

                //if top pixel has same label but left pixel doesn't, then assign same label as of top pixel
                if (Image[i][j] != Image[i - 1][j] && Image[i][j] == Image[i][j - 1])
                {
                    LabelArray[i][j] = LabelArray[i][j-1];
                }

                //if both top and left pixels are not equal to current pixel then give new label
                if (Image[i][j] != Image[i - 1][j] && Image[i][j] != Image[i][j - 1])
                {
                    L++;
                    LabelArray[i][j] = L;
                }

                //if top and left pixels are same, labels of top and left are also same then set same label (eg top label) 
                if (Image[i][j] == Image[i - 1][j] && Image[i][j] == Image[i][j - 1] && LabelArray[i-1][j]==LabelArray[i][j-1])
                {
                    LabelArray[i][j] = LabelArray[i][j-1];
                }

                //if top and left pixels are same, but have different labels then assign smaller label
                if (Image[i][j] == Image[i - 1][j] && Image[i][j] == Image[i][j - 1] && LabelArray[i - 1][j] != LabelArray[i][j - 1])
                {
                    LabelArray[i][j] = smaller(LabelArray[i - 1][j], LabelArray[i][j - 1]);
                    //record equivalency by creating object of equivalence class inside array
                    EQ[i]= Equivalent(LabelArray[i - 1][j], LabelArray[i][j - 1]);
                }
            }
            /*if (Image[0][j] > 0 && Image[0][j] != Image[0][j - 1])
            {
                L++;
                LabelArray[0][j] = L;
            }*/
        }
    }
    //2nd pass
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (LabelArray[i][j] == EQ[i].getLabel1() || LabelArray[i][j] == EQ[i].getLabel2())
            {
                LabelArray[i][j] = smaller(EQ[i].getLabel1(), EQ[i].getLabel2());
            }
        }
    }

    //after assigning labels we consider the most number of labels as lesion
    int* temp = convertTo1D(LabelArray, cols, rows);
    int freqLabel = mostFrequent(temp, cols * rows);
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (LabelArray[i][j] == freqLabel)
            {
                Image[i][j] = 255;
            }
            else
                Image[i][j] = 0;
        }
    }

    return Image;
}

int main()
{
    Mat img;
    string image_path = samples::findFile("Segmented Outputs/mIMD002.bmp");
    img = imread(image_path, IMREAD_COLOR);
    if (img.empty())
    {
        cout << "Could not read the image: " << image_path << endl;
        return 1;
    }
     
    //taking an image matrix//
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
            ImageArray[i][j]=(int)img.at<uchar>(i, j);
            //x=(int)img.at<uchar>(i, j);
            //if (x == 255)
            //{
            //    cout << "Value of pixel" << "(" << i << "," << j << ")" << "=" << x << endl;
            //}//showing the values in console window//
        }
    }

   int** ModImage = ConnectedComponentsLabelling(ImageArray, height, width);
    /*Mat Image;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Image.at<uchar>(i, j) = ModImage[i][j] ;
        }
    }*/
    /*Mat A(height,width, CV_64F, ModImage);
    memcpy(A.data, ModImage, height * width * sizeof(int));

    imwrite("Segmented Outputs/my1.bmp", A);
    imshow("Display window", A);*/

    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if (k == 's')
    {
        imwrite("Segmented Outputs/mIMD002.bmp", img);
    }


   
    //int k = waitKey(0); // Wait for a keystroke in the window
    //if (k == 's')
    //{
    //    imwrite("Segmented Outputs/mIMD002.bmp", img);
    //}
    return 0;
}
