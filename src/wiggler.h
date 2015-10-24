/*
 * Copyright (C) 2015 Emmanuel Durand
 *
 * This file is part of Wiggler.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * blobserver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Wiggler.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <opencv2/opencv.hpp>

/*************/
class Wiggler
{
    public:
        Wiggler();
        ~Wiggler();

        void setWiggleDist(float value) {_wiggleDist = std::max(0.f, value);}
        void setWiggleFactor(float value) {_wiggleFactor = value;}
        
        bool setInputs(cv::Mat rgb, cv::Mat depth);
        cv::Mat doWiggle();

    private:
        cv::Mat _rgb;
        cv::Mat _depth;

        float _wiggleDist {0.f};
        float _wiggleFactor {0.f};
};
