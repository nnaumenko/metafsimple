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
// Tests for runway state groups Rxx/xxxxxx, Rxx/CLRDxx, Rxx/SNOCLO
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationRunwayState, runwayState) {
    static const auto rawReport =
        "METAR UWGG 052200Z 19002MPS 9999 SCT033 13/08 Q1022 R18L/090070 NOSIG";
        // 5 SEP 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{5, 22, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "UWGG";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 190;
    refCurrent.weatherData.windSpeed = Speed{2, Speed::Unit::MPS};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLOUDS;
    refCurrent.weatherData.cloudLayers.push_back(
        CloudLayer{CloudLayer::Amount::SCATTERED,
                   Height{3300, Height::Unit::FEET},
                   CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
                   std::optional<int>()});
    refCurrent.airTemperature = Temperature{13, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{8, Temperature::Unit::C};
    refCurrent.relativeHumidity = 71;
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1022, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    Aerodrome refAerodrome;
    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways[0].runway = Runway {18, Runway::Designator::LEFT};
    refAerodrome.runways[0].deposits = Aerodrome::RunwayDeposits::CLEAR_AND_DRY;
    refAerodrome.runways[0].depositDepth = 
        Precipitation {0, Precipitation::Unit::MM};
    refAerodrome.runways[0].contaminationExtent = 
        Aerodrome::RunwayContamExtent::MORE_THAN_50_PERCENT;
    refAerodrome.runways[0].coefficient = 70;
    EXPECT_EQ(result.aerodrome, refAerodrome);
    
    EXPECT_EQ(result.historical, Historical());

    Forecast refForecast;
    refForecast.noSignificantChanges = true;
    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationRunwayState, runwayStateMultipleRunways) {
    static const auto rawReport =
        "METAR ZZZZ 062237Z R25/250157 R34/19//61=";
        // Fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{6, 22, 37};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Aerodrome refAerodrome;
    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways[0].runway = Runway {25, Runway::Designator::NONE};
    refAerodrome.runways[0].deposits = 
        Aerodrome::RunwayDeposits::WET_AND_WATER_PATCHES;
    refAerodrome.runways[0].contaminationExtent = 
        Aerodrome::RunwayContamExtent::FROM_26_TO_50_PERCENT;
    refAerodrome.runways[0].depositDepth = 
        Precipitation {1, Precipitation::Unit::MM};
    refAerodrome.runways[0].coefficient = 57;

    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways[1].runway = Runway {34, Runway::Designator::NONE};
    refAerodrome.runways[1].deposits = Aerodrome::RunwayDeposits::DAMP;
    refAerodrome.runways[1].contaminationExtent = 
        Aerodrome::RunwayContamExtent::MORE_THAN_50_PERCENT;
    refAerodrome.runways[1].coefficient = 61;
    EXPECT_EQ(result.aerodrome, refAerodrome);
    
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationRunwayState, runwayStateClrd) {
    static const auto rawReport =
        "METAR UUDD 052200Z 17003MPS CAVOK 14/08 Q1019 R14R/CLRD60 NOSIG=";
        // 5 SEP 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{5, 22, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "UUDD";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 170;
    refCurrent.weatherData.windSpeed = Speed{3, Speed::Unit::MPS};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.weatherData.cavok = true;
    refCurrent.airTemperature = Temperature{14, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{8, Temperature::Unit::C};
    refCurrent.relativeHumidity = 67;
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1019, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    Aerodrome refAerodrome;
    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways[0].runway = Runway {14, Runway::Designator::RIGHT};
    refAerodrome.runways[0].clrd = true;
    refAerodrome.runways[0].coefficient = 60;
    EXPECT_EQ(result.aerodrome, refAerodrome);
    
    EXPECT_EQ(result.historical, Historical());

    Forecast refForecast;
    refForecast.noSignificantChanges = true;
    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationRunwayState, aerodromeSnoclo) {
    static const auto rawReport =
        "METAR EGLC 280750Z AUTO 07008KT 9999 NCD M04/M07 Q1018 R/SNOCLO=";
        // 28 FEB 2018

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{28, 7, 50};
    refReport.error = Report::Error::NO_ERROR;
    refReport.automated = true;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EGLC";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 70;
    refCurrent.weatherData.windSpeed = Speed{8, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CLEAR_NCD;
    refCurrent.airTemperature = Temperature{-4, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{-7, Temperature::Unit::C};
    refCurrent.relativeHumidity = 79;
    refCurrent.weatherData.seaLevelPressure = 
        Pressure{1018, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    Aerodrome refAerodrome;
    refAerodrome.snoclo = true;
    EXPECT_EQ(result.aerodrome, refAerodrome);
    
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationRunwayState, runwaySnoclo) {
    static const auto rawReport =
        "METAR ZZZZ 061909Z R21/SNOCLO=";
        // Fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{6, 19, 9};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Aerodrome refAerodrome;
    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways[0].runway = Runway {21, Runway::Designator::NONE};
    refAerodrome.runways[0].snoclo = true;
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationRunwayState, runwayNotOperational) {
    static const auto rawReport =
        "METAR ZZZZ 061909Z R13/7999//=";
        // Fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{6, 19, 9};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Aerodrome refAerodrome;
    refAerodrome.runways.push_back(Aerodrome::RunwayData());
    refAerodrome.runways[0].runway = Runway {13, Runway::Designator::NONE};
    refAerodrome.runways[0].deposits = Aerodrome::RunwayDeposits::ICE;
    refAerodrome.runways[0].contaminationExtent = 
        Aerodrome::RunwayContamExtent::MORE_THAN_50_PERCENT;
    refAerodrome.runways[0].notOperational = true;
    EXPECT_EQ(result.aerodrome, refAerodrome);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}
