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
// This file provides tests for METAR precise temperature groups specified in 
// remarks Txxxxxxxx and group SLPxxx
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationMetarTemperature, preciseTemperaturePressureRmk) {
    static const auto rawReport =
        "METAR CXSE 272000Z AUTO 02010KT M00/M01"
        " RMK AO1 SLP170 T10031013="; // 27 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{27, 20, 0};
    refReport.error = Report::Error::NO_ERROR;
    refReport.automated = true;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "CXSE";
    refStation.autoType = Station::AutoType::AO1;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 20;
    refCurrent.weatherData.windSpeed = Speed{10, Speed::Unit::KT};
    refCurrent.airTemperature = Temperature{-3, Temperature::Unit::TENTH_C};
    refCurrent.dewPoint = Temperature{-13, Temperature::Unit::TENTH_C};
    refCurrent.relativeHumidity = 92;
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1017, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMetarTemperature, pressureQfe) {
    static const auto rawReport =
        "METAR ULOO 312200Z AUTO 36001MPS 9000 // 06/05 Q1026"
        " RMK QFE765="; // 31 OCT 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{31, 22, 0};
    refReport.error = Report::Error::NO_ERROR;
    refReport.automated = true;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ULOO";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 360;
    refCurrent.weatherData.windSpeed = Speed{1, Speed::Unit::MPS};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 9000, Distance::Unit::METERS};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::UNKNOWN, {}});
    refCurrent.airTemperature = Temperature{6, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{5, Temperature::Unit::C};
    refCurrent.relativeHumidity = 93;
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1026, Pressure::Unit::HPA};
    refCurrent.pressureGroundLevel = 
        Pressure{765, Pressure::Unit::MM_HG};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}
