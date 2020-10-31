/*
* Copyright (C) 2020 Nick Naumenko (https://gitlab.com/nnaumenko,
* https:://github.com/nnaumenko)
* All rights reserved.
* This software may be modified and distributed under the terms
* of the MIT license. See the LICENSE file for details.
*/

#include "comparisons.hpp"
#include "gtest/gtest.h"
#include "metafsimple.hpp"

using namespace metafsimple;

// Note: operator < required to use Runway in std::set
TEST(Comparisons, runwayLess) {
    Runway r27 {27, Runway::Designator::NONE};
    Runway r27r {27, Runway::Designator::RIGHT};
    Runway r26 {26, Runway::Designator::NONE};
    EXPECT_LT(r26, r27);
    EXPECT_LT(r27, r27r);
}

// TODO: Temperature
// TODO: Speed
// TODO: Distance
// TODO: Height
// TODO: Pressure
// TODO: Precipitation
// TODO: WaveHeight