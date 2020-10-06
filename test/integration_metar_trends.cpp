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
// This file provides tests for METAR trends: NOSIG, FMxxxx, TLxxxx, ATxxxx,
// BECMG, TEMPO, INTER, xxxx/xxxx and their combinations
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationMetarTrends, nosig) {
    static const auto rawReport =
        "METAR UKLI 180600Z 00000MPS CAVOK 19/16 Q1010 NOSIG=";  // 18 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{18, 6, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "UKLI";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windCalm = true;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{19, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{16, Temperature::Unit::C};
    refCurrent.relativeHumidity = 82;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1010, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());

    Forecast refForecast;
    refForecast.noSignificantChanges = true;
    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationMetarTrends, tempo) {
    static const auto rawReport =
        "METAR VOVZ 182330Z 26009KT 6000 SCT014 OVC080 27/26 Q0998 TEMPO DZ=";
    // 18 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{18, 23, 30};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "VOVZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 260;
    refCurrent.weatherData.windSpeed = Speed{9, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 6000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{1400, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{8000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{27, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{26, Temperature::Unit::C};
    refCurrent.relativeHumidity = 94;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{998, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());

    Forecast refForecast;
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().metar = true;
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_MODERATE,
                {Weather::Precipitation::DRIZZLE}});

    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationMetarTrends, becmg) {
    static const auto rawReport =
        "METAR RJGG 182330Z 34006KT 9999 FEW020 BKN/// 29/24 Q1011"
        " BECMG 24005KT=";
    // 18 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{18, 23, 30};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "RJGG";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 340;
    refCurrent.weatherData.windSpeed = Speed{6, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{2000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height(),
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{29, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{24, Temperature::Unit::C};
    refCurrent.relativeHumidity = 74;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1011, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());

    Forecast refForecast;
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().metar = true;
    refForecast.trends.back().forecast.windDirectionDegrees = 240;
    refForecast.trends.back().forecast.windSpeed = Speed{5, Speed::Unit::KT};

    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationMetarTrends, fm) {
    static const auto rawReport =
        "METAR YBCS 182300Z AUTO 28003KT 9999 // NCD 22/16 Q1012"
        " FM0100 01009KT CAVOK=";  // 18 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{18, 23, 00};
    refReport.error = Report::Error::NO_ERROR;
    refReport.automated = true;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "YBCS";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 280;
    refCurrent.weatherData.windSpeed = Speed{3, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::UNKNOWN, {}});
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_NCD;
    refCurrent.airTemperature = Temperature{22, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{16, Temperature::Unit::C};
    refCurrent.relativeHumidity = 68;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1012, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());

    Forecast refForecast;
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{std::optional<int>(), 1, 0};
    refForecast.trends.back().metar = true;
    refForecast.trends.back().forecast.windDirectionDegrees = 10;
    refForecast.trends.back().forecast.windSpeed = Speed{9, Speed::Unit::KT};
    refForecast.trends.back().forecast.cavok = true;
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CAVOK;
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};

    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationMetarTrends, tempoFm) {
    static const auto rawReport =
        "METAR VVCI 182330Z 08004KT 9999 FEW020 SCT033 26/24 Q1004"
        " TEMPO FM0000 4000 RA=";  // 18 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{18, 23, 30};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "VVCI";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 80;
    refCurrent.weatherData.windSpeed = Speed{4, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{2000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{3300, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{26, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{24, Temperature::Unit::C};
    refCurrent.relativeHumidity = 88;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1004, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());

    Forecast refForecast;
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().timeFrom = Time{std::optional<int>(), 0, 0};
    refForecast.trends.back().metar = true;
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 4000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_MODERATE,
                {Weather::Precipitation::RAIN}});
    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationMetarTrends, becmgTl) {
    static const auto rawReport =
        "METAR ZBTJ 182330Z 03004MPS 360V060 9999 BKN006 OVC026 21/20 Q1009"
        " BECMG TL0030 SCT010=";  // 18 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{18, 23, 30};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZBTJ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 30;
    refCurrent.weatherData.windSpeed = Speed{4, Speed::Unit::MPS};
    refCurrent.weatherData.windDirectionVarFromDegrees = 360;
    refCurrent.weatherData.windDirectionVarToDegrees = 60;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{600, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{2600, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{21, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{20, Temperature::Unit::C};
    refCurrent.relativeHumidity = 94;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1009, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());

    Forecast refForecast;
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeUntil = Time{std::optional<int>(), 0, 30};
    refForecast.trends.back().metar = true;
    refForecast.trends.back().forecast.skyCondition = Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{1000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationMetarTrends, becmgAt) {
    static const auto rawReport =
        "METAR ZGOW 182300Z 12003MPS 070V160 9999 TS FEW013 FEW030CB BKN040 "
        "27/25 Q1008"
        " BECMG AT2330 NSW=";  // 18 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{18, 23, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZGOW";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 120;
    refCurrent.weatherData.windSpeed = Speed{3, Speed::Unit::MPS};
    refCurrent.weatherData.windDirectionVarFromDegrees = 70;
    refCurrent.weatherData.windDirectionVarToDegrees = 160;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::THUNDERSTORM, {}});
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{1300, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{27, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{25, Temperature::Unit::C};
    refCurrent.relativeHumidity = 88;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1008, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());

    Forecast refForecast;
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeAt = Time{std::optional<int>(), 23, 30};
    refForecast.trends.back().metar = true;
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::NO_SIGNIFICANT_WEATHER, {}});
    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationMetarTrends, interTimeSpan) {
    static const auto rawReport =
        "METAR YPAD 182300Z 25022KT 9999 FEW012 SCT049 BKN060 12/08 Q0998"
        " INTER 2300/0200 26025G35KT 3000 SHRA BKN015=";  // 18 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{18, 23, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "YPAD";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 250;
    refCurrent.weatherData.windSpeed = Speed{22, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{1200, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{4900, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{6000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{12, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{8, Temperature::Unit::C};
    refCurrent.relativeHumidity = 76;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{998, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());

    // INTER 2300/0200 26025G35KT 3000 SHRA BKN015
    Forecast refForecast;
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::INTER;
    refForecast.trends.back().timeFrom = Time{std::optional<int>(), 23, 0};
    refForecast.trends.back().timeUntil = Time{std::optional<int>(), 2, 0};
    refForecast.trends.back().metar = true;
    refForecast.trends.back().forecast.windDirectionDegrees = 260;
    refForecast.trends.back().forecast.windSpeed = Speed{25, Speed::Unit::KT};
    refForecast.trends.back().forecast.gustSpeed = Speed{35, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 3000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_MODERATE,
                {Weather::Precipitation::RAIN}});
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{1500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationMetarTrends, multipleTrends) {
    static const auto rawReport =
        "METAR YWLM 092200Z 27011KT 8000 -RA SCT012 BKN033 OVC090 10/10 Q1011"
        " FM2300 17020G32KT 9999 -SHRA FEW010 BKN020"
        " TEMPO 2200/0100 4000 SHRA BKN010=";  // 9 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{9, 22, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "YWLM";
    EXPECT_EQ(result.station, refStation);

    // 27011KT 8000 -RA SCT012 BKN033 OVC090 10/10 Q1011
    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 270;
    refCurrent.weatherData.windSpeed = Speed{11, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 8000, Distance::Unit::METERS};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{1200, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{3300, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{9000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{10, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{10, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1011, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());

    // FM2300 17020G32KT 9999 -SHRA FEW010 BKN020
    Forecast refForecast;
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{std::optional<int>(), 23, 0};
    refForecast.trends.back().metar = true;
    refForecast.trends.back().forecast.windDirectionDegrees = 170;
    refForecast.trends.back().forecast.windSpeed = Speed{20, Speed::Unit::KT};
    refForecast.trends.back().forecast.gustSpeed = Speed{32, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{1000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{2000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // TEMPO 2200/0100 4000 SHRA BKN010
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().metar = true;
    refForecast.trends.back().timeFrom = Time{std::optional<int>(), 22, 0};
    refForecast.trends.back().timeUntil = Time{std::optional<int>(), 1, 0};
    refForecast.trends.back().metar = true;
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 4000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_MODERATE,
                {Weather::Precipitation::RAIN}});
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{1000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationMetarTrends, tempoFmTl) {
    static const auto rawReport =
        "METAR VTSG 121700Z VRB02KT 9000 -RA SCT020 BKN100 24/24 Q1012"
        " TEMPO FM1730 TL1750 5000 RA=";  // 12 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{12, 17, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "VTSG";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionVariable = true;
    refCurrent.weatherData.windSpeed = Speed{2, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 9000, Distance::Unit::METERS};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{2000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{10000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{24, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{24, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1012, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());

    // TEMPO FM1730 TL1750 5000 RA
    Forecast refForecast;
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().timeFrom = Time{std::optional<int>(), 17, 30};
    refForecast.trends.back().timeUntil = Time{std::optional<int>(), 17, 50};
    refForecast.trends.back().metar = true;
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 5000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_MODERATE,
                {Weather::Precipitation::RAIN}});
    EXPECT_EQ(result.forecast, refForecast);
}
