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
// Tests cover snow depth on ground, water equivalent of snow on ground, and
// 'snow increasing rapidly' groups
////////////////////////////////////////////////////////////////////////////////

TEST(PrecipitationSnow, snowDepthOnGround) {
    static const auto rawReport =
        "METAR ZZZZ 241503Z /////KT ////SM RMK 4/014=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{24, 15, 03};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.snowDepthOnGround = Precipitation {14, Precipitation::Unit::IN};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(PrecipitationSnow, waterEquivalentOfSnowOnGround) {
    static const auto rawReport =
        "METAR ZZZZ 241503Z /////KT ////SM RMK 933021=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{24, 15, 03};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.snowWaterEquivalent = 
        Precipitation {210, Precipitation::Unit::HUNDREDTHS_IN};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(PrecipitationSnow, snowIncreasingRapidly) {
    static const auto rawReport =
        "METAR ZZZZ 241503Z /////KT ////SM RMK SNINCR 1/9=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{24, 15, 03};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.snowIncreasingRapidly = true;
    EXPECT_EQ(result.current, refCurrent);

    Historical refHistorical;
    refHistorical.snowfallIncrease1h = 
        Precipitation {1, Precipitation::Unit::IN};
    refHistorical.snowfallTotal = 
        Precipitation {9, Precipitation::Unit::IN};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(PrecipitationSnow, snowIncreasingRapidlyNoDetails) {
    static const auto rawReport =
        "METAR ZZZZ 241503Z /////KT ////SM RMK SNINCR=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{24, 15, 03};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.snowIncreasingRapidly = true;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

