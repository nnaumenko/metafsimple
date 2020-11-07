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

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK PRESRR=");
    historical = Historical();
    historical.pressureTendency = 
        Historical::PressureTendency::RISING_RAPIDLY;
    historical.pressureTrend = 
        Historical::PressureTrend::UNKNOWN;
    EXPECT_EQ(result.historical, historical);

    result = metafsimple::simplify("METAR ZZZZ 070800Z /////KT RMK PRESFR=");
    historical = Historical();
    historical.pressureTendency = 
        Historical::PressureTendency::FALLING_RAPIDLY;
    historical.pressureTrend = 
        Historical::PressureTrend::UNKNOWN;
    EXPECT_EQ(result.historical, historical);

}

TEST(IntegrationHistoricalTemperature, minMax24hour) {
    static const auto rawReport =
        "METAR ZZZZ 071135Z /////KT RMK 401001015="; 
        // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{7, 11, 35};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.temperatureMax24h = 
        Temperature {100, Temperature::Unit::TENTH_C};
    refHistorical.temperatureMin24h = 
        Temperature {-15, Temperature::Unit::TENTH_C};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());    
    EXPECT_EQ(result.current, Current());    
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationHistoricalTemperature, minMax6hour) {
    static const auto rawReport =
        "METAR ZZZZ 071135Z /////KT RMK 10142 20012="; 
        // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{7, 11, 35};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.temperatureMin6h = 
        Temperature {12, Temperature::Unit::TENTH_C};
    refHistorical.temperatureMax6h = 
        Temperature {142, Temperature::Unit::TENTH_C};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());    
    EXPECT_EQ(result.current, Current());    
    EXPECT_EQ(result.forecast, Forecast());    
}

