#pragma once
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <string>
using namespace cv;
using namespace std;

void GetStringSize(HDC hDC, const char* str, int* w, int* h);
void putTextZH(Mat &dst, const char* str, Point org, Scalar color, int fontSize,
    const char *fn = "Arial", bool italic = false, bool underline = false);

inline int changeImage()
{
    cv::Mat img = cv::imread("C:\\1.png", cv::ImreadModes::IMREAD_COLOR);
    int font = cv::FONT_HERSHEY_DUPLEX;
    putTextZH(img, "ΩÒÃÏ «°£°£°£", cv::Point(50, img.rows / 2 - 50), cv::Scalar(0, 0, 0), 72);
    cv::imshow("img", img);
    cv::waitKey();
    return 0;
}

