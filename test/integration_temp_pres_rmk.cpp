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