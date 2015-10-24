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

#include "wigglebox.h"

#include <spawn.h>

using namespace std;

/*************/
void WiggleBox::parseArguments(int argc, char** argv)
{
    for (int i = 1; i < argc;)
    {
        if ("--help" == string(argv[i]) || "-h" == string(argv[i]))
        {
            cout << "Wigglebox engine - Where the fun is side-shifted!" << endl;
            cout << "Basic usage: wigglebox" << endl;
            exit(0);
        }

        ++i;
    }
}

/*************/
WiggleBox::WiggleBox(int argc, char** argv)
{
    parseArguments(argc, argv);

    // Load camera
    _camera = unique_ptr<RgbdCamera>(new RgbdCamera());
}

/*************/
WiggleBox::~WiggleBox()
{
}

/*************/
void WiggleBox::run()
{
    while(_state.run)
    {
        auto frameBegin = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

        if (_camera->isReady())
        {
            _camera->grab();

            cv::Mat depthMask = _camera->retrieveDepthMask();

            auto rgbFrame = _camera->retrieveRGB();
            cv::imshow("img", rgbFrame);
        }

        // Handle keyboard
        // TODO: more precise loop timing
        auto frameEnd = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        long frameDuration = 33; // 33ms per frame, so 30fps
        auto sleepTime = std::max(1l, frameDuration - ((long)frameEnd - (long)frameBegin));

        short key = cv::waitKey(sleepTime);
        processKeyEvent(key);
    }

    return;
}

/*************/
void WiggleBox::processKeyEvent(short key)
{
    switch (key)
    {
    default:
        //cout << "Pressed key: " << key << endl;
        break;
    case 27: // Escape
        _state.run = false;
        break;
    }
}

/*************/
int main(int argc, char** argv)
{
    WiggleBox wigglebox(argc, argv);
    wigglebox.run();
    return 0;
}
