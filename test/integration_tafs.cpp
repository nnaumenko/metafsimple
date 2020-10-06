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
// This file provides tests for various TAF features: trends, wind shear
// conditions, temperature, phenomena in vicinity, icing, turbulence, and
// pressure forecasts
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TAF reports with multiple trends: FMxxxxxx, TEMPO xxxx/xxxx, BECMG xxxx/xxxx,
// INTER xxxx/xxxx, PROBxx TEMPO xxxx/xxxx, PROBxx INTER xxxx/xxxx,
// PROBxx xxxx/xxxx, and invalid trend PROBxx without accompanying trend type.
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationTafs, trendBecmgFmTempoInterProbInter) {
    static const auto rawReport =
        "TAF YPEA 081704Z 0818/0912 03020G35KT 9999 -RA NSC"
        " BECMG 0900/0901 01030G45KT 9999 -RA SCT025 BKN040"
        " FM090400 33018G32KT 9999 -SHRA SCT025 SCT040"
        " FM091000 34014KT 9999 -SHRA SCT020 BKN030"
        " TEMPO 0822/0904 5000 RA SCT020"
        " INTER 0906/0912 VRB20G35KT 2000 TSRA BKN010 FEW030CB"
        " PROB30 INTER 0903/0906 VRB30G50KT 2000 TSRA BKN008 FEW030CB=";
    // 8 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time{8, 17, 04};
    refReport.applicableFrom = Time{8, 18, 0};
    refReport.applicableUntil = Time{9, 12, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "YPEA";
    EXPECT_EQ(result.station, refStation);

    // 0818/0912 03020G35KT 9999 -RA NSC
    Forecast refForecast;
    refForecast.prevailing.windDirectionDegrees = 30;
    refForecast.prevailing.windSpeed = Speed{20, Speed::Unit::KT};
    refForecast.prevailing.gustSpeed = Speed{35, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.prevailing.skyCondition =
        Essentials::SkyCondition::NO_SIGNIFICANT_CLOUD;
    refForecast.prevailing.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});

    // BECMG 0900/0901 01030G45KT 9999 -RA SCT025 BKN040
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{9, 0, 0};
    refForecast.trends.back().timeUntil = Time{9, 1, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 10;
    refForecast.trends.back().forecast.windSpeed = Speed{30, Speed::Unit::KT};
    refForecast.trends.back().forecast.gustSpeed = Speed{45, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{2500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});

    // FM090400 33018G32KT 9999 -SHRA SCT025 SCT040
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{9, 4, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 330;
    refForecast.trends.back().forecast.windSpeed = Speed{18, Speed::Unit::KT};
    refForecast.trends.back().forecast.gustSpeed = Speed{32, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{2500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});

    // FM091000 34014KT 9999 -SHRA SCT020 BKN030
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{9, 10, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 340;
    refForecast.trends.back().forecast.windSpeed = Speed{14, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{2000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});

    // TEMPO 0822/0904 5000 RA SCT020
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().timeFrom = Time{8, 22, 0};
    refForecast.trends.back().timeUntil = Time{9, 4, 0};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 5000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{2000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_MODERATE,
                {Weather::Precipitation::RAIN}});

    // INTER 0906/0912 VRB20G35KT 2000 TSRA BKN010 FEW030CB
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::INTER;
    refForecast.trends.back().timeFrom = Time{9, 6, 0};
    refForecast.trends.back().timeUntil = Time{9, 12, 0};
    refForecast.trends.back().forecast.windDirectionVariable = true;
    refForecast.trends.back().forecast.windSpeed = Speed{20, Speed::Unit::KT};
    refForecast.trends.back().forecast.gustSpeed = Speed{35, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 2000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{1000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::THUNDERSTORM_PRECIPITATION_MODERATE,
                {Weather::Precipitation::RAIN}});

    // PROB30 INTER 0903/0906 VRB30G50KT 2000 TSRA BKN008 FEW030CB
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::INTER;
    refForecast.trends.back().probability = 30;
    refForecast.trends.back().timeFrom = Time{9, 3, 0};
    refForecast.trends.back().timeUntil = Time{9, 6, 0};
    refForecast.trends.back().forecast.windDirectionVariable = true;
    refForecast.trends.back().forecast.windSpeed = Speed{30, Speed::Unit::KT};
    refForecast.trends.back().forecast.gustSpeed = Speed{50, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 2000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{800, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::THUNDERSTORM_PRECIPITATION_MODERATE,
                {Weather::Precipitation::RAIN}});
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}

TEST(IntegrationTafs, trendProbTempo) {
    static const auto rawReport =
        "TAF NFNA 051103Z 0512/0612 12005KT 9999 SCT025 BKN048"
        " PROB30 TEMPO 0512/0520 5000 SHRA BKN015"
        " PROB40 TEMPO 0603/0612 5000 SHRA BKN015=";  // 5 AUG 2020
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time{5, 11, 3};
    refReport.applicableFrom = Time{5, 12, 0};
    refReport.applicableUntil = Time{6, 12, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "NFNA";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    // 0512/0612 12005KT 9999 SCT025 BKN048
    refForecast.prevailing.windDirectionDegrees = 120;
    refForecast.prevailing.windSpeed = Speed{5, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.prevailing.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.prevailing.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{2500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.prevailing.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{4800, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // PROB30 TEMPO 0512/0520 5000 SHRA BKN015
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().probability = 30;
    refForecast.trends.back().timeFrom = Time{5, 12, 0};
    refForecast.trends.back().timeUntil = Time{5, 20, 0};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 5000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{1500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_MODERATE,
                {Weather::Precipitation::RAIN}});

    // PROB40 TEMPO 0603/0612 5000 SHRA BKN015
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().probability = 40;
    refForecast.trends.back().timeFrom = Time{6, 3, 0};
    refForecast.trends.back().timeUntil = Time{6, 12, 0};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 5000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{1500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_MODERATE,
                {Weather::Precipitation::RAIN}});

    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}

TEST(IntegrationTafs, trendProbTimedAndRemark) {
    static const auto rawReport =
        "TAF AMD CYGL 082048Z 0820/0918 24010G20KT P6SM FEW015 BKN090"
        " TEMPO 0820/0824 5SM -SHRA BR FEW008 BKN015"
        " PROB30 0820/0824 VRB20G30KT 2SM TSRA BR OVC040CB"
        " FM090000 28008KT P6SM BKN020"
        " TEMPO 0900/0903 2SM -DZ BR OVC004"
        " FM090300 VRB03KT P6SM SCT002"
        " PROB30 0903/0909 1/2SM -DZ FG VV002"
        " FM090900 VRB03KT 2SM BR BKN004"
        " PROB40 0909/0912 1/2SM -DZ FG VV002"
        " FM091500 13007KT P6SM FEW020"
        " RMK NXT FCST BY 090000Z=";  // 8 AUG 2020
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time{8, 20, 48};
    refReport.applicableFrom = Time{8, 20, 0};
    refReport.applicableUntil = Time{9, 18, 0};
    refReport.amended = true;
    refReport.error = Report::Error::NO_ERROR;
    refReport.plainText.push_back("NXT FCST BY 090000Z");
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "CYGL";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    // 0820/0918 24010G20KT P6SM FEW015 BKN090
    refForecast.prevailing.windDirectionDegrees = 240;
    refForecast.prevailing.windSpeed = Speed{10, Speed::Unit::KT};
    refForecast.prevailing.gustSpeed = Speed{20, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.prevailing.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.prevailing.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{1500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.prevailing.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{9000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // TEMPO 0820/0824 5SM -SHRA BR FEW008 BKN015
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().timeFrom = Time{8, 20, 0};
    refForecast.trends.back().timeUntil = Time{8, 24, 0};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 5, Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::MIST, {}});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{800, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{1500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // PROB30 0820/0824 VRB20G30KT 2SM TSRA BR OVC040CB
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().probability = 30;
    refForecast.trends.back().timeFrom = Time{8, 20, 0};
    refForecast.trends.back().timeUntil = Time{8, 24, 0};
    refForecast.trends.back().forecast.windDirectionVariable = true;
    refForecast.trends.back().forecast.windSpeed = Speed{20, Speed::Unit::KT};
    refForecast.trends.back().forecast.gustSpeed = Speed{30, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 2, Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::THUNDERSTORM_PRECIPITATION_MODERATE,
                {Weather::Precipitation::RAIN}});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::MIST, {}});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::CUMULONIMBUS,
                   std::optional<int>()});

    // FM090000 28008KT P6SM BKN020
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{9, 0, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 280;
    refForecast.trends.back().forecast.windSpeed = Speed{8, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{2000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // TEMPO 0900/0903 2SM -DZ BR OVC004
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().timeFrom = Time{9, 0, 0};
    refForecast.trends.back().timeUntil = Time{9, 3, 0};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 2, Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_LIGHT,
                {Weather::Precipitation::DRIZZLE}});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::MIST, {}});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{400, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // FM090300 VRB03KT P6SM SCT002
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{9, 3, 0};
    refForecast.trends.back().forecast.windDirectionVariable = true;
    refForecast.trends.back().forecast.windSpeed = Speed{3, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{200, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // PROB30 0903/0909 1/2SM -DZ FG VV002
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().probability = 30;
    refForecast.trends.back().timeFrom = Time{9, 3, 0};
    refForecast.trends.back().timeUntil = Time{9, 9, 0};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY,
                 8,  // 1/2 = 8/16
                 Distance::Unit::STATUTE_MILE_1_16S};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::OBSCURED;
    refForecast.trends.back().forecast.verticalVisibility =
        Height{200, Height::Unit::FEET};
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_LIGHT,
                {Weather::Precipitation::DRIZZLE}});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::FOG, {}});

    // FM090900 VRB03KT 2SM BR BKN004
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{9, 9, 0};
    refForecast.trends.back().forecast.windDirectionVariable = true;
    refForecast.trends.back().forecast.windSpeed = Speed{3, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 2, Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{400, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::MIST, {}});

    // PROB40 0909/0912 1/2SM -DZ FG VV002
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().probability = 40;
    refForecast.trends.back().timeFrom = Time{9, 9, 0};
    refForecast.trends.back().timeUntil = Time{9, 12, 0};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY,
                 8,  // 1/2 = 8/16
                 Distance::Unit::STATUTE_MILE_1_16S};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::OBSCURED;
    refForecast.trends.back().forecast.verticalVisibility =
        Height{200, Height::Unit::FEET};
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_LIGHT,
                {Weather::Precipitation::DRIZZLE}});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::FOG, {}});

    // FM091500 13007KT P6SM FEW020
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{9, 15, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 130;
    refForecast.trends.back().forecast.windSpeed = Speed{7, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{
            Distance::Details::MORE_THAN,
            6,
            Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{2000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}

TEST(IntegrationTafs, probOnly) {
    static const auto rawReport =
        "TAF ZZZZ 091750Z 0918/1018 27014KT CAVOK"
        " PROB30 VRB05KT=";  // Fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time{9, 17, 50};
    refReport.applicableFrom = Time{9, 18, 0};
    refReport.applicableUntil = Time{10, 18, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    // 0918/1018 27014KT CAVOK
    refForecast.prevailing.windDirectionDegrees = 270;
    refForecast.prevailing.windSpeed = Speed{14, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{Distance::Details::MORE_THAN,
                 10000,
                 Distance::Unit::METERS};
    refForecast.prevailing.skyCondition =
        Essentials::SkyCondition::CAVOK;
    refForecast.prevailing.cavok = true;

    // PROB30 VRB05KT
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::PROB;
    refForecast.trends.back().probability = 30;
    refForecast.trends.back().forecast.windDirectionVariable = true;
    refForecast.trends.back().forecast.windSpeed = Speed{5, Speed::Unit::KT};
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}

TEST(IntegrationTafs, turbulenceForecast) {
    static const auto rawReport =
        "TAF EGYP 081931Z 0821/0915 35015G25KT 9999 BKN010 520003"
        " BECMG 0821/0824 31015KT 50////"
        " PROB30 TEMPO 0821/0824 VRB08KT 560003"
        " PROB30 TEMPO 0821/0909 2000 +RADZ SCT004"
        " BECMG 0903/0906 19025G35KT"
        " BECMG 0908/0911 BKN016"
        " PROB40 TEMPO 0909/0915 4000 SHRASN SCT012"
        " BECMG 0912/0915 20013KT SCT025";  //8 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time{8, 19, 31};
    refReport.applicableFrom = Time{8, 21, 0};
    refReport.applicableUntil = Time{9, 15, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EGYP";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    // 0821/0915 35015G25KT 9999 BKN010 520003
    refForecast.prevailing.windDirectionDegrees = 350;
    refForecast.prevailing.windSpeed = Speed{15, Speed::Unit::KT};
    refForecast.prevailing.gustSpeed = Speed{25, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.prevailing.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.prevailing.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{1000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.prevailingTurbulence.push_back(
        TurbulenceForecast{
            TurbulenceForecast::Severity::MODERATE,
            TurbulenceForecast::Location::IN_CLEAR_AIR,
            TurbulenceForecast::Frequency::OCCASIONAL,
            Height{0, Height::Unit::FEET},
            Height{3000, Height::Unit::FEET},
        });
    // BECMG 0821/0824 31015KT 50///
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{8, 21, 0};
    refForecast.trends.back().timeUntil = Time{8, 24, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 310;
    refForecast.trends.back().forecast.windSpeed = Speed{15, Speed::Unit::KT};
    refForecast.trends.back().turbulence.push_back(
        TurbulenceForecast{
            TurbulenceForecast::Severity::NONE,
            TurbulenceForecast::Location::NONE,
            TurbulenceForecast::Frequency::NONE,
            Height(),
            Height(),
        });

    // PROB30 TEMPO 0821/0824 VRB08KT 560003
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().probability = 30;
    refForecast.trends.back().timeFrom = Time{8, 21, 0};
    refForecast.trends.back().timeUntil = Time{8, 24, 0};
    refForecast.trends.back().forecast.windDirectionVariable = true;
    refForecast.trends.back().forecast.windSpeed = Speed{8, Speed::Unit::KT};
    refForecast.trends.back().turbulence.push_back(
        TurbulenceForecast{
            TurbulenceForecast::Severity::SEVERE,
            TurbulenceForecast::Location::IN_CLEAR_AIR,
            TurbulenceForecast::Frequency::OCCASIONAL,
            Height{0, Height::Unit::FEET},
            Height{3000, Height::Unit::FEET},
        });

    // PROB30 TEMPO 0821/0909 2000 +RADZ SCT004"
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().probability = 30;
    refForecast.trends.back().timeFrom = Time{8, 21, 0};
    refForecast.trends.back().timeUntil = Time{9, 9, 0};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 2000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_HEAVY,
                {Weather::Precipitation::RAIN,
                 Weather::Precipitation::DRIZZLE}});
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{400, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // BECMG 0903/0906 19025G35KT
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{9, 3, 0};
    refForecast.trends.back().timeUntil = Time{9, 6, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 190;
    refForecast.trends.back().forecast.windSpeed = Speed{25, Speed::Unit::KT};
    refForecast.trends.back().forecast.gustSpeed = Speed{35, Speed::Unit::KT};

    // BECMG 0908/0911 BKN016
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{9, 8, 0};
    refForecast.trends.back().timeUntil = Time{9, 11, 0};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{1600, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // PROB40 TEMPO 0909/0915 4000 SHRASN SCT012
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().probability = 40;
    refForecast.trends.back().timeFrom = Time{9, 9, 0};
    refForecast.trends.back().timeUntil = Time{9, 15, 0};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 4000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_MODERATE,
                {Weather::Precipitation::RAIN, Weather::Precipitation::SNOW}});
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{1200, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // BECMG 0912/0915 20013KT SCT025
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{9, 12, 0};
    refForecast.trends.back().timeUntil = Time{9, 15, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 200;
    refForecast.trends.back().forecast.windSpeed = Speed{13, Speed::Unit::KT};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{2500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}

TEST(IntegrationTafs, vicinityInPrevailing) {
    static const auto rawReport =
        "KBTV 051501Z 0515/0612 22009G19KT P6SM VCSH BKN035"
        " TEMPO 0515/0517 VRB20G30KT 3SM -SHRA BR BKN020"
        " FM051700 24010G20KT P6SM SCT050"
        " FM052300 26005KT P6SM FEW250=";  // 5 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time{5, 15, 1};
    refReport.applicableFrom = Time{5, 15, 0};
    refReport.applicableUntil = Time{6, 12, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KBTV";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    // 0515/0612 22009G19KT P6SM VCSH BKN035
    refForecast.prevailing.windDirectionDegrees = 220;
    refForecast.prevailing.windSpeed = Speed{9, Speed::Unit::KT};
    refForecast.prevailing.gustSpeed = Speed{19, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.prevailing.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.prevailing.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{3500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.prevailingVicinity.insert(ObservedPhenomena::PRECIPITATION);

    // TEMPO 0515/0517 VRB20G30KT 3SM -SHRA BR BKN020
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().timeFrom = Time{5, 15, 0};
    refForecast.trends.back().timeUntil = Time{5, 17, 0};
    refForecast.trends.back().forecast.windDirectionVariable = true;
    refForecast.trends.back().forecast.windSpeed = Speed{20, Speed::Unit::KT};
    refForecast.trends.back().forecast.gustSpeed = Speed{30, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 3, Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::MIST, {}});
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{2000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // FM051700 24010G20KT P6SM SCT050
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{5, 17, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 240;
    refForecast.trends.back().forecast.windSpeed = Speed{10, Speed::Unit::KT};
    refForecast.trends.back().forecast.gustSpeed = Speed{20, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{5000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // FM052300 26005KT P6SM FEW250
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{5, 23, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 260;
    refForecast.trends.back().forecast.windSpeed = Speed{5, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{25000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}

TEST(IntegrationTafTrends, icingPressureTempForecastVicinityInTrend) {
    static const auto rawReport =
        "TAF PAEI 081404Z 0814/0920 20004KT 9999 FEW025 BKN040 "
        "620709 QNH2969INS"
        " BECMG 0816/0817 21009KT 9999 FEW018 BKN030 OVC040 620759 QNH2972INS"
        " BECMG 0821/0822 22009KT 9999 FEW030 BKN055 620759 QNH2975INS"
        " BECMG 0900/0901 24009KT 9999 VCSH FEW030 BKN040 610751 620859 "
        "QNH2977INS"
        " TEMPO 0901/0904 VRB10G15KT 9000 -SHRA VCTS SCT030 BKN040CB"
        " BECMG 0906/0907 VRB02KT 9999 NSW FEW030 BKN040 620759 QNH2976INS"
        " BECMG 0913/0914 VRB02KT 4800 BR FEW030 BKN050 620709 QNH2974INS"
        " BECMG 0916/0917 VRB02KT 9999 VCSH FEW025 BKN040"
        " 610751 620859 QNH2969INS"
        " TX21/0900Z TN10/0814Z=";  //8 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time{8, 14, 4};
    refReport.applicableFrom = Time{8, 14, 0};
    refReport.applicableUntil = Time{9, 20, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "PAEI";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    // 0814/0920 20004KT 9999 FEW025 BKN040 620709 QNH2969INS
    refForecast.prevailing.windDirectionDegrees = 200;
    refForecast.prevailing.windSpeed = Speed{4, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.prevailing.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.prevailing.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{2500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.prevailing.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.prevailingIcing.push_back(
        IcingForecast{
            IcingForecast::Severity::LIGHT,
            IcingForecast::Type::RIME_IN_CLOUD,
            Height{7000, Height::Unit::FEET},
            Height{16000, Height::Unit::FEET}});
    refForecast.prevailing.seaLevelPressure =
        Pressure{2969, Pressure::Unit::HUNDREDTHS_IN_HG};

    // BECMG 0816/0817 21009KT 9999 FEW018 BKN030 OVC040 620759 QNH2972INS
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{8, 16, 0};
    refForecast.trends.back().timeUntil = Time{8, 17, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 210;
    refForecast.trends.back().forecast.windSpeed = Speed{9, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{1800, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().icing.push_back(
        IcingForecast{
            IcingForecast::Severity::LIGHT,
            IcingForecast::Type::RIME_IN_CLOUD,
            Height{7500, Height::Unit::FEET},
            Height{16500, Height::Unit::FEET}});
    refForecast.trends.back().forecast.seaLevelPressure =
        Pressure{2972, Pressure::Unit::HUNDREDTHS_IN_HG};

    // BECMG 0821/0822 22009KT 9999 FEW030 BKN055 620759 QNH2975INS
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{8, 21, 0};
    refForecast.trends.back().timeUntil = Time{8, 22, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 220;
    refForecast.trends.back().forecast.windSpeed = Speed{9, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{5500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().icing.push_back(
        IcingForecast{
            IcingForecast::Severity::LIGHT,
            IcingForecast::Type::RIME_IN_CLOUD,
            Height{7500, Height::Unit::FEET},
            Height{16500, Height::Unit::FEET}});
    refForecast.trends.back().forecast.seaLevelPressure =
        Pressure{2975, Pressure::Unit::HUNDREDTHS_IN_HG};

    // BECMG 0900/0901 24009KT 9999 VCSH FEW030 BKN040 610751 620859 QNH2977INS
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{9, 0, 0};
    refForecast.trends.back().timeUntil = Time{9, 1, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 240;
    refForecast.trends.back().forecast.windSpeed = Speed{9, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.trends.back().vicinity.insert(ObservedPhenomena::PRECIPITATION);
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().icing.push_back(
        IcingForecast{
            IcingForecast::Severity::LIGHT,
            IcingForecast::Type::MIXED,
            Height{7500, Height::Unit::FEET},
            Height{8500, Height::Unit::FEET}});
    refForecast.trends.back().icing.push_back(
        IcingForecast{
            IcingForecast::Severity::LIGHT,
            IcingForecast::Type::RIME_IN_CLOUD,
            Height{8500, Height::Unit::FEET},
            Height{17500, Height::Unit::FEET}});
    refForecast.trends.back().forecast.seaLevelPressure =
        Pressure{2977, Pressure::Unit::HUNDREDTHS_IN_HG};

    // TEMPO 0901/0904 VRB10G15KT 9000 -SHRA VCTS SCT030 BKN040CB
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().timeFrom = Time{9, 1, 0};
    refForecast.trends.back().timeUntil = Time{9, 4, 0};
    refForecast.trends.back().forecast.windDirectionVariable = true;
    refForecast.trends.back().forecast.windSpeed = Speed{10, Speed::Unit::KT};
    refForecast.trends.back().forecast.gustSpeed = Speed{15, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 9000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});
    refForecast.trends.back().vicinity.insert(ObservedPhenomena::THUNDERSTORM);
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::CUMULONIMBUS,
                   std::optional<int>()});

    // BECMG 0906/0907 VRB02KT 9999 NSW FEW030 BKN040 620759 QNH2976INS
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{9, 6, 0};
    refForecast.trends.back().timeUntil = Time{9, 7, 0};
    refForecast.trends.back().forecast.windDirectionVariable = true;
    refForecast.trends.back().forecast.windSpeed = Speed{2, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::NO_SIGNIFICANT_WEATHER, {}});
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().icing.push_back(
        IcingForecast{
            IcingForecast::Severity::LIGHT,
            IcingForecast::Type::RIME_IN_CLOUD,
            Height{7500, Height::Unit::FEET},
            Height{16500, Height::Unit::FEET}});
    refForecast.trends.back().forecast.seaLevelPressure =
        Pressure{2976, Pressure::Unit::HUNDREDTHS_IN_HG};

    // BECMG 0913/0914 VRB02KT 4800 BR FEW030 BKN050 620709 QNH2974INS
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{9, 13, 0};
    refForecast.trends.back().timeUntil = Time{9, 14, 0};
    refForecast.trends.back().forecast.windDirectionVariable = true;
    refForecast.trends.back().forecast.windSpeed = Speed{2, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::EXACTLY, 4800, Distance::Unit::METERS};
    refForecast.trends.back().forecast.weather.push_back(
        Weather{Weather::Phenomena::MIST, {}});
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{5000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().icing.push_back(
        IcingForecast{
            IcingForecast::Severity::LIGHT,
            IcingForecast::Type::RIME_IN_CLOUD,
            Height{7000, Height::Unit::FEET},
            Height{16000, Height::Unit::FEET}});
    refForecast.trends.back().forecast.seaLevelPressure =
        Pressure{2974, Pressure::Unit::HUNDREDTHS_IN_HG};

    // BECMG 0916/0917 VRB02KT 9999 VCSH FEW025 BKN040 610751 620859 QNH2969INS
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{9, 16, 0};
    refForecast.trends.back().timeUntil = Time{9, 17, 0};
    refForecast.trends.back().forecast.windDirectionVariable = true;
    refForecast.trends.back().forecast.windSpeed = Speed{2, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.trends.back().vicinity.insert(ObservedPhenomena::PRECIPITATION);
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{2500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().icing.push_back(
        IcingForecast{
            IcingForecast::Severity::LIGHT,
            IcingForecast::Type::MIXED,
            Height{7500, Height::Unit::FEET},
            Height{8500, Height::Unit::FEET}});
    refForecast.trends.back().icing.push_back(
        IcingForecast{
            IcingForecast::Severity::LIGHT,
            IcingForecast::Type::RIME_IN_CLOUD,
            Height{8500, Height::Unit::FEET},
            Height{17500, Height::Unit::FEET}});
    refForecast.trends.back().forecast.seaLevelPressure =
        Pressure{2969, Pressure::Unit::HUNDREDTHS_IN_HG};

    //TX21/0900Z TN10/0814Z
    refForecast.maxTemperature.push_back(TemperatureForecast{
        Temperature{21, Temperature::Unit::C},
        Time{9, 0, 0}});
    refForecast.minTemperature.push_back(TemperatureForecast{
        Temperature{10, Temperature::Unit::C},
        Time{8, 14, 0}});
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}

TEST(IntegrationTafs, tempForecastMultipleTx) {
    static const auto rawReport =
        "TAF RKNY 122300Z 1300/1406 26006KT CAVOK"
        " TX33/1306Z TN28/1319Z TX32/1406Z"
        " BECMG 1303/1304 9999 FEW030 BKN100"
        " BECMG 1305/1306 17007KT"
        " BECMG 1322/1323 25009KT=";  //12 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time{12, 23, 0};
    refReport.applicableFrom = Time{13, 0, 0};
    refReport.applicableUntil = Time{14, 6, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "RKNY";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    // 1300/1406 26006KT CAVOK
    refForecast.prevailing.windDirectionDegrees = 260;
    refForecast.prevailing.windSpeed = Speed{6, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.prevailing.skyCondition =
        Essentials::SkyCondition::CAVOK;
    refForecast.prevailing.cavok = true;

    // BECMG 1303/1304 9999 FEW030 BKN100
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{13, 3, 0};
    refForecast.trends.back().timeUntil = Time{13, 4, 0};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{10000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // BECMG 1305/1306 17007KT
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{13, 5, 0};
    refForecast.trends.back().timeUntil = Time{13, 6, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 170;
    refForecast.trends.back().forecast.windSpeed = Speed{7, Speed::Unit::KT};

    // BECMG 1322/1323 25009KT
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::BECMG;
    refForecast.trends.back().timeFrom = Time{13, 22, 0};
    refForecast.trends.back().timeUntil = Time{13, 23, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 250;
    refForecast.trends.back().forecast.windSpeed = Speed{9, Speed::Unit::KT};

    // TX33/1306Z TN28/1319Z TX32/1406Z
    refForecast.maxTemperature.push_back(TemperatureForecast{
        Temperature{33, Temperature::Unit::C},
        Time{13, 6, 0}});
    refForecast.maxTemperature.push_back(TemperatureForecast{
        Temperature{32, Temperature::Unit::C},
        Time{14, 6, 0}});
    refForecast.minTemperature.push_back(TemperatureForecast{
        Temperature{28, Temperature::Unit::C},
        Time{13, 19, 0}});
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}

TEST(IntegrationTafs, tempForecastMultipleTn) {
    static const auto rawReport =
        "TAF LSZH 100225Z 1003/1109 VRB02KT CAVOK"
        " TX31/1015Z TN14/1005Z TN16/1105Z"
        " PROB30 TEMPO 1014/1020 9999 FEW080CB=";  // 10 AUG 2020
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time{10, 2, 25};
    refReport.applicableFrom = Time{10, 3, 0};
    refReport.applicableUntil = Time{11, 9, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "LSZH";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    // 1003/1109 VRB02KT CAVOK
    refForecast.prevailing.windDirectionVariable = true;
    refForecast.prevailing.windSpeed = Speed{2, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.prevailing.skyCondition =
        Essentials::SkyCondition::CAVOK;
    refForecast.prevailing.cavok = true;

    // PROB30 TEMPO 1014/1020 9999 FEW080CB
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().probability = 30;
    refForecast.trends.back().timeFrom = Time{10, 14, 0};
    refForecast.trends.back().timeUntil = Time{10, 20, 0};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{8000, Height::Unit::FEET},
                   CloudLayer::Details::CUMULONIMBUS,
                   std::optional<int>()});

    // TX31/1015Z TN14/1005Z TN16/1105Z
    refForecast.maxTemperature.push_back(TemperatureForecast{
        Temperature{31, Temperature::Unit::C},
        Time{10, 15, 0}});
    refForecast.minTemperature.push_back(TemperatureForecast{
        Temperature{14, Temperature::Unit::C},
        Time{10, 5, 0}});
    refForecast.minTemperature.push_back(TemperatureForecast{
        Temperature{16, Temperature::Unit::C},
        Time{11, 5, 0}});
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}

TEST(IntegrationTafs, windShearInPrevailing) {
    static const auto rawReport =
        "TAF KSTJ 101120Z 1012/1112 19008KT P6SM FEW150 WS020/22040KT"
        " FM101300 20010KT P6SM BKN150"
        " FM101900 21007KT P6SM VCTS SCT040CB BKN250"
        " FM102200 07006KT P6SM VCTS SCT040CB BKN250"
        " FM110400 09009KT P6SM BKN250=";  //10 AUG 2020
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time{10, 11, 20};
    refReport.applicableFrom = Time{10, 12, 0};
    refReport.applicableUntil = Time{11, 12, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KSTJ";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    // 1012/1112 19008KT P6SM FEW150 WS020/22040KT
    refForecast.prevailing.windDirectionDegrees = 190;
    refForecast.prevailing.windSpeed = Speed{8, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{
            Distance::Details::MORE_THAN,
            6,
            Distance::Unit::STATUTE_MILES};
    refForecast.prevailing.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.prevailing.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{15000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.prevailing.windShear.push_back(
        WindShear{
            Height{2000, Height::Unit::FEET},
            220,
            Speed{40, Speed::Unit::KT}});

    // FM101300 20010KT P6SM BKN150
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{10, 13, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 200;
    refForecast.trends.back().forecast.windSpeed = Speed{10, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{15000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // FM101900 21007KT P6SM VCTS SCT040CB BKN250
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{10, 19, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 210;
    refForecast.trends.back().forecast.windSpeed = Speed{7, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{25000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().vicinity.insert(ObservedPhenomena::THUNDERSTORM);

    // FM102200 07006KT P6SM VCTS SCT040CB BKN250
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{10, 22, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 70;
    refForecast.trends.back().forecast.windSpeed = Speed{6, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{4000, Height::Unit::FEET},
                   CloudLayer::Details::CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{25000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().vicinity.insert(ObservedPhenomena::THUNDERSTORM);

    // FM110400 09009KT P6SM BKN250
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{11, 4, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 90;
    refForecast.trends.back().forecast.windSpeed = Speed{9, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{25000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}

TEST(IntegrationTafs, windShearInTrend) {
    static const auto rawReport =
        "TAF KVTN 131737Z 1318/1418 21007KT P6SM SKC"
        " FM132000 28007KT P6SM SKC"
        " FM132100 31006KT P6SM SKC"
        " FM132300 36007KT P6SM FEW200"
        " FM141100 20011KT P6SM SCT035 SCT200 WS020/22040KT"
        " FM141300 22012KT P6SM FEW035="; // 13 AUG 2020
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time{13, 17, 37};
    refReport.applicableFrom = Time{13, 18, 0};
    refReport.applicableUntil = Time{14, 18, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KVTN";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    // 1318/1418 21007KT P6SM SKC
    refForecast.prevailing.windDirectionDegrees = 210;
    refForecast.prevailing.windSpeed = Speed{7, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{
            Distance::Details::MORE_THAN,
            6,
            Distance::Unit::STATUTE_MILES};
    refForecast.prevailing.skyCondition =
        Essentials::SkyCondition::CLEAR_SKC;

    // FM132000 28007KT P6SM SKC
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{13, 20, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 280;
    refForecast.trends.back().forecast.windSpeed = Speed{7, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLEAR_SKC;

    // FM132100 31006KT P6SM SKC
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{13, 21, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 310;
    refForecast.trends.back().forecast.windSpeed = Speed{6, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLEAR_SKC;

    // FM132300 36007KT P6SM FEW200
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{13, 23, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 360;
    refForecast.trends.back().forecast.windSpeed = Speed{7, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{20000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});

    // FM141100 20011KT P6SM SCT035 SCT200 WS020/22040KT
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{14, 11, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 200;
    refForecast.trends.back().forecast.windSpeed = Speed{11, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{3500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{20000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.trends.back().forecast.windShear.push_back(
        WindShear{
            Height{2000, Height::Unit::FEET},
            220,
            Speed{40, Speed::Unit::KT}});

    // FM141300 22012KT P6SM FEW035
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{14, 13, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 220;
    refForecast.trends.back().forecast.windSpeed = Speed{12, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN,
                 6,
                 Distance::Unit::STATUTE_MILES};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refForecast.trends.back().forecast.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{3500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}

TEST(IntegrationTafs, wscondsInTrend) {
    static const auto rawReport =
        "TAF KNJK 0615/0715 25020G25KT 9999 SKC 520009 QNH2963INS"
        " TEMPO 0616/0618 25015KT"
        " FM070500 25008KT 9999 SKC WSCONDS 530009 QNH2970INS"
        " T40/0622Z T25/0713Z"
        " FS30130=";  //6 AUG 2020
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time();
    refReport.applicableFrom = Time{6, 15, 0};
    refReport.applicableUntil = Time{7, 15, 0};
    refReport.error = Report::Error::NO_ERROR;
    refReport.plainText.push_back("FS30130");
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KNJK";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    // 0615/0715 25020G25KT 9999 SKC 520009 QNH2963INS
    refForecast.prevailing.windDirectionDegrees = 250;
    refForecast.prevailing.windSpeed = Speed{20, Speed::Unit::KT};
    refForecast.prevailing.gustSpeed = Speed{25, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{
            Distance::Details::MORE_THAN,
            10000,
            Distance::Unit::METERS};
    refForecast.prevailing.skyCondition =
        Essentials::SkyCondition::CLEAR_SKC;
    refForecast.prevailingTurbulence.push_back(
        TurbulenceForecast{
            TurbulenceForecast::Severity::MODERATE,
            TurbulenceForecast::Location::IN_CLEAR_AIR,
            TurbulenceForecast::Frequency::OCCASIONAL,
            Height{0, Height::Unit::FEET},
            Height{9000, Height::Unit::FEET},
        });
    refForecast.prevailing.seaLevelPressure =
        Pressure{2963, Pressure::Unit::HUNDREDTHS_IN_HG};

    // TEMPO 0616/0618 25015KT
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TEMPO;
    refForecast.trends.back().timeFrom = Time{6, 16, 0};
    refForecast.trends.back().timeUntil = Time{6, 18, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 250;
    refForecast.trends.back().forecast.windSpeed = Speed{15, Speed::Unit::KT};

    // FM070500 25008KT 9999 SKC WSCONDS 530009 QNH2970INS
    refForecast.trends.push_back(Trend());
    refForecast.trends.back().type = Trend::Type::TIMED;
    refForecast.trends.back().timeFrom = Time{7, 5, 0};
    refForecast.trends.back().forecast.windDirectionDegrees = 250;
    refForecast.trends.back().forecast.windSpeed = Speed{8, Speed::Unit::KT};
    refForecast.trends.back().forecast.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.trends.back().forecast.skyCondition =
        Essentials::SkyCondition::CLEAR_SKC;
    refForecast.trends.back().windShearConditions = true;
    refForecast.trends.back().turbulence.push_back(
        TurbulenceForecast{
            TurbulenceForecast::Severity::MODERATE,
            TurbulenceForecast::Location::IN_CLEAR_AIR,
            TurbulenceForecast::Frequency::FREQUENT,
            Height{0, Height::Unit::FEET},
            Height{9000, Height::Unit::FEET},
        });
    refForecast.trends.back().forecast.seaLevelPressure = 
        Pressure{2970, Pressure::Unit::HUNDREDTHS_IN_HG};

    // T40/0622Z T25/0713Z
    refForecast.maxTemperature.push_back(TemperatureForecast{
        Temperature{40, Temperature::Unit::C},
        Time{6, 22, 0}});
    refForecast.minTemperature.push_back(TemperatureForecast{
        Temperature{25, Temperature::Unit::C},
        Time{7, 13, 0}});
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}

TEST(IntegrationTafs, wscondsInPrevailing) {
    static const auto rawReport =
        "TAF ZZZZ 1823/1923 25020KT 9999 SKC WSCONDS=";
        // Fake report created for this test
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time();
    refReport.applicableFrom = Time{18, 23, 0};
    refReport.applicableUntil = Time{19, 23, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    // 1823/1923 25020KT 9999 SKC WSCONDS
    refForecast.prevailing.windDirectionDegrees = 250;
    refForecast.prevailing.windSpeed = Speed{20, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{
            Distance::Details::MORE_THAN,
            10000,
            Distance::Unit::METERS};
    refForecast.prevailing.skyCondition = Essentials::SkyCondition::CLEAR_SKC;
    refForecast.prevailingWsConds = true;
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}