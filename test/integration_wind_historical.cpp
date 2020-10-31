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
// Tests covering peak wind and wind shift groups
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationWindHistorical, peakWind) {
    static const auto rawReport =
        "METAR K1IM 052158Z AUTO 34014G18KT 10SM CLR 34/00 A2998"
        " RMK AO2 PK WND 22029/2054 SLP131 T03361003 $=";
    // 05 SEP 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{5, 21, 58};
    refReport.error = Report::Error::NO_ERROR;
    refReport.automated = true;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "K1IM";
    refStation.autoType = Station::AutoType::AO2;
    refStation.requiresMaintenance = true;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 340;
    refCurrent.weatherData.windSpeed = Speed{14, Speed::Unit::KT};
    refCurrent.weatherData.gustSpeed = Speed{18, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 10, Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_CLR;
    refCurrent.airTemperature = Temperature{336, Temperature::Unit::TENTH_C};
    refCurrent.dewPoint = Temperature{-3, Temperature::Unit::TENTH_C};
    refCurrent.relativeHumidity = 11;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{2998, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    Historical refHistorical;
    refHistorical.peakWindDirectionDegrees = 220;
    refHistorical.peakWindSpeed = Speed {29, Speed::Unit::KT};
    refHistorical.peakWindObserved = Time {std::optional<int>(), 20, 54};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationWindHistorical, windShift) {
    static const auto rawReport =
        "METAR KTUS 052153Z 07013KT 10SM CLR 42/02 A3006"
        " RMK AO2 WSHFT 2045 SLP118 T04170017="; // 05 SEP 2020
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{5, 21, 53};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KTUS";
    refStation.autoType = Station::AutoType::AO2;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 70;
    refCurrent.weatherData.windSpeed = Speed{13, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 10, Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_CLR;
    refCurrent.airTemperature = Temperature{417, Temperature::Unit::TENTH_C};
    refCurrent.dewPoint = Temperature{17, Temperature::Unit::TENTH_C};
    refCurrent.relativeHumidity = 8;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{3006, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    Historical refHistorical;
    refHistorical.windShiftBegan = Time{std::optional<int>(), 20, 45};
    refHistorical.windShift = true;
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationWindHistorical, windShiftFropa) {
    static const auto rawReport =
        "METAR ZZZZ 060752Z /////KT RMK WSHFT 0731 FROPA=";
    // Fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{6, 7, 52};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.windShiftBegan = Time{std::optional<int>(), 7, 31};
    refHistorical.windShiftFrontPassage = true;
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.forecast, Forecast());
}