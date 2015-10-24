/*
 * Copyright (C) 2015 Emmanuel Durand
 *
 * This file is part of WiggleBox.
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
 * along with WiggleBox.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <opencv2/opencv.hpp>

#include "./rgbdCamera.h"

/*************/
class WiggleBox
{
    public:
        WiggleBox(int argc, char** argv);
        ~WiggleBox();

        void run();

    private:
        struct State
        {
            bool run {true};
        } _state;

        std::unique_ptr<RgbdCamera> _camera;

        void parseArguments(int argc, char** argv);
        void processKeyEvent(short key);
};
