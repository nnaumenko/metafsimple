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

TEST(IntegrationBasicReports, tafBecmgInter) {
    static const auto rawReport =
        "TAF YSNF 051126Z 0512/0612 04010KT 9999 -SHRA BKN012"
        " BECMG 0515/0517 34010KT 9999 -SHRA SCT015"
        " BECMG 0600/0602 25014KT 9999 -SHRA SCT015 SCT025"
        " INTER 0512/0603 5000 SHRA BKN007="; // 5 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time {5, 11, 26};
    refReport.applicableFrom = Time {5, 12, 0};
    refReport.applicableUntil = Time {6, 12, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "YSNF";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    refForecast.prevailing.windDirectionDegrees = 40;
    refForecast.prevailing.windSpeed = Speed {10, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.prevailing.skyCondition = Essentials::SkyCondition::CLOUDS;
    refForecast.prevailing.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{1200, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refForecast.prevailing.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});

    Essentials essentialsBecmg_0515_0517;
    essentialsBecmg_0515_0517.windDirectionDegrees = 340;
    essentialsBecmg_0515_0517.windSpeed = Speed {10, Speed::Unit::KT};
    essentialsBecmg_0515_0517.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    essentialsBecmg_0515_0517.skyCondition = Essentials::SkyCondition::CLOUDS;
    essentialsBecmg_0515_0517.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{1500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    essentialsBecmg_0515_0517.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});
    refForecast.trends.push_back(
        Trend {
            Trend::Type::BECMG,
            std::optional<int>(),
            Time{5, 15, 0},
            Time{5, 17, 0},
            Time(),
            essentialsBecmg_0515_0517,
            {},
            {},
            Pressure()
        }
    );

    Essentials essentialsBecmg_0600_0602;
    essentialsBecmg_0600_0602.windDirectionDegrees = 250;
    essentialsBecmg_0600_0602.windSpeed = Speed {14, Speed::Unit::KT};
    essentialsBecmg_0600_0602.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    essentialsBecmg_0600_0602.skyCondition = Essentials::SkyCondition::CLOUDS;
    essentialsBecmg_0600_0602.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{1500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    essentialsBecmg_0600_0602.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{2500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    essentialsBecmg_0600_0602.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});
    refForecast.trends.push_back(
        Trend {
            Trend::Type::BECMG,
            std::optional<int>(),
            Time{6, 0, 0},
            Time{6, 2, 0},
            Time(),
            essentialsBecmg_0600_0602,
            {},
            {},
            Pressure()
        }
    );

    Essentials essentialsInter_0512_0603;
    essentialsInter_0512_0603.visibility =
        Distance{ Distance::Details::EXACTLY, 5000, Distance::Unit::METERS};
    essentialsInter_0512_0603.skyCondition = Essentials::SkyCondition::CLOUDS;
    essentialsInter_0512_0603.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{700, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    essentialsInter_0512_0603.weather.push_back(
        Weather{Weather::Phenomena::SHOWERY_PRECIPITATION_MODERATE,
                {Weather::Precipitation::RAIN}});
    refForecast.trends.push_back(
        Trend {
            Trend::Type::INTER,
            std::optional<int>(),
            Time{5, 12, 0},
            Time{6, 3, 0},
            Time(),
            essentialsInter_0512_0603,
            {},
            {},
            Pressure()
        }
    );

    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}
