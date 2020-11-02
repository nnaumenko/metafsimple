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

TEST(IntegrationMisc, phenomenaInVicinityRmkDsnt) {
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

TEST(IntegrationMisc, phenomenaInVicinityRmkVc) {
    static const auto rawReport =
        "METAR ZZZZ 261425Z /////KT //// RMK VIRGA VC ALQDS=";
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
            Distance{Distance::Details::EXACTLY, 9260, Distance::Unit::METERS},
            Distance{Distance::Details::EXACTLY, 18520, Distance::Unit::METERS}},
        CardinalDirection::NOT_SPECIFIED,
        {CardinalDirection::ALL_QUADRANTS}});
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMisc, phenomenaInVicinityRmkMovUnknown) {
    static const auto rawReport =
        "METAR ZZZZ 261425Z /////KT //// RMK CB E-SE MOV UNKNOWN=";
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
        ObservedPhenomena::CUMULONIMBUS,
        DistanceRange{},
        CardinalDirection::UNKNOWN,
        {CardinalDirection::E, CardinalDirection::SE}});
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

TEST(IntegrationMisc, colourCodes) {
    static const std::string basicReport = "METAR ZZZZ 010000Z /////KT //// ";
    //all reports in this test are fake reports

    Simple result;

    result = metafsimple::simplify(basicReport + "BLU=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::BLUE);
    EXPECT_FALSE(result.aerodrome.colourCodeBlack);

    result = metafsimple::simplify(basicReport + "WHT=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::WHITE);
    EXPECT_FALSE(result.aerodrome.colourCodeBlack);

    result = metafsimple::simplify(basicReport + "GRN=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::GREEN);
    EXPECT_FALSE(result.aerodrome.colourCodeBlack);

    result = metafsimple::simplify(basicReport + "YLO1=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::YELLOW1);
    EXPECT_FALSE(result.aerodrome.colourCodeBlack);

    result = metafsimple::simplify(basicReport + "YLO2=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::YELLOW2);
    EXPECT_FALSE(result.aerodrome.colourCodeBlack);

    result = metafsimple::simplify(basicReport + "AMB=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::AMBER);
    EXPECT_FALSE(result.aerodrome.colourCodeBlack);

    result = metafsimple::simplify(basicReport + "RED=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::RED);
    EXPECT_FALSE(result.aerodrome.colourCodeBlack);
}

TEST(IntegrationMisc, colourCodesBlack) {
    static const std::string basicReport = "METAR ZZZZ 010000Z /////KT BLACK";
    //all reports in this test are fake reports

    Simple result;

    result = metafsimple::simplify(basicReport + "BLU=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::BLUE);
    EXPECT_TRUE(result.aerodrome.colourCodeBlack);

    result = metafsimple::simplify(basicReport + "WHT=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::WHITE);
    EXPECT_TRUE(result.aerodrome.colourCodeBlack);

    result = metafsimple::simplify(basicReport + "GRN=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::GREEN);
    EXPECT_TRUE(result.aerodrome.colourCodeBlack);

    result = metafsimple::simplify(basicReport + "YLO1=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::YELLOW1);
    EXPECT_TRUE(result.aerodrome.colourCodeBlack);

    result = metafsimple::simplify(basicReport + "YLO2=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::YELLOW2);
    EXPECT_TRUE(result.aerodrome.colourCodeBlack);

    result = metafsimple::simplify(basicReport + "AMB=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::AMBER);
    EXPECT_TRUE(result.aerodrome.colourCodeBlack);

    result = metafsimple::simplify(basicReport + "RED=");
    EXPECT_EQ(result.aerodrome.colourCode, Aerodrome::ColourCode::RED);
    EXPECT_TRUE(result.aerodrome.colourCodeBlack);
}

TEST(IntegrationMisc, lowMidHighClouds) {
    static const auto rawReport =
        "METAR ZZZZ 011302Z /////KT //// RMK 8/578=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 13, 2};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.lowCloudLayer = Current::LowCloudLayer::SC_NON_CUGEN;
    refCurrent.midCloudLayer =
        Current::MidCloudLayer::AC_DU_AC_OP_AC_WITH_AS_OR_NS;
    refCurrent.highCloudLayer = Current::HighCloudLayer::CS;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMisc, densityAltitude) {
    static const auto rawReport =
        "METAR ZZZZ 011302Z /////KT //// RMK DENSITY ALT 3500FT=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 13, 2};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.densityAltitude = Height{3500, Height::Unit::FEET};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMisc, sunshineDuration) {
    static const auto rawReport =
        "METAR ZZZZ 262116Z /////KT //// RMK 98173=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 21, 16};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.sunshineDurationMinutes24h = 173;
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMisc, hailstoneSize) {
    static const auto rawReport =
        "METAR ZZZZ 262116Z /////KT //// RMK GR 1 3/4=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 21, 16};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.hailstoneSizeQuartersInch = 7;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMisc, obscurations) {
    static const auto rawReport =
        "METAR ZZZZ 262116Z /////KT //// RMK FU BKN002=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 21, 16};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.obscurations.push_back(CloudLayer());
    refCurrent.obscurations.back().amount = CloudLayer::Amount::BROKEN;
    refCurrent.obscurations.back().height = Height{200, Height::Unit::FEET};
    refCurrent.obscurations.back().details = CloudLayer::Details::SMOKE;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMisc, windShearLowerLayers) {
    static const auto rawReport =
        "METAR ZZZZ 262253Z /////KT //// WS RWY07C=";
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
    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways.back().runway.number = 7;
    refAerodrome.runways.back().runway.designator = Runway::Designator::CENTER;
    refAerodrome.runways.back().windShearLowerLayers = true;
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMisc, windShearLowerLayersAllRwy) {
    static const auto rawReport =
        "METAR ZZZZ 262253Z /////KT //// WS ALL RWY=";
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
    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways.back().runway.number = 88;
    refAerodrome.runways.back().runway.designator = Runway::Designator::NONE;
    refAerodrome.runways.back().windShearLowerLayers = true;
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}
