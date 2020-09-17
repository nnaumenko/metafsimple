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
// The following tests confirm that comparison operators declared in
// test/comparisons.hpp return false if compared variables differ.
// NOTE: comparison operators are only used for unit/integration tests and are
// not part of MetafSimple library.
////////////////////////////////////////////////////////////////////////////////

TEST(ValidateComparisons, runway) {
    const auto ref = Runway();
    Runway test;

    test = Runway();
    test.number = 24;
    EXPECT_FALSE(ref == test);

    test = Runway();
    test.designator = Runway::Designator::RIGHT;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, time) {
    const auto ref = Time();
    Time test;

    test = Time();
    test.day = 1;
    EXPECT_FALSE(ref == test);

    test = Time();
    test.hour = 1;
    EXPECT_FALSE(ref == test);

    test = Time();
    test.minute = 1;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, temperature) {
    const auto ref = Temperature();
    Temperature test;

    test = Temperature();
    test.temperature = 1;
    EXPECT_FALSE(ref == test);

    test = Temperature();
    test.unit = Temperature::Unit::TENTH_C;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, speed) {
    const auto ref = Speed();
    Speed test;

    test = Speed();
    test.speed = 1;
    EXPECT_FALSE(ref == test);

    test = Speed();
    test.unit = Speed::Unit::MPH;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, distance) {
    const auto ref = Distance();
    Distance test;

    test = Distance();
    test.distance = 1;
    EXPECT_FALSE(ref == test);

    test = Distance();
    test.unit = Distance::Unit::FEET;
    EXPECT_FALSE(ref == test);

    test = Distance();
    test.details = Distance::Details::MORE_THAN;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, distanceRange) {
    const auto ref = DistanceRange();
    DistanceRange test;

    test = DistanceRange();
    test.prevailing =
        Distance{Distance::Details::EXACTLY, 1200, Distance::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = DistanceRange();
    test.minimum =
        Distance{Distance::Details::EXACTLY, 1200, Distance::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = DistanceRange();
    test.maximum =
        Distance{Distance::Details::EXACTLY, 1200, Distance::Unit::FEET};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, height) {
    const auto ref = Height();
    Height test;

    test = Height();
    test.height = 100;
    EXPECT_FALSE(ref == test);

    test = Height();
    test.unit = Height::Unit::METERS;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, ceiling) {
    const auto ref = Ceiling();
    Ceiling test;

    test = Ceiling();
    test.exact = Height{100, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = Ceiling();
    test.minimum = Height{100, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = Ceiling();
    test.maximum = Height{100, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, pressure) {
    const auto ref = Pressure();
    Pressure test;

    test = Pressure();
    test.pressure = 1;
    EXPECT_FALSE(ref == test);

    test = Pressure();
    test.unit = Pressure::Unit::IN_HG;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, precipitation) {
    const auto ref = Precipitation();
    Precipitation test;

    test = Precipitation();
    test.amount = 1;
    EXPECT_FALSE(ref == test);

    test = Precipitation();
    test.unit = Precipitation::Unit::IN;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, waveHeight) {
    const auto ref = WaveHeight();
    WaveHeight test;

    test = WaveHeight();
    test.waveHeight = 1;
    EXPECT_FALSE(ref == test);

    test = WaveHeight();
    test.unit = WaveHeight::Unit::YARDS;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, weather) {
    const auto ref = Weather();
    Weather test;

    test = Weather();
    test.phenomena = Weather::Phenomena::NO_SIGNIFICANT_WEATHER;
    EXPECT_FALSE(ref == test);

    test = Weather();
    test.phenomena = Weather::Phenomena::PRECIPITATION_LIGHT;
    test.precipitation = {Weather::Precipitation::RAIN};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, cloudLayer) {
    const auto ref = CloudLayer();
    CloudLayer test;

    test = CloudLayer();
    test.amount = CloudLayer::Amount::OVERCAST;
    EXPECT_FALSE(ref == test);

    test = CloudLayer();
    test.height = Height{100, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = CloudLayer();
    test.details = CloudLayer::Details::CUMULONIMBUS;
    EXPECT_FALSE(ref == test);

    test = CloudLayer();
    test.okta = 1;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, vicinity) {
    const auto ref = Vicinity();
    Vicinity test;

    test = Vicinity();
    test.phenomena = ObservedPhenomena::CUMULONIMBUS;
    EXPECT_FALSE(ref == test);

    test = Vicinity();
    test.distance.prevailing =
        Distance{Distance::Details::EXACTLY, 20000, Distance::Unit::METERS};
    EXPECT_FALSE(ref == test);

    test = Vicinity();
    test.moving = CardinalDirection::W;
    EXPECT_FALSE(ref == test);

    test = Vicinity();
    test.directions.insert(CardinalDirection::NW);
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, lightningStrikes) {
    const auto ref = LightningStrikes();
    LightningStrikes test;

    test = LightningStrikes();
    test.frequency = LightningStrikes::Frequency::CONSTANT;
    EXPECT_FALSE(ref == test);

    test = LightningStrikes();
    test.type.insert(LightningStrikes::Type::IN_CLOUD);
    EXPECT_FALSE(ref == test);

    test.distance.prevailing =
        Distance{Distance::Details::EXACTLY, 20000, Distance::Unit::METERS};
    EXPECT_FALSE(ref == test);

    test = LightningStrikes();
    test.directions.insert(CardinalDirection::NW);
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, icingForecast) {
    const auto ref = IcingForecast();
    IcingForecast test;

    test = IcingForecast();
    test.severity = IcingForecast::Severity::LIGHT;
    EXPECT_FALSE(ref == test);

    test = IcingForecast();
    test.type = IcingForecast::Type::MIXED;
    EXPECT_FALSE(ref == test);

    test = IcingForecast();
    test.minHeight = Height{1200, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = IcingForecast();
    test.maxHeight = Height{1200, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, turbulenceForecast) {
    const auto ref = TurbulenceForecast();
    TurbulenceForecast test;

    test = TurbulenceForecast();
    test.severity = TurbulenceForecast::Severity::LIGHT;
    EXPECT_FALSE(ref == test);

    test = TurbulenceForecast();
    test.location = TurbulenceForecast::Location::IN_CLOUD;
    EXPECT_FALSE(ref == test);

    test = TurbulenceForecast();
    test.location = TurbulenceForecast::Location::IN_CLOUD;
    EXPECT_FALSE(ref == test);

    test = TurbulenceForecast();
    test.frequency = TurbulenceForecast::Frequency::FREQUENT;
    EXPECT_FALSE(ref == test);

    test = TurbulenceForecast();
    test.minHeight = Height{1200, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = TurbulenceForecast();
    test.maxHeight = Height{1200, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, essentials) {
    const auto ref = Essentials();
    Essentials test;

    test = Essentials();
    test.windDirectionDegrees = 270;
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.windDirectionVariable = true;
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.windDirectionVarFromDegrees = 270;
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.windDirectionVarToDegrees = 270;
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.windSpeed = Speed{1, Speed::Unit::KT};
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.gustSpeed = Speed{1, Speed::Unit::KT};
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.windCalm = true;
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.visibility =
        Distance{Distance::Details::EXACTLY, 3, Distance::Unit::STATUTE_MILES};
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.cavok = true;
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.skyCondition = Essentials::SkyCondition::OBSCURED;
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.cloudLayers.push_back(CloudLayer());
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.verticalVisibility = Height{100, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.weather.push_back(
        Weather{Weather::Phenomena::NO_SIGNIFICANT_WEATHER, {}});
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.seaLevelPressure = Pressure{3001, Pressure::Unit::IN_HG};
    EXPECT_FALSE(ref == test);

    test = Essentials();
    test.windShear.push_back(WindShear());
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, trend) {
    const auto ref = Trend();
    Trend test;

    test = Trend();
    test.type = Trend::Type::BECMG;
    EXPECT_FALSE(ref == test);

    test = Trend();
    test.probability = 30;
    EXPECT_FALSE(ref == test);

    test = Trend();
    test.timeFrom = Time{17, 20, 51};
    EXPECT_FALSE(ref == test);

    test = Trend();
    test.timeUntil = Time{17, 20, 51};
    EXPECT_FALSE(ref == test);

    test = Trend();
    test.timeAt = Time{17, 20, 51};
    EXPECT_FALSE(ref == test);

    test = Trend();
    test.forecast.windDirectionVariable = true;
    EXPECT_FALSE(ref == test);

    test = Trend();
    test.icing.push_back(IcingForecast());
    EXPECT_FALSE(ref == test);

    test = Trend();
    test.turbulence.push_back(TurbulenceForecast());
    EXPECT_FALSE(ref == test);

    test = Trend();
    test.vicinity.insert(ObservedPhenomena::CUMULONIMBUS);
    EXPECT_FALSE(ref == test);

    test = Trend();
    test.windShearConditions = true;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, temperatureForecast) {
    const auto ref = TemperatureForecast();
    TemperatureForecast test;

    test = TemperatureForecast();
    test.temperature = Temperature{10, Temperature::Unit::C};
    EXPECT_FALSE(ref == test);

    test = TemperatureForecast();
    test.time = Time{17, 20, 59};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, reportWarning) {
    const auto ref = Report::Warning();
    Report::Warning test;

    test = Report::Warning();
    test.message = Report::Warning::Message::DUPLICATED_DATA;
    EXPECT_FALSE(ref == test);

    test = Report::Warning();
    test.id = "id";
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, report) {
    const auto ref = Report();
    Report test;

    test = Report();
    test.type = Report::Type::TAF;
    EXPECT_FALSE(ref == test);

    test = Report();
    test.missing = true;
    EXPECT_FALSE(ref == test);

    test = Report();
    test.cancelled = true;
    EXPECT_FALSE(ref == test);

    test = Report();
    test.correctional = true;
    EXPECT_FALSE(ref == test);

    test = Report();
    test.amended = true;
    EXPECT_FALSE(ref == test);

    test = Report();
    test.automated = true;
    EXPECT_FALSE(ref == test);

    test = Report();
    test.correctionNumber = 1;
    EXPECT_FALSE(ref == test);

    test = Report();
    test.reportTime = Time{17, 21, 07};
    EXPECT_FALSE(ref == test);

    test = Report();
    test.applicableFrom = Time{17, 21, 07};
    EXPECT_FALSE(ref == test);

    test = Report();
    test.applicableUntil = Time{17, 21, 07};
    EXPECT_FALSE(ref == test);

    test = Report();
    test.error = Report::Error::EMPTY_REPORT;
    EXPECT_FALSE(ref == test);

    test = Report();
    test.warnings.push_back(Report::Warning());
    EXPECT_FALSE(ref == test);

    test = Report();
    test.plainText.push_back("test");
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, station) {
    const auto ref = Station();
    Station test;

    test = Station();
    test.icaoCode = "UKLL";
    EXPECT_FALSE(ref == test);

    test = Station();
    test.autoType = Station::AutoType::AO2A;
    EXPECT_FALSE(ref == test);

    test = Station();
    test.requiresMaintenance = true;
    EXPECT_FALSE(ref == test);

    test = Station();
    test.noSpeciReports = true;
    EXPECT_FALSE(ref == test);

    test = Station();
    test.noVisDirectionalVariation = true;
    EXPECT_FALSE(ref == test);

    test = Station();
    test.missingData.insert(Station::MissingData::SLPNO);
    EXPECT_FALSE(ref == test);

    test = Station();
    test.runwaysNoCeilingData.insert(Runway());
    EXPECT_FALSE(ref == test);

    test = Station();
    test.runwaysNoVisData.insert(Runway());
    EXPECT_FALSE(ref == test);

    test = Station();
    test.directionsNoCeilingData.insert(CardinalDirection::W);
    EXPECT_FALSE(ref == test);

    test = Station();
    test.directionsNoVisData.insert(CardinalDirection::W);
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, aerodromeRunwayData) {
    const auto ref = Aerodrome::RunwayData();
    Aerodrome::RunwayData test;

    test = Aerodrome::RunwayData();
    test.runway = Runway{31, Runway::Designator::NONE};
    EXPECT_FALSE(ref == test);

    test = Aerodrome::RunwayData();
    test.notOperational = true;
    EXPECT_FALSE(ref == test);

    test = Aerodrome::RunwayData();
    test.snoclo = true;
    EXPECT_FALSE(ref == test);

    test = Aerodrome::RunwayData();
    test.clrd = true;
    EXPECT_FALSE(ref == test);

    test = Aerodrome::RunwayData();
    test.windShearLowerLayers = true;
    EXPECT_FALSE(ref == test);

    test = Aerodrome::RunwayData();
    test.deposits = Aerodrome::RunwayDeposits::DAMP;
    EXPECT_FALSE(ref == test);

    test = Aerodrome::RunwayData();
    test.contaminationExtent =
        Aerodrome::RunwayContamExtent::LESS_THAN_11_PERCENT;
    EXPECT_FALSE(ref == test);

    test = Aerodrome::RunwayData();
    test.depositDepth = Precipitation{1, Precipitation::Unit::MM};
    EXPECT_FALSE(ref == test);

    test = Aerodrome::RunwayData();
    test.coefficient = 78;
    EXPECT_FALSE(ref == test);

    test = Aerodrome::RunwayData();
    test.surfaceFrictionUnreliable = true;
    EXPECT_FALSE(ref == test);

    test = Aerodrome::RunwayData();
    test.visualRange = DistanceRange{
        Distance{Distance::Details::EXACTLY, 1200, Distance::Unit::FEET},
        Distance(),
        Distance()};
    EXPECT_FALSE(ref == test);

    test = Aerodrome::RunwayData();
    test.visualRangeTrend = Aerodrome::RvrTrend::DOWNWARD;
    EXPECT_FALSE(ref == test);

    test = Aerodrome::RunwayData();
    test.ceiling = Ceiling{Height{100, Height::Unit::FEET}, Height(), Height()};
    EXPECT_FALSE(ref == test);

    test = Aerodrome::RunwayData();
    test.visibility = DistanceRange{
        Distance{Distance::Details::EXACTLY, 4500, Distance::Unit::METERS},
        Distance(),
        Distance()};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, aerodromeDirectionData) {
    const auto ref = Aerodrome::DirectionData();
    Aerodrome::DirectionData test;

    test = Aerodrome::DirectionData();
    test.cardinalDirection = CardinalDirection::W;
    EXPECT_FALSE(ref == test);

    test = Aerodrome::DirectionData();
    test.ceiling = Ceiling{Height{100, Height::Unit::FEET}, Height(), Height()};
    EXPECT_FALSE(ref == test);

    test = Aerodrome::DirectionData();
    test.visibility = DistanceRange{
        Distance{Distance::Details::EXACTLY, 4500, Distance::Unit::METERS},
        Distance(),
        Distance()};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, aerodrome) {
    const auto ref = Aerodrome();
    Aerodrome test;

    test = Aerodrome();
    test.snoclo = true;
    EXPECT_FALSE(ref == test);

    test = Aerodrome();
    test.colourCode = Aerodrome::ColourCode::BLUE;
    EXPECT_FALSE(ref == test);

    test = Aerodrome();
    test.colourCodeBlack = true;
    EXPECT_FALSE(ref == test);

    test = Aerodrome();
    test.runways.push_back(Aerodrome::RunwayData());
    EXPECT_FALSE(ref == test);

    test = Aerodrome();
    test.directions.push_back(Aerodrome::DirectionData());
    EXPECT_FALSE(ref == test);

    test = Aerodrome();
    test.ceiling = Ceiling{Height{100, Height::Unit::FEET}, Height(), Height()};
    EXPECT_FALSE(ref == test);

    test = Aerodrome();
    test.surfaceVisibility = 
        Distance{Distance::Details::EXACTLY, 4500, Distance::Unit::METERS};
    EXPECT_FALSE(ref == test);

    test = Aerodrome();
    test.towerVisibility = 
        Distance{Distance::Details::EXACTLY, 4500, Distance::Unit::METERS};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, windShear) {
    const auto ref = WindShear();
    WindShear test;

    test = WindShear();
    test.height = Height{3000, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = WindShear();
    test.directionDegrees = 160;
    EXPECT_FALSE(ref == test);

    test = WindShear();
    test.windSpeed = Speed {40, Speed::Unit::KT};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, historicalWeatherEvent) {
    const auto ref = Historical::WeatherEvent();
    Historical::WeatherEvent test;

    test = Historical::WeatherEvent();
    test.event = Historical::Event::ENDED;
    EXPECT_FALSE(ref == test);

    test = Historical::WeatherEvent();
    test.time = Time{17, 21, 40};
    EXPECT_FALSE(ref == test);

    test = Historical::WeatherEvent();
    test.weather.phenomena = Weather::Phenomena::NO_SIGNIFICANT_WEATHER;
    EXPECT_FALSE(ref == test);
}

// TODO: Current
// TODO: Historical
// TODO: Forecast
// TODO: Simple