/*    hough.cpp - class source for hough transform algorithm that
 *                    preforms hough transform to find the center
 *                    of the rplidar data
 *
 *    Carnegie Mellon University
 *    Authors: Mohammadreza Mousei
 *    Contact: mmousaei@andrew.cmu.edu
 *
 */

#include "hough.h"

std::vector<double> Hough::initializeHough(std::vector<std::pair<double, double>> *cartesian)
{
  std::vector<double> res;
  int vsize = cartesian->size();
  double maxHeight = 2*vsize*sqrt(2) + 1;
  double maxWidth = 180;

  double d = 0;
  double a, b;
  int MaxH = 0;
  int a_int, b_int, r_int;
  int d_ind = 0;
  double x_min = 1000, x_max = 0, y_min = 1000, y_max = 0;
  int r_min = 350, r_max = 410;//30 in config
  // double r_inc = 0.001, a_inc = 0.001, b_inc = 0.001;
  double r_hough, a_hough, b_hough;
  double avg_x = 0, avg_y = 0, sum_cnt = 0;
  for(int i = 0; i < cartesian->size(); i++)
  {
    if(!std::isinf(cartesian->at(i).first))
    {
      if(cartesian->at(i).first < x_min) x_min = cartesian->at(i).first;
      if(cartesian->at(i).first > x_max && cartesian->at(i).first < 1) x_max = cartesian->at(i).first;
      if(cartesian->at(i).second < y_min) y_min = cartesian->at(i).second;
      if(cartesian->at(i).second > y_max && cartesian->at(i).second < 1) y_max = cartesian->at(i).second;
      avg_x += cartesian->at(i).first - 0.375;
      avg_y += cartesian->at(i).second;
      sum_cnt++;
    }
  }
  avg_x /= sum_cnt;
  avg_y /= sum_cnt;

  std::cout << "x:  " << avg_x << '\n';
  std::cout << "y:  " << avg_y << '\n';

  int x_min_int, x_max_int, y_min_int, y_max_int;

  x_min_int = x_min*1000;
  x_max_int = x_max*1000;
  y_min_int = y_min*1000;
  y_max_int = y_max*1000;

  int width = x_max_int - x_min_int + 1;
  int height = y_max_int - y_min_int + 1;

  std::cout << x_min_int << '\n';
  std::cout << x_max_int << '\n';
  std::cout << y_min_int << '\n';
  std::cout << y_max_int << '\n';


  // // std::vector<std::vector<std::vector<int>>> houghArray(asize, std::vector<std::vector<int>>(bsize, std::vector<int>(rsize)));


  static int houghArray[3000][3000][100];
  memset(houghArray,0,sizeof(houghArray));



    for(int i = 0; i < vsize; i++)
    {
      for(int r = r_min; r < r_max; r++)
      {
        for(int theta = 0; theta < 360; theta++)
        {
          if(!std::isinf(cartesian->at(i).first))
          {
            a_int = (int) cartesian->at(i).first*1000 + r*cos((double) theta * 3.1415 / 180) - x_min_int + r;
            b_int = (int) cartesian->at(i).second*1000 + r*sin((double) theta * 3.1415 / 180) - y_min_int + r;
            r_int = r - r_min;
            // std::cout << "a = "<< a_int << '\n';
            // std::cout << "b = "<< b_int << '\n';
            // std::cout << "r = "<< r_int << '\n';

            if(a_int >=0 && a_int < 1000 && b_int >=0 && b_int < 1000 && r_int >=0 && r_int < 100)
            {
              houghArray[a_int][b_int][r_int]++;
              if(houghArray[a_int][b_int][r_int] > MaxH)
              {
                MaxH = houghArray[a_int][b_int][r_int];
                r_hough = r_int;
                a_hough = a_int;
                b_hough = b_int;
              }
            }
          }
        }
      }
    }
  //
  res.push_back((a_hough + x_min_int)/1000);
  res.push_back((b_hough + y_min_int)/1000);
  res.push_back((r_hough + r_min)/1000);

// res.push_back(1);
return res;
}

