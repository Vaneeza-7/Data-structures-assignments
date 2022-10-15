                              


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
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            oneD[i*cols + j] = arr[i][j];
            
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

void bubbleSort(int*& arr, int size)
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

void sort2D(int**& arr, int n, int m)
{
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
}

//int frequency(int** arr, int rows, int cols)
//{
//    int maxCount = 1;
//    int count = 1;
//    int freq = 0;
//    for (int i = 0; i < rows; i++)
//    {
//        for (int j = 1; j < cols; j++)
//        {
//            if (arr[i][j] == arr[i][j - 1])
//                count++;
//            else
//                count = 1;
//            if (count > maxCount) {
//                maxCount = count;
//                freq = arr[i][j - 1];
//            }
//        }
//    }
//
//    return freq;
//}
//int mostFrequent(int* arr, int n)
//{
//    // code here
//    int maxcount = 0;
//    int element_having_max_freq=0;
//    for (int i = 0; i < n; i++) {
//        int count = 0;
//        for (int j = 0; j < n; j++) {
//            if (arr[i] == arr[j])
//                count++;
//        }
//
//        if (count > maxcount) {
//            maxcount = count;
//            cout << maxcount<<endl;
//            element_having_max_freq = arr[i];
//            cout << arr[i];
//        }
//    }
//
//    return element_having_max_freq;
//}

int frequency(int** Label, int rows, int cols) {
    int  frequency = 0, label = 0;

    int** freq = new int* [rows];
    int maj_lesion = 0, maj_lesion_freq = 0;
    int* lesion = new int[cols];
    for (int i = 0; i < rows; i++) {
        freq[i] = new int[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            frequency = 1;

            label = Label[i][j];

            if (freq[i][j] != 0) {

                if (Label[i][j] != 0) {
                    for (int x = 0; x < rows; x++) {
                        for (int y = 0; y < cols; y++) {


                            if ((i == x) && (j == y)) {
                                continue;
                            }
                            if (Label[i][j] == Label[x][y]) {
                                freq[x][y] = 0;
                                frequency++;
                            }

                        }

                    }
                    lesion[label] = frequency;
                }
            }
        }
    }

    for (int i = 0; i < cols; i++) {
        if (lesion[i] > maj_lesion_freq) {
            maj_lesion_freq = lesion[i];
            maj_lesion = i;
        }
    }

    return maj_lesion;

}

