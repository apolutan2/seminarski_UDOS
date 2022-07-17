#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <complex>


using namespace std;
using namespace cv;

class Histogram {
public:
    Mat calc_histogram(Mat scr) {
        Mat hist;
        hist = Mat::zeros(256, 1, CV_32F);
        scr.convertTo(scr, CV_32F);
        double value = 0;
        for (int i = 0; i < scr.rows; i++)
        {
            for (int j = 0; j < scr.cols; j++)
            {
                value = scr.at<float>(i, j);
                hist.at<float>(value) = hist.at<float>(value) + 1;
            }
        }
        return hist;
    }

    void plot_histogram(Mat histogram) {
        Mat histogram_image(400, 512, CV_8UC3, Scalar(0, 0, 0));
        Mat normalized_histogram;
        normalize(histogram, normalized_histogram, 0, 400, NORM_MINMAX, -1, Mat());

        for (int i = 0; i < 256; i++)
        {
            rectangle(histogram_image, Point(2 * i, histogram_image.rows - normalized_histogram.at<float>(i)),
                Point(2 * (i + 1), histogram_image.rows), Scalar(255, 0, 0));
        }

        namedWindow("Histogram", WINDOW_NORMAL);
        imshow("Histogram", histogram_image);
    }
};

Mat LBP(Mat ulaz)
{

    Mat Image(ulaz.rows, ulaz.cols, CV_8UC1);
    Mat lbp(ulaz.rows, ulaz.cols, CV_8UC1);

    if (ulaz.channels() == 3)
        cvtColor(ulaz, Image, COLOR_BGR2GRAY);

    unsigned center = 0;
    unsigned center_lbp = 0;

    for (int row = 1; row < Image.rows-1; row++)
    {
        for (int col = 1; col < Image.cols-1; col++)
        {
            center = Image.at<uchar>(row, col);
            center_lbp = 0;

            if (center <= Image.at<uchar>(row - 1, col - 1))
                center_lbp += 1;

            if (center <= Image.at<uchar>(row - 1, col))
                center_lbp += 2;

            if (center <= Image.at<uchar>(row - 1, col + 1))
                center_lbp += 4;

            if (center <= Image.at<uchar>(row, col - 1))
                center_lbp += 8;

            if (center <= Image.at<uchar>(row, col + 1))
                center_lbp += 16;

            if (center <= Image.at<uchar>(row + 1, col - 1))
                center_lbp += 32;

            if (center <= Image.at<uchar>(row + 1, col))
                center_lbp += 64;

            if (center <= Image.at<uchar>(row + 1, col + 1))
                center_lbp += 128;
            lbp.at<uchar>(row, col) = center_lbp;
        }
    }

             imshow("image LBP", lbp);

             imshow("grayscale",Image);


    return lbp;
}

int main()
{
    Mat image;
       image= imread("C:\\Users\\9470\\Desktop\\UDOS\\seminarski\\cat.png");
       LBP(image);
       Histogram H1;
       Mat hist = H1.calc_histogram(image);
       H1.plot_histogram(hist);

       waitKey();
       destroyAllWindows();

    return 0;
}
