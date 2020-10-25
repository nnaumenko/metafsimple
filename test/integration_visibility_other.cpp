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
// The tests in this file cover visibility groups other than the main visibility
// group specified in the METAR report body or in METAR and TAF trends.
// Directional visibility group may be specified in METAR body (xxxxD or 
// xxxxDD).
// In remark section, directional/runway/sector visibility may be specified, 
// optionally its value may be variable.
// Surface or tower visibility may be specified in remarks.
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationVisibilityOther, directionalMetarBody) {
    static const auto rawReport =
        "METAR ESPA 031820Z 35004KT 9999 3000NW BCFG NSC 08/08 Q1027=";
        // 03 OCT 2020
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{3, 18, 20};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ESPA";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 350;
    refCurrent.weatherData.windSpeed = Speed{4, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::PATCHES_FOG, {}});
    refCurrent.weatherData.skyCondition = 
        Essentials::SkyCondition::NO_SIGNIFICANT_CLOUD;
    refCurrent.airTemperature = Temperature{8, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{8, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1027, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    Aerodrome refAerodrome;
    refAerodrome.directions.push_back(Aerodrome::DirectionData());
    refAerodrome.directions.back().cardinalDirection = CardinalDirection::NW;
    refAerodrome.directions.back().visibility = DistanceRange{
        Distance{Distance::Details::EXACTLY, 3000, Distance::Unit::METERS},
        Distance(),
        Distance()
    };
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibilityOther, directionalRmk) {
    static const auto rawReport =
        "SPECI PADG 291956Z 10006KT 7SM FEW008 BKN020 01/M01 A3001"
        " RMK VIS S 10="; // 29 SEP 2020
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::SPECI;
    refReport.reportTime = Time{29, 19, 56};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "PADG";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 100;
    refCurrent.weatherData.windSpeed = Speed{6, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 7, Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition = 
        Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{800, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{2000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{1, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{-1, Temperature::Unit::C};
    refCurrent.relativeHumidity = 86;
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{3001, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    Aerodrome refAerodrome;
    refAerodrome.directions.push_back(Aerodrome::DirectionData());
    refAerodrome.directions.back().cardinalDirection = CardinalDirection::S;
    refAerodrome.directions.back().visibility = DistanceRange{
        Distance{Distance::Details::EXACTLY, 10, Distance::Unit::STATUTE_MILES},
        Distance(),
        Distance()
    };
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
    
}
