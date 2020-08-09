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
        "LBIA 010700Z 07014KT 9999 SKC 27/17 Q1011";  // 01 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 7, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "LBIA";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 70;
    refCurrent.weatherData.windSpeed = Speed{14, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_SKC;
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1011, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{27, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{17, Temperature::Unit::C};
    refCurrent.relativeHumidity = 54;
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
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1011, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{14, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{13, Temperature::Unit::C};
    refCurrent.relativeHumidity = 93;
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
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1018, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{15, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{15, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
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
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1030, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{8, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{7, Temperature::Unit::C};
    refCurrent.relativeHumidity = 93;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, visibilityNotReportedMeters) {
    static const auto rawReport =
        "METAR LIVM 010855Z AUTO VRB04KT //// 28/18 Q1013=";  // 1 AUG 2020

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
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1013, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{28, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{18, Temperature::Unit::C};
    refCurrent.relativeHumidity = 54;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, visibility20sm) {
    static const auto rawReport =
        "METAR KBJC 251950Z 33011KT 20SM SCT080 BKN120 27/10 A3016=";
    // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{25, 19, 50};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KBJC";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 330;
    refCurrent.weatherData.windSpeed = Speed{11, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 20, Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{8000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{12000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.seaLevelPressure =
        Pressure{3016, Pressure::Unit::HUNDREDTHS_IN_HG};
    refCurrent.airTemperature = Temperature{27, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{10, Temperature::Unit::C};
    refCurrent.relativeHumidity = 34;
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
    refReport.reportTime = Time{1, 6, 59};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KOXD";
    refStation.autoType = Station::AutoType::AO2;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 80;
    refCurrent.weatherData.windSpeed = Speed{5, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 10, Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{4500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.seaLevelPressure =
        Pressure{2986, Pressure::Unit::HUNDREDTHS_IN_HG};
    refCurrent.airTemperature = Temperature{22, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{20, Temperature::Unit::C};
    refCurrent.relativeHumidity = 88;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, visibility7sm) {
    static const auto rawReport =
        "METAR KW29 011215Z AUTO 08005KT 7SM OVC120 26/24 A2994 RMK AO2";
    // 01 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 12, 15};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KW29";
    refStation.autoType = Station::AutoType::AO2;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 80;
    refCurrent.weatherData.windSpeed = Speed{5, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 7, Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{12000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.seaLevelPressure =
        Pressure{2994, Pressure::Unit::HUNDREDTHS_IN_HG};
    refCurrent.airTemperature = Temperature{26, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{24, Temperature::Unit::C};
    refCurrent.relativeHumidity = 88;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, visibility3sm) {
    static const auto rawReport =
        "KFRR 011215Z AUTO 00000KT 3SM OVC001 A2996 RMK AO1";
    // 01 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 12, 15};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KFRR";
    refStation.autoType = Station::AutoType::AO1;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windCalm = true;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 3, Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{100, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.seaLevelPressure =
        Pressure{2996, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, visibility2_1_2sm) {
    static const auto rawReport =
        "METAR KFDK 010955Z AUTO 05003KT 2 1/2SM BR OVC003 22/21 A2991"
        " RMK AO2=";  // 01 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 9, 55};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KFDK";
    refStation.autoType = Station::AutoType::AO2;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 50;
    refCurrent.weatherData.windSpeed = Speed{3, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY,
                 2 * 16 + 8,  // 2 1/2 = 2 8/16
                 Distance::Unit::STATUTE_MILE_1_16S};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{300, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::MIST, {}});
    refCurrent.weatherData.seaLevelPressure =
        Pressure{2991, Pressure::Unit::HUNDREDTHS_IN_HG};
    refCurrent.airTemperature = Temperature{22, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{21, Temperature::Unit::C};
    refCurrent.relativeHumidity = 94;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, visibility_3_4_sm) {
    static const auto rawReport =
        "KFDK 011147Z 00000KT 3/4SM BR OVC003 22/22 A2995=";  // 01 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 11, 47};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KFDK";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windCalm = true;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY,
                 12,  // 3/4 = 12/16
                 Distance::Unit::STATUTE_MILE_1_16S};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{300, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::MIST, {}});
    refCurrent.weatherData.seaLevelPressure =
        Pressure{2995, Pressure::Unit::HUNDREDTHS_IN_HG};
    refCurrent.airTemperature = Temperature{22, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{22, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, visibilityM1_4sm) {
    static const auto rawReport =
        "METAR K20U 011215Z AUTO M1/4SM FG VV000 11/11 A3024 RMK AO2=";
    // 01 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 12, 15};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "K20U";
    refStation.autoType = Station::AutoType::AO2;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::LESS_THAN,
                 4,  // 1/4 = 4/16
                 Distance::Unit::STATUTE_MILE_1_16S};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::OBSCURED;
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::FOG, {}});
    refCurrent.weatherData.verticalVisibility = Height{0, Height::Unit::FEET};
    refCurrent.weatherData.seaLevelPressure =
        Pressure{3024, Pressure::Unit::HUNDREDTHS_IN_HG};
    refCurrent.airTemperature = Temperature{11, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{11, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, visibilityP6sm) {
    static const auto rawReport =
        "TAF CYZU 011410Z 0114/0123 11012KT P6SM FEW040 SCT180"
        " RMK NXT FCST BY 011900Z=";  // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time{1, 14, 10};
    refReport.applicableFrom = Time{1, 14, 0};
    refReport.applicableUntil = Time{1, 23, 0};
    refReport.error = Report::Error::NO_ERROR;
    refReport.plainText.push_back("NXT FCST BY 011900Z");
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "CYZU";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    refForecast.prevailing.windDirectionDegrees = 110;
    refForecast.prevailing.windSpeed = Speed{12, Speed::Unit::KT};
    refForecast.prevailing.visibility = Distance{
        Distance::Details::MORE_THAN,
        6,
        Distance::Unit::STATUTE_MILES};
    refForecast.prevailing.skyCondition = Essentials::SkyCondition::CLOUDS;
    refForecast.prevailing.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.prevailing.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{18000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
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
    refCurrent.weatherData.seaLevelPressure =
        Pressure{2974, Pressure::Unit::HUNDREDTHS_IN_HG};
    refCurrent.airTemperature = Temperature{19, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{4, Temperature::Unit::C};
    refCurrent.relativeHumidity = 37;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}
