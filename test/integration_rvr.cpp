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
// This file provides tests for variable and non-variable Runway Visual Range
// groups, optionally with trend
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationRvr, rvr) {
    static const auto rawReport =
        "METAR EGNM 031820Z 05005KT 010V090 0800 R32/1100 -RA FG OVC002"
        " 12/12 Q0983=";  // 03 OCT 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{3, 18, 20};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EGNM";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 50;
    refCurrent.weatherData.windSpeed = Speed{5, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 10;
    refCurrent.weatherData.windDirectionVarToDegrees = 90;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 800, Distance::Unit::METERS};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::FOG, {}});
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{200, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{12, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{12, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{983, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    Aerodrome refAerodrome;
    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways[0].runway = Runway{32, Runway::Designator::NONE};
    refAerodrome.runways[0].visualRange.prevailing =
        Distance{Distance::Details::EXACTLY, 1100, Distance::Unit::METERS};
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationRvr, variableRvr) {
    static const auto rawReport =
        "SPECI KMRY 030837Z AUTO 00000KT 1/4SM R10R/1400VP6000FT FU HZ"
        " VV002 A2996 RMK AO2 $=";  // 03 OCT 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::SPECI;
    refReport.reportTime = Time{3, 8, 37};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KMRY";
    refStation.autoType = Station::AutoType::AO2;
    refStation.requiresMaintenance = true;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windCalm = true;
    refCurrent.weatherData.visibility =
        Distance{
            Distance::Details::EXACTLY,
            4,
            Distance::Unit::STATUTE_MILE_1_16S};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::SMOKE, {}});
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::HAZE, {}});
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::OBSCURED;
    refCurrent.weatherData.verticalVisibility = 
        Height{200, Height::Unit::FEET};
    refCurrent.weatherData.seaLevelPressure =
        Pressure{2996, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    Aerodrome refAerodrome;
    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways[0].runway = Runway{10, Runway::Designator::RIGHT};
    refAerodrome.runways[0].visualRange.minimum =
        Distance{Distance::Details::EXACTLY, 1400, Distance::Unit::FEET};
    refAerodrome.runways[0].visualRange.maximum =
        Distance{Distance::Details::MORE_THAN, 6000, Distance::Unit::FEET};
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationRvr, rvrMultipleTrendAndNotReported) {
    static const auto rawReport =
        "METAR ESKM 030820Z AUTO 01005KT 350V050 9999 R16/P2000N "
        "R34///// OVC015/// 11/11 Q1017 =";  // 03 OCT 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{3, 8, 20};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ESKM";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 10;
    refCurrent.weatherData.windSpeed = Speed{5, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 350;
    refCurrent.weatherData.windDirectionVarToDegrees = 50;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{1500, Height::Unit::FEET},
                   CloudLayer::Details::UNKNOWN,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{11, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{11, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1017, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    Aerodrome refAerodrome;
    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways[0].runway = Runway{16, Runway::Designator::NONE};
    refAerodrome.runways[0].visualRange.prevailing =
        Distance{Distance::Details::MORE_THAN, 2000, Distance::Unit::METERS};
    refAerodrome.runways[0].visualRangeTrend = Aerodrome::RvrTrend::NEUTRAL;
    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways[1].runway = Runway{34, Runway::Designator::NONE};
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationRvr, rvrNotReported) {
    static const auto rawReport =
        "METAR SCCH 030800Z AUTO 07003KT //// R/////// NCD 01/01 Q1018=";
    // 03 OCT 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{3, 8, 0};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "SCCH";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 70;
    refCurrent.weatherData.windSpeed = Speed{3, Speed::Unit::KT};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_NCD;
    refCurrent.airTemperature = Temperature{1, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{1, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1018, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}