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
// Basic METAR report with one or more weather phenomena specified
// (obscuration, precipitation, and other phenomena).
// These tests do not cover groups with weather phenomena in vicinity such as
// VCSH or VCBLSN, recent weather phenomena and any groups specified in remarks.
// Not all weather phenomena are tested here (see unit_basicdataadapter.cpp for
// complete weather phenomena test).
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationCurrentWeather, haze) {
    static const auto rawReport =
        "METAR DAOF 300800Z 06010KT 1500 HZ NSC 32/12 Q1013=";  // 30 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 8, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "DAOF";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 60;
    refCurrent.weatherData.windSpeed = Speed{10, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 1500, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition =
        Essentials::SkyCondition::NO_SIGNIFICANT_CLOUD;
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::HAZE, {}});
    refCurrent.weatherData.seaLevelPressure = Pressure{1013, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{32, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{12, Temperature::Unit::C};
    refCurrent.relativeHumidity = 29;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationCurrentWeather, lowDriftingSand) {
    static const auto rawReport =
        "METAR DATM 300800Z 32016KT 2000 DRSA NSC 32/12 Q1010=";  // 30 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 8, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "DATM";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 320;
    refCurrent.weatherData.windSpeed = Speed{16, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 2000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition =
        Essentials::SkyCondition::NO_SIGNIFICANT_CLOUD;
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::DRIFTING_SAND, {}});
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1010, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{32, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{12, Temperature::Unit::C};
    refCurrent.relativeHumidity = 29;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationCurrentWeather, thunderstorm) {
    static const auto rawReport =
        "METAR WMKN 300800Z VRB04KT 9000 TS FEW017CB SCT018 32/26 Q1007=";
    // 30 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 8, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "WMKN";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionVariable = true;
    refCurrent.weatherData.windSpeed = Speed{4, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 9000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{1700, Height::Unit::FEET},
                   CloudLayer::Details::CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{1800, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::THUNDERSTORM, {}});
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1007, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{32, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{26, Temperature::Unit::C};
    refCurrent.relativeHumidity = 70;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationCurrentWeather, lightShoweryPrecipitation) {
    static const auto rawReport =
        "METAR RJFS 300800Z 23005KT 9999 -SHRA FEW015 SCT025 BKN035 30/27 Q1014"
        "=";
    // 30 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 8, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "RJFS";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 230;
    refCurrent.weatherData.windSpeed = Speed{5, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{1500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{2500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{3500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1014, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{30, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{27, Temperature::Unit::C};
    refCurrent.relativeHumidity = 84;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationCurrentWeather, heavyPrecipitation) {
    static const auto rawReport =
        "METAR WBKL 300800Z 25007KT 190V330 1000 +RA FEW010 SCT030 25/24 Q1007"
        "=";
    // 30 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 8, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "WBKL";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 250;
    refCurrent.weatherData.windSpeed = Speed{7, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 190;
    refCurrent.weatherData.windDirectionVarToDegrees = 330;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 1000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{1000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_HEAVY,
                {Weather::Precipitation::RAIN}});
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1007, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{25, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{24, Temperature::Unit::C};
    refCurrent.relativeHumidity = 94;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationCurrentWeather, mixedPrecipitation) {
    static const auto rawReport =
        "BGBW 300850Z 06005KT 7000 -RADZ FEW002 BKN004 BKN007 07/06 Q1012=";
    // 30 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 8, 50};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "BGBW";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 60;
    refCurrent.weatherData.windSpeed = Speed{5, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 7000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{200, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{400, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{700, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN,
                 Weather::Precipitation::DRIZZLE}});
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1012, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{7, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{6, Temperature::Unit::C};
    refCurrent.relativeHumidity = 93;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationCurrentWeather, multipleWeatherPhenomena) {
    static const auto rawReport =
        "METAR EGPI 300820Z 12016KT 090V160 3000 DZ BR OVC004 14/14 Q1011"
        "=";
    // 30 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 8, 20};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EGPI";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 120;
    refCurrent.weatherData.windSpeed = Speed{16, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 90;
    refCurrent.weatherData.windDirectionVarToDegrees = 160;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 3000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{400, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_MODERATE,
                {Weather::Precipitation::DRIZZLE}});
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::MIST, {}});
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1011, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{14, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{14, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationCurrentWeather, weatherNotReported) {
    static const auto rawReport =
        "EGOP 301950Z AUTO 12010KT 9999 // NCD 21/11 Q1012="; // 30 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.automated = true;
    refReport.reportTime = Time{30, 19, 50};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EGOP";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 120;
    refCurrent.weatherData.windSpeed = Speed{10, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_NCD;
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::UNKNOWN, {}});
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1012, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{21, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{11, Temperature::Unit::C};
    refCurrent.relativeHumidity = 52;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

