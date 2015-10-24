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
    cv::Mat wiggledDepth = cv::Mat::ones(_rgb.size(), CV_16U) * 65535;
    cv::Mat wiggleValue = cv::Mat::ones(_rgb.size(), CV_16S) * 32767;

    for (int32_t y = 0; y < _rgb.rows; ++y)
        for (int32_t x = 0; x < _rgb.cols; ++x)
            if (_depth.at<uint16_t>(y, x) != 0)
            {
                float wiggledPosition = (float)x + ((float)_depth.at<uint16_t>(y, x) - _wiggleDist) * _wiggleFactor;
                if (wiggledPosition >= 0 && wiggledPosition < _rgb.cols)
                {
                    if (wiggledDepth.at<uint16_t>(y, wiggledPosition) > _depth.at<unsigned char>(y, x))
                    {
                        wiggled.at<cv::Vec3b>(y, wiggledPosition) = _rgb.at<cv::Vec3b>(y, x);
                        wiggledDepth.at<uint16_t>(y, wiggledPosition) = _depth.at<uint16_t>(y, x);
                        wiggleValue.at<int16_t>(y, wiggledPosition) = wiggledPosition - x;
                    }
                }
            }

    // Filling the holes
    for (int32_t y = 0; y < _rgb.rows; ++y)
    {
        bool isHole {false};
        float previousWiggle = 0.f;
        float nextWiggle = 0.f;

        for (int32_t x = 0; x < _rgb.cols; ++x)
        {
            auto value = wiggleValue.at<int16_t>(y, x);
            int holeLength = 0;

            if (value != 32767)
            {
                previousWiggle = value;
                isHole = true;
                continue;
            }
            else
            {
                // Find the next wiggle value
                for (int32_t xx = x; xx < _rgb.cols; ++xx)
                {
                    value = wiggleValue.at<int16_t>(y, xx);
                    if (value != 32767)
                    {
                        nextWiggle = value;
                        break;
                    }
                    holeLength++;
                }
            }

            for (int32_t xx = x; xx < x + holeLength; ++xx)
            {
                float newWiggle = previousWiggle * (holeLength - (float)(xx - x)) / (float)holeLength
                                + nextWiggle * (float)(xx - x) / (float)holeLength;
                if (xx - newWiggle >= 0 || xx - newWiggle < _rgb.cols)
                    wiggled.at<cv::Vec3b>(y, xx) = _rgb.at<cv::Vec3b>(y, xx - newWiggle);
            }

            x += holeLength;
        }
    }


    return wiggled;
}
