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

int main()
{
void glcm(Mat &);
//Mat img=imread("C:\\Users\\9470\\Desktop\\UDOS\\seminarski\\platno.png");
//Mat img=imread("C:\\Users\\9470\\Desktop\\UDOS\\seminarski\\plocica.png");
Mat img=imread("C:\\Users\\9470\\Desktop\\UDOS\\seminarski\\cat.png");

glcm(img);
namedWindow("Image");
imshow("Image",img);
waitKey(0);
return 0;

}



void glcm(Mat &img)
{
  float energy=0,contrast=0,homogenity=0,entropy=0;
  int row=img.rows,col=img.cols;
  Mat gl=Mat::zeros(256,256,CV_32FC1);

  //kreiranje glcm matrice sa 256 nivoa,radius=1, u horizontalnom smjeru
  for(int i=0;i<row;i++)
     for(int j=0;j<col-1;j++)
         gl.at<float>(img.at<uchar>(i,j),img.at<uchar>(i,j+1))=gl.at<float>(img.at<uchar>(i,j),img.at<uchar>(i,j+1))+1;

 // normalizacija glcm matrice za računanje parametara
  gl=gl+gl.t();
  gl=gl/sum(gl)[0];


 for(int i=0;i<256;i++)
    for(int j=0;j<256;j++)
        {
        energy=energy+gl.at<float>(i,j)*gl.at<float>(i,j);
        contrast=contrast+(i-j)*(i-j)*gl.at<float>(i,j);
        homogenity=homogenity+gl.at<float>(i,j)/(1+abs(i-j));
        if(gl.at<float>(i,j)!=0)
          entropy=entropy-gl.at<float>(i,j)*log10(gl.at<float>(i,j));
        }

 cout<<"Energija="<<energy<<endl;
 cout<<"Kontrast="<<contrast<<endl;
 cout<<"Homogenost="<<homogenity<<endl;
 cout<<"Entropija="<<entropy<<endl;
}
