/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2023 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    int result = 0;

    try {
        ::testing::InitGoogleTest(&argc, argv);

        result = RUN_ALL_TESTS();
    } catch (const std::exception &e) {
        std::cout << "Unit test crashed..." << e.what() << std::endl;
    }

    return result;
}