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
// TAF reports with multiple trends: FMxxxxxx, TEMPO, BECMG, INTER, PROB, etc;
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationTafTrends, trendBecmgFmTempoInterProbInter) {
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::BECMG,
            std::optional<int>(),
            Time{9, 0, 0},
            Time{9, 1, 0},
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TIMED,
            std::optional<int>(),
            Time{9, 4, 0},
            Time(),
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TIMED,
            std::optional<int>(),
            Time{9, 10, 0},
            Time(),
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TEMPO,
            std::optional<int>(),
            Time{8, 22, 0},
            Time{9, 4, 0},
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::INTER,
            std::optional<int>(),
            Time{9, 6, 0},
            Time{9, 12, 0},
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::INTER,
            30,
            Time{9, 3, 0},
            Time{9, 6, 0},
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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

TEST(IntegrationTafTrends, trendProbTempo) {
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TEMPO,
            30,
            Time{5, 12, 0},
            Time{5, 20, 0},
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TEMPO,
            40,
            Time{6, 3, 0},
            Time{6, 12, 0},
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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

TEST(IntegrationTafTrends, trendProbTimedAndRemark) {
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TEMPO,
            std::optional<int>(),
            Time{8, 20, 0},
            Time{8, 24, 0},
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TIMED,
            30,
            Time{8, 20, 0},
            Time{8, 24, 0},
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TIMED,
            std::optional<int>(),
            Time{9, 0, 0},
            Time(),
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TEMPO,
            std::optional<int>(),
            Time{9, 0, 0},
            Time{9, 3, 0},
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TIMED,
            std::optional<int>(),
            Time{9, 3, 0},
            Time(),
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TIMED,
            30,
            Time{9, 3, 0},
            Time{9, 9, 0},
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TIMED,
            std::optional<int>(),
            Time{9, 9, 0},
            Time(),
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TIMED,
            40,
            Time{9, 9, 0},
            Time{9, 12, 0},
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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
    refForecast.trends.push_back(
        Trend{
            Trend::Type::TIMED,
            std::optional<int>(),
            Time{9, 15, 0},
            Time(),
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
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

TEST(IntegrationTafTrends, probOnly) {
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
    refForecast.prevailing.windDirectionDegrees = 240;
    refForecast.prevailing.windSpeed = Speed{14, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{Distance::Details::MORE_THAN,
                 10000,
                 Distance::Unit::METERS};
    refForecast.prevailing.skyCondition =
        Essentials::SkyCondition::CAVOK;

    // PROB30 VRB05KT
    refForecast.trends.push_back(
        Trend{
            Trend::Type::PROB,
            30,
            Time(),
            Time(),
            Time(),
            Essentials(),
            {},
            {},
            {},
        });
    refForecast.trends.back().forecast.windDirectionVariable = true;
    refForecast.trends.back().forecast.windSpeed = Speed{5, Speed::Unit::KT};
}
