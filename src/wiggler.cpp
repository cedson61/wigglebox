#include "wiggler.h"

using namespace std;

/*************/
Wiggler::Wiggler()
{
}

/*************/
Wiggler::~Wiggler()
{
}

/*************/
bool Wiggler::setInputs(cv::Mat rgb, cv::Mat depth)
{
    if (rgb.cols != depth.cols || rgb.rows != depth.rows)
    {
        cout << "Inputs have not the same size!" << endl;
        return false;
    }

    _rgb = rgb.clone();
    _depth = depth.clone();

    return true;
}

/*************/
cv::Mat Wiggler::doWiggle()
{
    cv::Mat wiggled = cv::Mat::zeros(_rgb.size(), CV_8UC3);
    cv::Mat wiggledDepth = cv::Mat::ones(_rgb.size(), CV_8U) * 255;

    for (int32_t y = 0; y < _rgb.rows; ++y)
    {
        for (int32_t x = 0; x < _rgb.cols; ++x)
        {
            if (_depth.at<unsigned char>(y, x) != 0)
            {
                float wiggledPosition = (float)x + ((float)_depth.at<uint8_t>(y, x) - _wiggleDist) * _wiggleFactor;
                if (wiggledPosition >= 0 && wiggledPosition < _rgb.cols)
                {
                    if (wiggledDepth.at<uint8_t>(y, wiggledPosition) > _depth.at<unsigned char>(y, x))
                    {
                        wiggled.at<cv::Vec3b>(y, wiggledPosition) = _rgb.at<cv::Vec3b>(y, x);
                        wiggledDepth.at<uint8_t>(y, wiggledPosition) = _depth.at<unsigned char>(y, x);
                    }
                }
            }
        }
    }

    return wiggled;
}
