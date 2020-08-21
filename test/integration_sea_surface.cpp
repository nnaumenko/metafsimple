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
// This file provides tests for METAR sea surface state groups: Wxx/Sx and 
// Wxx/Hx
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationSeaSurface, stateOfSurface) {
    static const auto rawReport =
        "METAR ENLE 182320Z 17015KT 9999 FEW030 BKN040 17/16 Q1007 W16/S3="; 
        // 18 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{18, 23, 20};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ENLE";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 170;
    refCurrent.weatherData.windSpeed = Speed{15, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    refCurrent.airTemperature = Temperature{17, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{16, Temperature::Unit::C};
    refCurrent.relativeHumidity = 93;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1007, Pressure::Unit::HPA};
    refCurrent.seaSurfaceTemperature = Temperature{16, Temperature::Unit::C};
    refCurrent.waveHeight = WaveHeight{12, WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationSeaSurface, waveHeight) {
    static const auto rawReport =
        "METAR EHSA 182325Z AUTO 20016KT 9999 ///////// 20/16 Q1010 W18/H9=";
        // 18 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{18, 23, 25};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EHSA";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 200;
    refCurrent.weatherData.windSpeed = Speed{16, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::UNKNOWN,
                   Height(),
                   CloudLayer::Details::UNKNOWN,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{20, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{16, Temperature::Unit::C};
    refCurrent.relativeHumidity = 77;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1010, Pressure::Unit::HPA};
    refCurrent.seaSurfaceTemperature = Temperature{18, Temperature::Unit::C};
    refCurrent.waveHeight = WaveHeight{9, WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationSeaSurface, stateOfSurfaceNotReported) {
    static const auto rawReport =
        "METAR ENUN 212220Z AUTO 05016KT 9999NDV -SHRA BKN046///"
        " 14/13 Q0992 W13/S/="; // 21 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{21, 22, 20};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ENUN";
    refStation.noVisDirectionalVariation = true;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 50;
    refCurrent.weatherData.windSpeed = Speed{16, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{4600, Height::Unit::FEET},
                   CloudLayer::Details::UNKNOWN,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{14, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{13, Temperature::Unit::C};
    refCurrent.relativeHumidity = 93;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{992, Pressure::Unit::HPA};
    refCurrent.seaSurfaceTemperature = Temperature{13, Temperature::Unit::C};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationSeaSurface, waveHeightNotReported) {
    static const auto rawReport =
        "METAR EHSA 071655Z AUTO 05007KT 9999 ///////// 26/10 Q1018 W///H///=";
        // 7 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{7, 16, 55};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EHSA";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 50;
    refCurrent.weatherData.windSpeed = Speed{7, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::UNKNOWN,
                   Height(),
                   CloudLayer::Details::UNKNOWN,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{26, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{10, Temperature::Unit::C};
    refCurrent.relativeHumidity = 36;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1018, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());

    Historical refHistorical;
    EXPECT_EQ(result.historical, Historical());

    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationSeaSurface, surfaceTemperatureNotReported) {
    static const auto rawReport =
        "METAR ENNE 182320Z AUTO 28007KT 9999NDV OVC019/// 10/06"
        " Q1008 W///S3="; // 18 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{18, 23, 20};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ENNE";
    refStation.noVisDirectionalVariation = true;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 280;
    refCurrent.weatherData.windSpeed = Speed{7, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{1900, Height::Unit::FEET},
                   CloudLayer::Details::UNKNOWN,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{10, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{6, Temperature::Unit::C};
    refCurrent.relativeHumidity = 76;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1008, Pressure::Unit::HPA};
    refCurrent.waveHeight = WaveHeight{12, WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

