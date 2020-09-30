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
// Miscellanious uncommon groups: lightning, vicinity, colour codes,
// low/mid/high cloud layers, density altitude, hailstone size
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationMisc, lightning) {
    static const auto rawReport =
        "METAR ZZZZ 262103Z /////KT ////SM RMK CONS LTGICCGCC OHD=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 21, 03};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.lightningStrikes.push_back(LightningStrikes{
        LightningStrikes::Frequency::CONSTANT,
        {LightningStrikes::Type::IN_CLOUD,
         LightningStrikes::Type::CLOUD_CLOUD,
         LightningStrikes::Type::CLOUD_GROUND},
        DistanceRange(),
        {CardinalDirection::OVERHEAD}});
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMisc, lightningDistanceRange) {
    static const auto rawReport =
        "METAR ZZZZ 262103Z /////KT ////SM RMK LTG DSNT NW=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 21, 03};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.lightningStrikes.push_back(LightningStrikes{
        LightningStrikes::Frequency::UNKNOWN,
        {},
        DistanceRange{
            Distance(),
            Distance{Distance::Details::EXACTLY, 18520, Distance::Unit::METERS},
            Distance{Distance::Details::EXACTLY, 55560, Distance::Unit::METERS}},
        {CardinalDirection::NW}});
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMisc, phenomenaInVicinityRmk) {
    static const auto rawReport =
        "METAR ZZZZ 261425Z /////KT //// RMK TCU 35KM SW-NW MOV NE=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 14, 25};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.phenomenaInVicinity.push_back(Vicinity{
        ObservedPhenomena::TOWERING_CUMULUS,
        DistanceRange{
            Distance{Distance::Details::EXACTLY, 35000, Distance::Unit::METERS},
            Distance(),
            Distance()},
        CardinalDirection::NE,
        {CardinalDirection::SW, CardinalDirection::W, CardinalDirection::NW}});
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMisc, phenomenaInVicinityRmkDistanceRange) {
    static const auto rawReport =
        "METAR ZZZZ 261425Z /////KT //// RMK VIRGA DSNT NW-N=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 14, 25};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.phenomenaInVicinity.push_back(Vicinity{
        ObservedPhenomena::VIRGA,
        DistanceRange{
            Distance(),
            Distance{Distance::Details::EXACTLY, 18520, Distance::Unit::METERS},
            Distance{Distance::Details::EXACTLY, 55560, Distance::Unit::METERS}},
        CardinalDirection::NOT_SPECIFIED,
        {CardinalDirection::NW, CardinalDirection::N}});
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMisc, phenomenaInVicinityMetar) {
    static const auto rawReport =
        "METAR ZZZZ 261425Z /////KT //// VCSH ///// Q////=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 14, 25};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.phenomenaInVicinity.push_back(Vicinity{
        ObservedPhenomena::PRECIPITATION,
        DistanceRange{
            Distance(),
            Distance{
                Distance::Details::EXACTLY,
                5,
                Distance::Unit::STATUTE_MILES},
            Distance{
                Distance::Details::EXACTLY,
                10,
                Distance::Unit::STATUTE_MILES}},
        CardinalDirection::NOT_SPECIFIED,
        {}});
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMisc, colourCode) {
    static const auto rawReport =
        "METAR ZZZZ 262253Z /////KT //// WHT=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 22, 53};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Aerodrome refAerodrome;
    refAerodrome.colourCode = Aerodrome::ColourCode::WHITE;
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMisc, colourCodeBlack) {
    static const auto rawReport =
        "METAR ZZZZ 262253Z /////KT //// BLACKRED=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 22, 53};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Aerodrome refAerodrome;
    refAerodrome.colourCode = Aerodrome::ColourCode::RED;
    refAerodrome.colourCodeBlack = true;
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// TODO: low/mid/high clouds
// TODO: density altitude
// TODO: sunshine duration
// TODO: hailstone size