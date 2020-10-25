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
        Distance()};
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibilityOther, directionalRmk) {
    static const auto rawReport =
        "SPECI PADG 291956Z 10006KT 7SM FEW008 BKN020 01/M01 A3001"
        " RMK VIS S 10=";  // 29 SEP 2020
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
        Distance()};
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibilityOther, directionalSector) {
    static const auto rawReport =
        "SPECI PAJN 031616Z 00000KT 2SM BR FEW001 BKN005 BKN030 10/09 A3001"
        " RMK AO2 VIS SW-N 7 T01000089=";  // 03 OCT 2020
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::SPECI;
    refReport.reportTime = Time{3, 16, 16};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "PAJN";
    refStation.autoType = Station::AutoType::AO2;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windCalm = true;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 2, Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::MIST, {}});
    refCurrent.weatherData.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::FEW,
                   Height{100, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{3000, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{100, Temperature::Unit::TENTH_C};
    refCurrent.dewPoint = Temperature{89, Temperature::Unit::TENTH_C};
    refCurrent.relativeHumidity = 92;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{3001, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    Aerodrome refAerodrome;

    const DistanceRange sectorVisibility = {
        Distance{Distance::Details::EXACTLY, 7, Distance::Unit::STATUTE_MILES},
        Distance(),
        Distance()};

    refAerodrome.directions.push_back(Aerodrome::DirectionData());
    refAerodrome.directions.back().cardinalDirection = CardinalDirection::SW;
    refAerodrome.directions.back().visibility = sectorVisibility;

    refAerodrome.directions.push_back(Aerodrome::DirectionData());
    refAerodrome.directions.back().cardinalDirection = CardinalDirection::W;
    refAerodrome.directions.back().visibility = sectorVisibility;

    refAerodrome.directions.push_back(Aerodrome::DirectionData());
    refAerodrome.directions.back().cardinalDirection = CardinalDirection::NW;
    refAerodrome.directions.back().visibility = sectorVisibility;

    refAerodrome.directions.push_back(Aerodrome::DirectionData());
    refAerodrome.directions.back().cardinalDirection = CardinalDirection::N;
    refAerodrome.directions.back().visibility = sectorVisibility;

    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibilityOther, runway) {
    static const auto rawReport =
        "SPECI KCEF 030826Z AUTO 00000KT 10SM OVC002 04/04 A3010"
        " RMK AO2 VIS 1 1/2 RWY23 SLP199=";  // 03 OCT 2020
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::SPECI;
    refReport.reportTime = Time{3, 8, 26};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KCEF";
    refStation.autoType = Station::AutoType::AO2;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windCalm = true;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 10, Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{200, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{4, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{4, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{3010, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    Aerodrome refAerodrome;
    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways.back().runway = Runway{23, Runway::Designator::NONE};
    refAerodrome.runways.back().visibility = DistanceRange{
        Distance{
            Distance::Details::EXACTLY,
            24,
            Distance::Unit::STATUTE_MILE_1_16S},
        Distance(),
        Distance()};
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibilityOther, surface) {
    static const auto rawReport =
        "METAR KROA 252154Z 16005KT 1SM BR OVC003 11/10 A3013"
        " RMK AO2 SFC VIS 2 SLP203 T01060100";  // 25 OCT 2020
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{25, 21, 54};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KROA";
    refStation.autoType = Station::AutoType::AO2;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 160;
    refCurrent.weatherData.windSpeed = Speed{5, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 1, Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::MIST, {}});
    refCurrent.weatherData.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{300, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{106, Temperature::Unit::TENTH_C};
    refCurrent.dewPoint = Temperature{100, Temperature::Unit::TENTH_C};
    refCurrent.relativeHumidity = 96;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{3013, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    Aerodrome refAerodrome;
    refAerodrome.surfaceVisibility =
        Distance{Distance::Details::EXACTLY, 2, Distance::Unit::STATUTE_MILES};
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisibilityOther, tower) {
    static const auto rawReport =
        "METAR PAED 302003Z 00000KT 10SM -RA BKN005 OVC055 10/09 A2940"
        " RMK AO2A TWR VIS 3 SLP952=";  // 30 SEP 2020
    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 3};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "PAED";
    refStation.autoType = Station::AutoType::AO2A;
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windCalm = true;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::EXACTLY, 10, Distance::Unit::STATUTE_MILES};
    refCurrent.weatherData.weather.push_back(
        Weather{Weather::Phenomena::PRECIPITATION_LIGHT,
                {Weather::Precipitation::RAIN}});
    refCurrent.weatherData.skyCondition =
        Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::BROKEN,
                   Height{500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::OVERCAST,
                   Height{5500, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{10, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{9, Temperature::Unit::C};
    refCurrent.relativeHumidity = 93;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{2940, Pressure::Unit::HUNDREDTHS_IN_HG};
    EXPECT_EQ(result.current, refCurrent);

    Aerodrome refAerodrome;
    refAerodrome.towerVisibility =
        Distance{Distance::Details::EXACTLY, 3, Distance::Unit::STATUTE_MILES};
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}