void Hough::convertToMat(std::vector<std::pair<double, double>> *cartesian)
{

  double x_min = 1000, x_max = 0, y_min = 1000, y_max = 0;
  double r_min = 0.35, r_max = 0.41;//30 in config
  double avg_x = 0, avg_y = 0, sum_cnt = 0;
  int x_min_int, x_max_int, y_min_int, y_max_int;

  for(int i = 0; i < cartesian->size(); i++)
  {
    if(!std::isinf(cartesian->at(i).first))
    {
      if(cartesian->at(i).first < x_min) x_min = cartesian->at(i).first;
      if(cartesian->at(i).first > x_max && cartesian->at(i).first < 1) x_max = cartesian->at(i).first;
      if(cartesian->at(i).second < y_min) y_min = cartesian->at(i).second;
      if(cartesian->at(i).second > y_max && cartesian->at(i).second < 1) y_max = cartesian->at(i).second;
      avg_x += cartesian->at(i).first;
      avg_y += cartesian->at(i).second;
      sum_cnt++;
    }
  }
  avg_x /= sum_cnt;
  avg_y /= sum_cnt;

  x_min_int = x_min*1000;
  x_max_int = x_max*1000;
  y_min_int = y_min*1000;
  y_max_int = y_max*1000;

  int width = x_max_int - x_min_int + 1;
  int height = y_max_int - y_min_int + 1;


  cv::Mat Matrix(width, height, CV_64F, cv::Scalar(0));
  // std::cout << x_min_int << '\n';
  // std::cout << x_max_int << '\n';
  // std::cout << y_min_int << '\n';
  // std::cout << y_max_int << '\n';
  // std::cout << Matrix.cols << '\n';
  // std::cout << Matrix.rows << '\n';

  int x_temp, y_temp;

  for(int i = 0; i < cartesian->size(); i++)
  {
    x_temp = cartesian->at(i).first * 1000 - x_min_int;
    y_temp = cartesian->at(i).second * 1000 - y_min_int;
    if(x_temp < width  && y_temp < height && x_temp >= 0 && y_temp >= 0)
    {
      Matrix.at<double>(y_temp, x_temp) = 1;
    }
  }
  cv::Mat out;
  // cv::cvtColor(Matrix, out, cv::COLOR_GRAY2BGR);

  std::vector<cv::Vec3f> circles;
  cv::Mat src = cv::imread("img.jpg", 0);
  cv::Mat src_gray;
  cv::medianBlur(src, src_gray,1);

  cv::HoughCircles(src, circles, CV_HOUGH_GRADIENT, 1,
               src.rows/16,  // change this value to detect circles with different distances to each other
               100, 30, 1, 30 // change the last two parameters
          // (min_radius & max_radius) to detect larger circles
  );
//   cv::HoughCircles(src, circles, CV_HOUGH_GRADIENT, 1, 10,
//                  100, 30, 1, 30 // change the last two parameters
//                                 // (min_radius & max_radius) to detect larger circles
// );

  // std::cout << Matrix.type() << '\n';

  // std::cout << circles.size() << '\n';
  // for( size_t i = 0; i < circles.size(); i++ )
  // {
  //      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
  //      int radius = cvRound(circles[i][2]);
  //      // draw the circle center
  //      circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
  //      // draw the circle outline
  //      circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );
  // }

  //
  // for(int i = 0; i < width; i++)
  // {
  //   for(int j = 0; j < height; j++)
  //   {
  //     x_temp = i + x_min_int;
  //     y_temp = j + y_min_int;
  //
  //     Matrix.at<double>(j, i) = 0;
  //   }
  // }



     cv::namedWindow("Circle");
     cv::imshow("Circle", Matrix);
     cv::waitKey(0);


}
