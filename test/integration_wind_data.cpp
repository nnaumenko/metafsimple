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
// Basic METAR report with various wind groups: calm wind, wind speed measured 
// in meters per second, variable wind direction, variable wind sector, 
// wind with gusts
////////////////////////////////////////////////////////////////////////////////

TEST(ParseSimplifyReportWind, calmWind) {
    static const auto rawReport =
        "METAR EPZG 252000Z 00000KT CAVOK 18/18 Q1013="; // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {25, 20, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPZG";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windCalm = true;
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{18, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{18, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.pressureSeaLevel = Pressure{1013, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, variableWindSector) {
    static const auto rawReport =
        "METAR EPRZ 251500Z 01006KT 330V050 CAVOK 26/14 Q1012="; // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {25, 15, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPRZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 10;
    refCurrent.weatherData.windSpeed = Speed {6, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 330;
    refCurrent.weatherData.windDirectionVarToDegrees = 50;
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{26, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{14, Temperature::Unit::C};
    refCurrent.relativeHumidity = 47;
    refCurrent.pressureSeaLevel = Pressure{1012, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, variableWindDirection) {
    static const auto rawReport =
        "METAR EPRZ 251600Z VRB03KT CAVOK 26/14 Q1012="; // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {25, 16, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPRZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionVariable = true;
    refCurrent.weatherData.windSpeed = Speed {3, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{26, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{14, Temperature::Unit::C};
    refCurrent.relativeHumidity = 47;
    refCurrent.pressureSeaLevel = Pressure{1012, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, windGusts) {
    static const auto rawReport =
        "METAR EPGD 211330Z 29019G29KT CAVOK 19/08 Q1017="; // 21 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {21, 13, 30};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPGD";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 290;
    refCurrent.weatherData.windSpeed = Speed {19, Speed::Unit::KT};
    refCurrent.weatherData.gustSpeed = Speed {29, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{19, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{8, Temperature::Unit::C};
    refCurrent.relativeHumidity = 48;
    refCurrent.pressureSeaLevel = Pressure{1017, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, windGustsVariableSector) {
    static const auto rawReport =
        "METAR EPZG 241400Z 25007G18KT 180V300 CAVOK 28/08 Q1008="; 
        // 24 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {24, 14, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPZG";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 250;
    refCurrent.weatherData.windSpeed = Speed {7, Speed::Unit::KT};
    refCurrent.weatherData.gustSpeed = Speed {18, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 180;
    refCurrent.weatherData.windDirectionVarToDegrees = 300;
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{28, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{8, Temperature::Unit::C};
    refCurrent.relativeHumidity = 28;
    refCurrent.pressureSeaLevel = Pressure{1008, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// TODO: non-reported wind group
// TODO: wind speed in MPS
// TODO: variable wind sector without wind direction/speed group
// TODO: duplicate wind group
// TODO: duplicate variable wind sector