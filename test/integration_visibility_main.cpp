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
// Basic METAR report with various visibility groups: visibility in meters, 
// visibility in miles, visibility in fractions of miles, visibility with 
// modifier.
// These tests cover only main visibility group specified in METAR report or 
// in METAR or TAF trends. They do not cover additional visibility groups 
// specified in remarks and directional visibility groups.
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationVisibility, visibility10km) {
    static const auto rawReport =
        "LBIA 010700Z 07014KT 9999 SKC 27/17 Q1011"; // 01 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {1, 7, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "LBIA";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 70;
    refCurrent.weatherData.windSpeed = Speed {14, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_SKC;
    refCurrent.airTemperature = Temperature{27, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{17, Temperature::Unit::C};
    refCurrent.relativeHumidity = 54;
    refCurrent.pressureSeaLevel = Pressure{1011, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, visibility8km) {
    static const auto rawReport =
        "METAR EPKK 250200Z 23003KT 8000 NSC 14/13 Q1011=";
        // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{25, 2, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPKK";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 230;
    refCurrent.weatherData.windSpeed = Speed{3, Speed::Unit::KT};
    refCurrent.weatherData.visibility = 
        Distance{Distance::Details::EXACTLY, 8000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = 
        Essentials::SkyCondition::NO_SIGNIFICANT_CLOUD;
    refCurrent.airTemperature = Temperature{14, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{13, Temperature::Unit::C};
    refCurrent.relativeHumidity = 93;
    refCurrent.pressureSeaLevel = Pressure{1011, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, visibility700m) {
    static const auto rawReport =
        "METAR UKLR 300330Z 20002MPS 0700 FG NSC 15/15 Q1018 NOSIG=";
        // 30 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 3, 30};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "UKLR";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 200;
    refCurrent.weatherData.windSpeed = Speed{2, Speed::Unit::MPS};
    refCurrent.weatherData.visibility = 
        Distance{Distance::Details::EXACTLY, 700, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = 
        Essentials::SkyCondition::NO_SIGNIFICANT_CLOUD;
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::FOG, {}});
    refCurrent.airTemperature = Temperature{15, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{15, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.pressureSeaLevel = Pressure{1018, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());

    Forecast refForecast;
    refForecast.noSignificantChanges = true;
    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationVisibility, visibility50m) {
    static const auto rawReport =
        "METAR EGDM 270050Z AUTO 17003KT 0050 FG NCD 08/07 Q1030=";
        // 27 SEP 2018

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{27, 0, 50};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EGDM";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 170;
    refCurrent.weatherData.windSpeed = Speed{3, Speed::Unit::KT};
    refCurrent.weatherData.visibility = 
        Distance{Distance::Details::EXACTLY, 50, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = 
        Essentials::SkyCondition::CLEAR_NCD;
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::FOG, {}});
    refCurrent.airTemperature = Temperature{8, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{7, Temperature::Unit::C};
    refCurrent.relativeHumidity = 93;
    refCurrent.pressureSeaLevel = Pressure{1030, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, visibilityNotReportedMeters) {
    static const auto rawReport =
        "METAR LIVM 010855Z AUTO VRB04KT //// 28/18 Q1013="; // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 8, 55};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "LIVM";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionVariable = true;
    refCurrent.weatherData.windSpeed = Speed{4, Speed::Unit::KT};
    refCurrent.airTemperature = Temperature{28, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{18, Temperature::Unit::C};
    refCurrent.relativeHumidity = 54;
    refCurrent.pressureSeaLevel = Pressure{1013, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, visibility10sm) {
    static const auto rawReport =
        "METAR KOXD 010659Z AUTO 08005KT 10SM OVC045 22/20 A2986 RMK AO2"; 
        // 01 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {1, 6, 59};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KOXD";
    refStation.autoType = Station::AutoType::AO2;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 80;
    refCurrent.weatherData.windSpeed = Speed {5, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::EXACTLY, 
        10, 
        Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{4500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{22, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{20, Temperature::Unit::C};
    refCurrent.relativeHumidity = 88;
    refCurrent.pressureSeaLevel = 
        Pressure{2986, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, visibilityNotReportedMiles) {
    static const auto rawReport =
        "METAR CWZZ 010900Z AUTO 25010KT 230V290 ////SM NCD 19/04 A2974="; 
        // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 9, 00};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "CWZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 250;
    refCurrent.weatherData.windSpeed = Speed{10, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 230;
    refCurrent.weatherData.windDirectionVarToDegrees = 290;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_NCD;
    refCurrent.airTemperature = Temperature{19, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{4, Temperature::Unit::C};
    refCurrent.relativeHumidity = 37;
    refCurrent.pressureSeaLevel = 
        Pressure{2974, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}
