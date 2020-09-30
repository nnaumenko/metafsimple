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

TEST(IntegrationRecentWeather, recentWeather) {
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

TEST(IntegrationRecentWeather, weatherEvents) {
    static const auto rawReport =
        "METAR ZZZZ 301946Z /////KT ////SM ///// A////"
        " RMK DZB23E38RAB42 TSB41=";
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
            Weather::Phenomena::PRECIPITATION,
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