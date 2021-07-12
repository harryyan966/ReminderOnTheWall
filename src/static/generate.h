#pragma once
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <string>
using namespace cv;
using namespace std;

namespace generate
{
    // under the same dir or its sub dir only 
    void change_wallpaper(string base, const char *fname);

    class ChangeWallpaper
    {
        string fname;
        cv::Mat *mat;
        int font;

        static void GetStringSize(HDC hDC, const char* str, int* w, int* h);
    public:
        ChangeWallpaper() : fname(""), mat(nullptr), font(cv::FONT_HERSHEY_DUPLEX) {}
        ChangeWallpaper(const string &full_path);
        ChangeWallpaper(const string &runtime_path, const string &file_rel_path);
        ~ChangeWallpaper();

        inline const cv::Mat& getMat(void) const { return *mat; }

        void save(const string& argv, const string& img);
        inline void putTextZH(const char* str, Point org, Scalar color, int fontSize,
            const char* fn = "Arial", bool italic = false, bool underline = false) {
            putTextZH(*mat, str, org, color, fontSize, fn, italic, underline);
        }
        inline void changeBrightness(int value) { mat->convertTo(*mat, -1, 1, value); }
        inline void resize(int width, int height) {
            cv::resize(*mat, *mat, cv::Size(width, height), 0, 0, INTER_LINEAR);
        }
        inline void changeWallpaper(const string &argv, const string &img) {
            string path = getBaseName(argv.c_str());
            path += img;
            SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0,
                (PVOID)path.c_str(),
                SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
        }

        // get base name
        static string getBaseName(const char* argv);
        // put chinese character on cv::Mat
        static void putTextZH(Mat& dst, const char* str, Point org, Scalar color, int fontSize,
            const char* fn = "Arial", bool italic = false, bool underline = false);
    };
}
