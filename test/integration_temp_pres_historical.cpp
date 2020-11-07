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

////////////////////////////////////////////////////////////////////////////////
// Tests 24-hour and 6-hour min/max temperature groups and pressure tendency 
// group specified in remarks
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationHistoricalPressure, pressureTendencyTrend) {
    Simple result;
    Historical historical;

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK 50132=");
    historical = Historical();
    historical.pressureChange3h = Pressure {132, Pressure::Unit::TENTHS_HPA};
    historical.pressureTendency = 
        Historical::PressureTendency::INCREASING_THEN_DECREASING;
    historical.pressureTrend = 
        Historical::PressureTrend::HIGHER_OR_SAME;
    EXPECT_EQ(result.historical, historical);

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK 51132=");
    historical = Historical();
    historical.pressureChange3h = Pressure {132, Pressure::Unit::TENTHS_HPA};
    historical.pressureTendency = 
        Historical::PressureTendency::INCREASING_MORE_SLOWLY;
    historical.pressureTrend = 
        Historical::PressureTrend::HIGHER;
    EXPECT_EQ(result.historical, historical);

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK 52132=");
    historical = Historical();
    historical.pressureChange3h = Pressure {132, Pressure::Unit::TENTHS_HPA};
    historical.pressureTendency = 
        Historical::PressureTendency::INCREASING;
    historical.pressureTrend = 
        Historical::PressureTrend::HIGHER;
    EXPECT_EQ(result.historical, historical);

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK 53132=");
    historical = Historical();
    historical.pressureChange3h = Pressure {132, Pressure::Unit::TENTHS_HPA};
    historical.pressureTendency = 
        Historical::PressureTendency::INCREASING_MORE_RAPIDLY;
    historical.pressureTrend = 
        Historical::PressureTrend::HIGHER;
    EXPECT_EQ(result.historical, historical);

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK 54132=");
    historical = Historical();
    historical.pressureChange3h = Pressure {132, Pressure::Unit::TENTHS_HPA};
    historical.pressureTendency = 
        Historical::PressureTendency::STEADY;
    historical.pressureTrend = 
        Historical::PressureTrend::SAME;
    EXPECT_EQ(result.historical, historical);

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK 55132=");
    historical = Historical();
    historical.pressureChange3h = Pressure {132, Pressure::Unit::TENTHS_HPA};
    historical.pressureTendency = 
        Historical::PressureTendency::DECREASING_THEN_INCREASING;
    historical.pressureTrend = 
        Historical::PressureTrend::LOWER_OR_SAME;
    EXPECT_EQ(result.historical, historical);

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK 56132=");
    historical = Historical();
    historical.pressureChange3h = Pressure {132, Pressure::Unit::TENTHS_HPA};
    historical.pressureTendency = 
        Historical::PressureTendency::DECREASING_MORE_SLOWLY;
    historical.pressureTrend = 
        Historical::PressureTrend::LOWER;
    EXPECT_EQ(result.historical, historical);

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK 57132=");
    historical = Historical();
    historical.pressureChange3h = Pressure {132, Pressure::Unit::TENTHS_HPA};
    historical.pressureTendency = 
        Historical::PressureTendency::DECREASING;
    historical.pressureTrend = 
        Historical::PressureTrend::LOWER;
    EXPECT_EQ(result.historical, historical);

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK 58132=");
    historical = Historical();
    historical.pressureChange3h = Pressure {132, Pressure::Unit::TENTHS_HPA};
    historical.pressureTendency = 
        Historical::PressureTendency::DECREASING_MORE_RAPIDLY;
    historical.pressureTrend = 
        Historical::PressureTrend::LOWER;
    EXPECT_EQ(result.historical, historical);

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK 59132=");
    historical = Historical();
    EXPECT_EQ(result.historical, historical);

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK 5/132=");
    historical = Historical();
    historical.pressureChange3h = Pressure {132, Pressure::Unit::TENTHS_HPA};
    EXPECT_EQ(result.historical, historical);

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK 53///=");
    historical = Historical();
    historical.pressureTendency = 
        Historical::PressureTendency::INCREASING_MORE_RAPIDLY;
    historical.pressureTrend = 
        Historical::PressureTrend::HIGHER;
    EXPECT_EQ(result.historical, historical);

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK 5////=");
    historical = Historical();
    EXPECT_EQ(result.historical, historical);
}

// TODO 24-hour and 6-hour min/max