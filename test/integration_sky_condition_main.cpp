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
// Basic METAR report with various sky condition groups: CLR, SKC, NSC, NCD,
// one or multiple cloud layers (FEW, SCT, BKN, OVC) optionally with convective
// type (TCU, CB), and vertical visibility groups.
// These tests cover only main cloud conditions groups specified in METAR report
// or in METAR or TAF trends. They do not cover augmenting groups specified in
// remarks.
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationSkyCondition, skc) {
    static const auto rawReport =
        "METAR MMML 251944Z 17007KT 10SM SKC 37/11 A2981";  // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{25, 19, 44};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "MMML";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 170;
    refCurrent.weatherData.windSpeed = Speed{7, Speed::Unit::KT};
    refCurrent.weatherData.visibility = Distance{
        Distance::Details::EXACTLY,
        10,
        Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_SKC;
    refCurrent.airTemperature = Temperature{37, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{11, Temperature::Unit::C};
    refCurrent.relativeHumidity = 20;
    refCurrent.pressureSeaLevel =
        Pressure{2981, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationSkyCondition, clr) {
    static const auto rawReport =
        "METAR KBVS 252015Z AUTO 29010KT 10SM CLR 22/11 A3017 RMK A01=";
    // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.automated = true;
    refReport.reportTime = Time{25, 20, 15};
    refReport.error = Report::Error::NO_ERROR;
    refReport.plainText.push_back("A01");
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KBVS";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 290;
    refCurrent.weatherData.windSpeed = Speed{10, Speed::Unit::KT};
    refCurrent.weatherData.visibility = Distance{
        Distance::Details::EXACTLY,
        10,
        Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_CLR;
    refCurrent.airTemperature = Temperature{22, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{11, Temperature::Unit::C};
    refCurrent.relativeHumidity = 49;
    refCurrent.pressureSeaLevel =
        Pressure{3017, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationSkyCondition, nsc) {
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

TEST(IntegrationSkyCondition, ncd) {
    static const auto rawReport =
        "ESMT 252020Z AUTO 17009KT 9999 NCD 18/14 Q1010=";
    // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.automated = true;
    refReport.reportTime = Time{25, 20, 20};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ESMT";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 170;
    refCurrent.weatherData.windSpeed = Speed{9, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_NCD;
    refCurrent.airTemperature = Temperature{18, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{14, Temperature::Unit::C};
    refCurrent.relativeHumidity = 77;
    refCurrent.pressureSeaLevel = Pressure{1010, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationSkyCondition, oneCloudLayer) {
    static const auto rawReport =
        "METAR EPMO 011230Z VRB05KT 9999 SCT043 23/10 Q1016=";  // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 12, 30};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPMO";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionVariable = true;
    refCurrent.weatherData.windSpeed = Speed{5, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{4300, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{23, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{10, Temperature::Unit::C};
    refCurrent.relativeHumidity = 43;
    refCurrent.pressureSeaLevel = Pressure{1016, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationSkyCondition, twoCloudLayers) {
    static const auto rawReport =
        "EGYP 011150Z 01023KT 9999 SCT006 OVC009 05/04 Q1011=";  // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 11, 50};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EGYP";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 10;
    refCurrent.weatherData.windSpeed = Speed{23, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{600, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{900, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{5, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{4, Temperature::Unit::C};
    refCurrent.relativeHumidity = 93;
    refCurrent.pressureSeaLevel = Pressure{1011, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationSkyCondition, threeCloudLayers) {
    static const auto rawReport =
        "METAR EINN 011230Z 24015KT 9999 FEW016 SCT024 BKN044 16/11 Q1016"
        " NOSIG=";  // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 12, 30};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EINN";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 240;
    refCurrent.weatherData.windSpeed = Speed{15, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{1600, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{2400, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{4400, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{16, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{11, Temperature::Unit::C};
    refCurrent.relativeHumidity = 72;
    refCurrent.pressureSeaLevel = Pressure{1016, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    Forecast refForecast;
    refForecast.noSignificantChanges = true;
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
}

TEST(IntegrationSkyCondition, fourCloudLayers) {
    static const auto rawReport =
        "METAR EIKN 011230Z 23010KT 190V270 9999 SCT017 FEW018CB SCT036 BKN096"
        " 14/11 Q1015 NOSIG=";  // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 12, 30};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EIKN";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 230;
    refCurrent.weatherData.windSpeed = Speed{10, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 190;
    refCurrent.weatherData.windDirectionVarToDegrees = 270;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{1700, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{1800, Height::Unit::FEET},
                   CloudLayer::Details::CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{3600, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{9600, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{14, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{11, Temperature::Unit::C};
    refCurrent.relativeHumidity = 82;
    refCurrent.pressureSeaLevel = Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    Forecast refForecast;
    refForecast.noSignificantChanges = true;
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
}

TEST(IntegrationSkyCondition, verticalVisibility) {
    static const auto rawReport =
        "PFKW 011218Z AUTO 00000KT 1/2SM FG VV002 10/10 A2975 RMK AO2=";
    // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 12, 18};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "PFKW";
    refStation.autoType = Station::AutoType::AO2;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windCalm = true;
    refCurrent.weatherData.visibility = Distance{
        Distance::Details::EXACTLY,
        8,
        Distance::Unit::STATUTE_MILE_1_16S};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::OBSCURED;
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::FOG, {}});
    refCurrent.weatherData.verticalVisibility = 
        Height {200, Height::Unit::FEET};
    refCurrent.airTemperature = Temperature{10, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{10, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.pressureSeaLevel = 
        Pressure{2975, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibility, verticalVisibilityZero) {
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
    refCurrent.airTemperature = Temperature{11, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{11, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.pressureSeaLevel =
        Pressure{3024, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}