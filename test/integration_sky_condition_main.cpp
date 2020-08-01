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
// Basic METAR report with various sky condition groups: CLR, SKC, NSC, NCD,
// one or multiple cloud layers (FEW, SCT, BKN, OVC) optionally with convective
// type (TCU, CB), and vertical visibility groups.
// These tests cover only main cloud conditions groups specified in METAR report
// or in METAR or TAF trends. They do not cover augmenting groups specified in
// remarks.
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationSkyCondition, skc) {
    static const auto rawReport =
        "METAR MMML 251944Z 17007KT 10SM SKC 37/11 A2981";  // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{25, 19, 44};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "MMML";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 170;
    refCurrent.weatherData.windSpeed = Speed{7, Speed::Unit::KT};
    refCurrent.weatherData.visibility = Distance{
        Distance::Details::EXACTLY,
        10,
        Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_SKC;
    refCurrent.airTemperature = Temperature{37, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{11, Temperature::Unit::C};
    refCurrent.relativeHumidity = 20;
    refCurrent.pressureSeaLevel =
        Pressure{2981, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationSkyCondition, clr) {
    static const auto rawReport =
        "METAR KBVS 252015Z AUTO 29010KT 10SM CLR 22/11 A3017 RMK A01=";
        // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.automated = true;
    refReport.reportTime = Time{25, 20, 15};
    refReport.error = Report::Error::NO_ERROR;
    refReport.plainText.push_back("A01");
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KBVS";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 290;
    refCurrent.weatherData.windSpeed = Speed{10, Speed::Unit::KT};
    refCurrent.weatherData.visibility = Distance{
        Distance::Details::EXACTLY,
        10,
        Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_CLR;
    refCurrent.airTemperature = Temperature{22, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{11, Temperature::Unit::C};
    refCurrent.relativeHumidity = 49;
    refCurrent.pressureSeaLevel =
        Pressure{3017, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationSkyCondition, nsc) {
    static const auto rawReport =
        "METAR EPKK 250200Z 23003KT 8000 NSC 14/13 Q1011=";
        // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{25, 2, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPKK";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 230;
    refCurrent.weatherData.windSpeed = Speed{3, Speed::Unit::KT};
    refCurrent.weatherData.visibility = 
        Distance{Distance::Details::EXACTLY, 8000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = 
        Essentials::SkyCondition::NO_SIGNIFICANT_CLOUD;
    refCurrent.airTemperature = Temperature{14, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{13, Temperature::Unit::C};
    refCurrent.relativeHumidity = 93;
    refCurrent.pressureSeaLevel = Pressure{1011, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationSkyCondition, ncd) {
    static const auto rawReport =
        "ESMT 252020Z AUTO 17009KT 9999 NCD 18/14 Q1010=";
        // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.automated = true;
    refReport.reportTime = Time{25, 20, 20};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ESMT";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 170;
    refCurrent.weatherData.windSpeed = Speed{9, Speed::Unit::KT};
    refCurrent.weatherData.visibility = 
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_NCD;
    refCurrent.airTemperature = Temperature{18, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{14, Temperature::Unit::C};
    refCurrent.relativeHumidity = 77;
    refCurrent.pressureSeaLevel = Pressure{1010, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}
