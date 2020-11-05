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
// Multiple values for a runway or direction in aerodrome data
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationAerodromeMultiple, runway) {
    static const auto rawReport =
        "METAR ZZZZ 040310Z /////KT //// R27C/0///// RMK CIG 008 RWY27C=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{4, 3, 10};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Aerodrome refAerodrome;
    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways.back().runway = Runway{27, Runway::Designator::CENTER};
    refAerodrome.runways.back().ceiling = Ceiling{
        Height{800, Height::Unit::FEET},
        Height(),
        Height()};
    refAerodrome.runways.back().deposits = 
        Aerodrome::RunwayDeposits::CLEAR_AND_DRY;
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationAerodromeMultiple, direction) {
    static const auto rawReport =
        "METAR ZZZZ 040310Z /////KT //// RMK CIG 008 NW VIS NW 3=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{4, 3, 10};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Aerodrome refAerodrome;
    refAerodrome.directions.push_back(Aerodrome::DirectionData());
    refAerodrome.directions.back().cardinalDirection = 
        CardinalDirection::NW;
    refAerodrome.directions.back().ceiling = Ceiling{
        Height{800, Height::Unit::FEET},
        Height(),
        Height()};
    refAerodrome.directions.back().visibility = DistanceRange{
        Distance{Distance::Details::EXACTLY, 3, Distance::Unit::STATUTE_MILES},
        Distance(),
        Distance()};
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}