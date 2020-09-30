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
// Tests covering recent weather groups (REDZ, etc.) and precipitation
// beginning/ending time group (DZB23E38RAB42)
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationRecentWeather, recentWeatherPrecipitation) {
    static const auto rawReport =
        "METAR EGXE 272050Z AUTO 26004KT 9999 NCD 05/04 Q1015 REDZ=";
    // 27 SEP 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{27, 20, 50};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EGXE";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 260;
    refCurrent.weatherData.windSpeed = Speed{4, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_NCD;
    refCurrent.airTemperature = Temperature{5, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{4, Temperature::Unit::C};
    refCurrent.relativeHumidity = 93;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    Historical refHistorical;
    refHistorical.recentWeather.push_back(Historical::WeatherEvent{
        Historical::Event::ENDED,
        Weather{
            Weather::Phenomena::PRECIPITATION,
            {Weather::Precipitation::DRIZZLE},
        },
        Time()});
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationRecentWeather, recentWeatherShowers) {
    static const auto rawReport =
        "METAR BIEG 302000Z 35007KT 9999 -DZ BKN018 OVC028 09/06 Q0987 RESHRA=";
    // 30 SEP 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "BIEG";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 350;
    refCurrent.weatherData.windSpeed = Speed{7, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_LIGHT,
                {Weather::Precipitation::DRIZZLE}});
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{1800, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{2800, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});


    refCurrent.airTemperature = Temperature{9, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{6, Temperature::Unit::C};
    refCurrent.relativeHumidity = 81;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{987, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    Historical refHistorical;
    refHistorical.recentWeather.push_back(Historical::WeatherEvent{
        Historical::Event::ENDED,
        Weather{
            Weather::Phenomena::SHOWERY_PRECIPITATION,
            {Weather::Precipitation::RAIN},
        },
        Time()});
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationRecentWeather, recentWeatherThunderstorm) {
    static const auto rawReport =
        "METAR FKKR 302000Z 26003KT CAVOK 26/25 Q1012 RETS NOSIG=";
    // 30 SEP 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "FKKR";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 260;
    refCurrent.weatherData.windSpeed = Speed{3, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.weatherData.cavok = true;
    refCurrent.airTemperature = Temperature{26, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{25, Temperature::Unit::C};
    refCurrent.relativeHumidity = 94;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1012, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    Historical refHistorical;
    refHistorical.recentWeather.push_back(Historical::WeatherEvent{
        Historical::Event::ENDED,
        Weather{Weather::Phenomena::THUNDERSTORM, {}},
        Time()});
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());

    Forecast refForecast;
    refForecast.noSignificantChanges = true;
    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationRecentWeather, weatherEvents) {
    static const auto rawReport =
        "METAR ZZZZ 301946Z /////KT ////SM ///// A////"
        " RMK DZB23E38SHRAB42 TSB41=";
        //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 19, 46};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.recentWeather.push_back(Historical::WeatherEvent{
        Historical::Event::BEGAN,
        Weather{
            Weather::Phenomena::PRECIPITATION,
            {Weather::Precipitation::DRIZZLE},
        },
        Time{std::optional<int>(), 19, 23}});
    refHistorical.recentWeather.push_back(Historical::WeatherEvent{
        Historical::Event::ENDED,
        Weather{
            Weather::Phenomena::PRECIPITATION,
            {Weather::Precipitation::DRIZZLE},
        },
        Time{std::optional<int>(), 19, 38}});
    refHistorical.recentWeather.push_back(Historical::WeatherEvent{
        Historical::Event::BEGAN,
        Weather{
            Weather::Phenomena::SHOWERY_PRECIPITATION,
            {Weather::Precipitation::RAIN},
        },
        Time{std::optional<int>(), 19, 42}});
    refHistorical.recentWeather.push_back(Historical::WeatherEvent{
        Historical::Event::BEGAN,
        Weather{
            Weather::Phenomena::THUNDERSTORM,
            {},
        },
        Time{std::optional<int>(), 19, 41}});
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.forecast, Forecast());
}