void ConnectedComponentsLabelling(Mat img)
{
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
            //x=(int)img.at<uchar>(i, j);
            //if (x == 255)
            //{
            //    cout << "Value of pixel" << "(" << i << "," << j << ")" << "=" << x << endl;
            //}//showing the values in console window//
        }
    }

    
    Equivalent* EQ = new Equivalent[cols];
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

    for (int i = 1; i < rows - 1; i++)              //label pixels in col i=0
    {
        for (int j = 1; j < cols - 1; j++)        //0th column and any row excluding 0th row 
        {
            if(Image[i][j]==255)
                if (LabelArray[i - 1][j] == 0)
                    if (LabelArray[i][j - 1] == 0)
                        if (LabelArray[i - 1][j - 1] == 0)
                            if (LabelArray[i - 1][j + 1] == 0)
                            {
                                L++;
                                LabelArray[i][j] = L;
                            }

                //else if (LabelArray[i - 1][j] == LabelArray[i][j - 1])
                //{
                //    LabelArray[i][j] = LabelArray[i - 1][j];
                //}
                //else if (LabelArray[i - 1][j] == LabelArray[i - 1][j - 1])
                //{
                //    LabelArray[i][j] = LabelArray[i - 1][j];
                //}
                //else if (LabelArray[i - 1][j] == LabelArray[i - 1][j + 1])
                //{
                //    LabelArray[i][j] = LabelArray[i - 1][j];
                //}
                //else
                //    LabelArray[i][j] = 0;
            if (Image[i][j] == 255)
                if (LabelArray[i - 1][j] == LabelArray[i][j - 1])
                    if (LabelArray[i - 1][j] == LabelArray[i - 1][j - 1])
                        if (LabelArray[i - 1][j] == LabelArray[i][j + 1])
                        {
                            LabelArray[i][j] = LabelArray[i - 1][j];
                        }

            if (Image[i][j] == 255)
                if (LabelArray[i - 1][j] != LabelArray[i][j - 1])
                    if (LabelArray[i - 1][j] != LabelArray[i - 1][j - 1])
                        if (LabelArray[i - 1][j] != LabelArray[i][j + 1])
                        {
                            int sml = smaller(LabelArray[i - 1][j], LabelArray[i][j - 1]);
                            sml = smaller(sml, LabelArray[i - 1][j - 1]);
                            LabelArray[i][j] = smaller(sml, LabelArray[i][j + 1]);
                            EQ[i] = Equivalent(LabelArray[i][j - 1], LabelArray[i - 1][j - 1]);
                        }
            

                ////if top pixel has same label but left pixel doesn't, then assign same label as of top pixel
                //if (Image[i][j] != Image[i - 1][j] && Image[i][j] == Image[i][j - 1])
                //{
                //    LabelArray[i][j] = LabelArray[i][j - 1];
                //}

                ////if both top and left pixels are not equal to current pixel then give new label
                //if (Image[i][j] != Image[i - 1][j] && Image[i][j] != Image[i][j - 1])
                //{
                //    L++;
                //    LabelArray[i][j] = L;
                //}

                ////if top and left pixels are same, labels of top and left are also same then set same label (eg top label) 
                //if (Image[i][j] == Image[i - 1][j] && Image[i][j] == Image[i][j - 1] && LabelArray[i - 1][j] == LabelArray[i][j - 1])
                //{
                //    LabelArray[i][j] = LabelArray[i][j - 1];
                //}

                ////if top and left pixels are same, but have different labels then assign smaller label
                //if (Image[i][j] == Image[i - 1][j] && Image[i][j] == Image[i][j - 1] && LabelArray[i - 1][j] != LabelArray[i][j - 1])
                //{
                //    LabelArray[i][j] = smaller(LabelArray[i - 1][j], LabelArray[i][j - 1]);
                //    //record equivalency by creating object of equivalence class inside array
                //    EQ[i] = Equivalent(LabelArray[i - 1][j], LabelArray[i][j - 1]);
                //}

               /*if (Image[0][j] > 0 && Image[0][j] != Image[0][j - 1])
        {
            L++;
            LabelArray[0][j] = L;
        }*/
                  
        }
    }
    //2nd pass
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (LabelArray[i][j] == EQ[i].getLabel1() || LabelArray[i][j] == EQ[i].getLabel2())
            {
                LabelArray[i][j] = smaller(EQ[i].getLabel1(), EQ[i].getLabel2());
            }
        }
    }

    //after assigning labels we consider the most number of labels as lesion
   // int* temp = convertTo1D(LabelArray, cols, rows);
    //int n = rows * cols;
    //int freqLabel = mostFrequent(temp, n);
    //sort2D(LabelArray, rows, cols);
    int freqLabel = frequency(LabelArray, rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (LabelArray[i][j] != freqLabel)
            {
                LabelArray[i][j] =0;
            }
           else
                LabelArray[i][j] = 255;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
                img.at<uchar>(i, j) = LabelArray[i][j];
           
            //x=(int)img.at<uchar>(i, j);
            //if (x == 255)
            //{
            //    cout << "Value of pixel" << "(" << i << "," << j << ")" << "=" << x << endl;
            //}//showing the values in console window//
        }
    }

    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if (k == 's')
    {
        imwrite("Segmented Outputs/mIMD002.bmp", img);
    }

}

int main()
{
    Mat img;
    string image_path = samples::findFile("Segmented Outputs/mIMD002.bmp");
    img = imread(image_path, IMREAD_GRAYSCALE);
    if (img.empty())
    {
        cout << "Could not read the image: " << image_path << endl;
        return 1;
    }

    

    ConnectedComponentsLabelling(img);


    //int k = waitKey(0); // Wait for a keystroke in the window
    //if (k == 's')
    //{
    //    imwrite("Segmented Outputs/mIMD002.bmp", img);
    //}
    return 0;
}