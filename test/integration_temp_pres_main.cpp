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
// This file provides tests for METAR temperature and atmospheric pressure 
// groups
// Note: Basic temperature and pressure groups xx/xx and Qxxxx were tested
// with basic reports in integration_basic_report.cpp.
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationMetarTemperature, dewPointNotReported) {
    static const auto rawReport =
        "METAR YPKU 182300Z AUTO 00000KT 9999 // NCD 23/// Q1011="; 
        // 18 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{18, 23, 0};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "YPKU";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windCalm = true;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::UNKNOWN, {}});
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_NCD;

    refCurrent.airTemperature = Temperature{23, Temperature::Unit::C};
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1011, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMetarTemperature, temperatureDewPointNotReported) {
    static const auto rawReport =
        "METAR CWUW 190000Z AUTO 10007KT ////SM SCT003 BKN014 OVC021"
        " ///// A////="; // 19 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{19, 0, 0};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "CWUW";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 100;
    refCurrent.weatherData.windSpeed = Speed{7, Speed::Unit::KT};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{300, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{1400, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{2100, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMetarTemperature, pressureInhg) {
    static const auto rawReport =
        "METAR KSUN 182258Z 20009G16KT 10SM SKC 33/07 A3022="; // 18 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{18, 22, 58};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KSUN";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 200;
    refCurrent.weatherData.windSpeed = Speed{9, Speed::Unit::KT};
    refCurrent.weatherData.gustSpeed = Speed{16, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 10, Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_SKC;
    refCurrent.airTemperature = Temperature{33, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{7, Temperature::Unit::C};
    refCurrent.relativeHumidity = 19;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{3022, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMetarTemperature, pressureInhgNotReported) {
    static const auto rawReport =
        "METAR CWUW 190000Z AUTO 10007KT ////SM SCT003 BKN014 OVC021"
        " ///// A////="; // 19 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{19, 0, 0};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "CWUW";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 100;
    refCurrent.weatherData.windSpeed = Speed{7, Speed::Unit::KT};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{300, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{1400, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{2100, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationMetarTemperature, pressureHpaNotReported) {
    static const auto rawReport =
        "METAR SBBW 211900Z /////KT CAVOK 30/11 Q////="; // 21 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{21, 19, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "SBBW";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.airTemperature = Temperature{30, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{11, Temperature::Unit::C};
    refCurrent.relativeHumidity = 30;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}
