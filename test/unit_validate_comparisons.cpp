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
    auto test = ref;

    test = ref;
    test.number = 24;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.designator = Runway::Designator::RIGHT;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, time) {
    const auto ref = Time();
    auto test = ref;

    test = ref;
    test.day = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.hour = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.minute = 1;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, temperature) {
    const auto ref = Temperature();
    auto test = ref;

    test = ref;
    test.temperature = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.unit = Temperature::Unit::TENTH_C;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, speed) {
    const auto ref = Speed();
    auto test = ref;

    test = ref;
    test.speed = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.unit = Speed::Unit::MPH;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, distance) {
    const auto ref = Distance();
    auto test = ref;

    test = ref;
    test.distance = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.unit = Distance::Unit::FEET;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.details = Distance::Details::MORE_THAN;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, distanceRange) {
    const auto ref = DistanceRange();
    auto test = ref;

    test = ref;
    test.prevailing =
        Distance{Distance::Details::EXACTLY, 1200, Distance::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.minimum =
        Distance{Distance::Details::EXACTLY, 1200, Distance::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.maximum =
        Distance{Distance::Details::EXACTLY, 1200, Distance::Unit::FEET};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, height) {
    const auto ref = Height();
    auto test = ref;

    test = ref;
    test.height = 100;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.unit = Height::Unit::METERS;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, ceiling) {
    const auto ref = Ceiling();
    auto test = ref;

    test = ref;
    test.exact = Height{100, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.minimum = Height{100, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.maximum = Height{100, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, pressure) {
    const auto ref = Pressure();
    auto test = ref;

    test = ref;
    test.pressure = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.unit = Pressure::Unit::IN_HG;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, precipitation) {
    const auto ref = Precipitation();
    auto test = ref;

    test = ref;
    test.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.unit = Precipitation::Unit::IN;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, waveHeight) {
    const auto ref = WaveHeight();
    auto test = ref;

    test = ref;
    test.waveHeight = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.unit = WaveHeight::Unit::YARDS;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, weather) {
    const auto ref = Weather();
    auto test = ref;

    test = ref;
    test.phenomena = Weather::Phenomena::NO_SIGNIFICANT_WEATHER;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.phenomena = Weather::Phenomena::PRECIPITATION_LIGHT;
    test.precipitation = {Weather::Precipitation::RAIN};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, cloudLayer) {
    const auto ref = CloudLayer();
    auto test = ref;

    test = ref;
    test.amount = CloudLayer::Amount::OVERCAST;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.height = Height{100, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.details = CloudLayer::Details::CUMULONIMBUS;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.okta = 1;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, vicinity) {
    const auto ref = Vicinity();
    auto test = ref;

    test = ref;
    test.phenomena = ObservedPhenomena::CUMULONIMBUS;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.distance.prevailing =
        Distance{Distance::Details::EXACTLY, 20000, Distance::Unit::METERS};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.moving = CardinalDirection::W;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.directions.insert(CardinalDirection::NW);
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, lightningStrikes) {
    const auto ref = LightningStrikes();
    auto test = ref;

    test = ref;
    test.frequency = LightningStrikes::Frequency::CONSTANT;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.type.insert(LightningStrikes::Type::IN_CLOUD);
    EXPECT_FALSE(ref == test);

    test.distance.prevailing =
        Distance{Distance::Details::EXACTLY, 20000, Distance::Unit::METERS};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.directions.insert(CardinalDirection::NW);
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, icingForecast) {
    const auto ref = IcingForecast();
    auto test = ref;

    test = ref;
    test.severity = IcingForecast::Severity::LIGHT;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.type = IcingForecast::Type::MIXED;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.minHeight = Height{1200, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.maxHeight = Height{1200, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, turbulenceForecast) {
    const auto ref = TurbulenceForecast();
    auto test = ref;

    test = ref;
    test.severity = TurbulenceForecast::Severity::LIGHT;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.location = TurbulenceForecast::Location::IN_CLOUD;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.location = TurbulenceForecast::Location::IN_CLOUD;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.frequency = TurbulenceForecast::Frequency::FREQUENT;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.minHeight = Height{1200, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.maxHeight = Height{1200, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, essentials) {
    const auto ref = Essentials();
    auto test = ref;

    test = ref;
    test.windDirectionDegrees = 270;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.windDirectionVariable = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.windDirectionVarFromDegrees = 270;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.windDirectionVarToDegrees = 270;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.windSpeed = Speed{1, Speed::Unit::KT};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.gustSpeed = Speed{1, Speed::Unit::KT};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.windCalm = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.visibility =
        Distance{Distance::Details::EXACTLY, 3, Distance::Unit::STATUTE_MILES};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.cavok = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.skyCondition = Essentials::SkyCondition::OBSCURED;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.cloudLayers.push_back(CloudLayer());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.verticalVisibility = Height{100, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.weather.push_back(
        Weather{Weather::Phenomena::NO_SIGNIFICANT_WEATHER, {}});
    EXPECT_FALSE(ref == test);

    test = ref;
    test.seaLevelPressure = Pressure{3001, Pressure::Unit::IN_HG};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.windShear.push_back(WindShear());
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, trend) {
    const auto ref = Trend();
    auto test = ref;

    test = ref;
    test.type = Trend::Type::BECMG;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.probability = 30;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.timeFrom = Time{17, 20, 51};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.timeUntil = Time{17, 20, 51};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.timeAt = Time{17, 20, 51};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.forecast.windDirectionVariable = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.icing.push_back(IcingForecast());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.turbulence.push_back(TurbulenceForecast());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.vicinity.insert(ObservedPhenomena::CUMULONIMBUS);
    EXPECT_FALSE(ref == test);

    test = ref;
    test.windShearConditions = true;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, temperatureForecast) {
    const auto ref = TemperatureForecast();
    auto test = ref;

    test = ref;
    test.temperature = Temperature{10, Temperature::Unit::C};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.time = Time{17, 20, 59};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, reportWarning) {
    const auto ref = Report::Warning();
    auto test = ref;

    test = ref;
    test.message = Report::Warning::Message::DUPLICATED_DATA;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.id = "id";
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, report) {
    const auto ref = Report();
    auto test = ref;

    test = ref;
    test.type = Report::Type::TAF;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.missing = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.cancelled = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.correctional = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.amended = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.automated = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.correctionNumber = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.reportTime = Time{17, 21, 07};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.applicableFrom = Time{17, 21, 07};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.applicableUntil = Time{17, 21, 07};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.error = Report::Error::EMPTY_REPORT;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.warnings.push_back(Report::Warning());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.plainText.push_back("test");
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, station) {
    const auto ref = Station();
    auto test = ref;

    test = ref;
    test.icaoCode = "UKLL";
    EXPECT_FALSE(ref == test);

    test = ref;
    test.autoType = Station::AutoType::AO2A;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.requiresMaintenance = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.noSpeciReports = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.noVisDirectionalVariation = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.missingData.insert(Station::MissingData::SLPNO);
    EXPECT_FALSE(ref == test);

    test = ref;
    test.runwaysNoCeilingData.insert(Runway());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.runwaysNoVisData.insert(Runway());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.directionsNoCeilingData.insert(CardinalDirection::W);
    EXPECT_FALSE(ref == test);

    test = ref;
    test.directionsNoVisData.insert(CardinalDirection::W);
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, aerodromeRunwayData) {
    const auto ref = Aerodrome::RunwayData();
    auto test = ref;

    test = ref;
    test.runway = Runway{31, Runway::Designator::NONE};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.notOperational = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.snoclo = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.clrd = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.windShearLowerLayers = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.deposits = Aerodrome::RunwayDeposits::DAMP;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.contaminationExtent =
        Aerodrome::RunwayContamExtent::LESS_THAN_11_PERCENT;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.depositDepth = Precipitation{1, Precipitation::Unit::MM};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.coefficient = 78;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.surfaceFrictionUnreliable = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.visualRange = DistanceRange{
        Distance{Distance::Details::EXACTLY, 1200, Distance::Unit::FEET},
        Distance(),
        Distance()};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.visualRangeTrend = Aerodrome::RvrTrend::DOWNWARD;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.ceiling = Ceiling{Height{100, Height::Unit::FEET}, Height(), Height()};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.visibility = DistanceRange{
        Distance{Distance::Details::EXACTLY, 4500, Distance::Unit::METERS},
        Distance(),
        Distance()};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, aerodromeDirectionData) {
    const auto ref = Aerodrome::DirectionData();
    auto test = ref;

    test = ref;
    test.cardinalDirection = CardinalDirection::W;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.ceiling = Ceiling{Height{100, Height::Unit::FEET}, Height(), Height()};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.visibility = DistanceRange{
        Distance{Distance::Details::EXACTLY, 4500, Distance::Unit::METERS},
        Distance(),
        Distance()};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, aerodrome) {
    const auto ref = Aerodrome();
    auto test = ref;

    test = ref;
    test.snoclo = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.colourCode = Aerodrome::ColourCode::BLUE;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.colourCodeBlack = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.runways.push_back(Aerodrome::RunwayData());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.directions.push_back(Aerodrome::DirectionData());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.ceiling = Ceiling{Height{100, Height::Unit::FEET}, Height(), Height()};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.surfaceVisibility = 
        Distance{Distance::Details::EXACTLY, 4500, Distance::Unit::METERS};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.towerVisibility = 
        Distance{Distance::Details::EXACTLY, 4500, Distance::Unit::METERS};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, windShear) {
    const auto ref = WindShear();
    auto test = ref;

    test = ref;
    test.height = Height{3000, Height::Unit::FEET};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.directionDegrees = 160;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.windSpeed = Speed {40, Speed::Unit::KT};
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, historicalWeatherEvent) {
    const auto ref = Historical::WeatherEvent();
    auto test = ref;

    test = ref;
    test.event = Historical::Event::ENDED;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.time = Time{17, 21, 40};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.weather.phenomena = Weather::Phenomena::NO_SIGNIFICANT_WEATHER;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, current) {
    const auto ref = Current();
    auto test = ref;

    test = ref;
    test.weatherData.cavok = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.variableVisibility.prevailing = 
        Distance{Distance::Details::EXACTLY, 1100, Distance::Unit::METERS};
    EXPECT_FALSE(ref == test);

    test = ref;
    test.obscurations.push_back(CloudLayer());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.lowCloudLayer = Current::LowCloudLayer::CB_CAL;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.midCloudLayer = Current::MidCloudLayer::AC_OF_CHAOTIC_SKY;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.highCloudLayer = Current::HighCloudLayer::CC;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.airTemperature.temperature = 10;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.dewPoint.temperature = 10;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.relativeHumidity = 82;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.pressureGroundLevel.pressure = 997;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.seaSurfaceTemperature.temperature = 6;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.waveHeight.waveHeight = 5;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.snowWaterEquivalent.amount = 10;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.snowDepthOnGround.amount = 10;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.snowIncreasingRapidly = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.phenomenaInVicinity.push_back(Vicinity());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.lightningStrikes.push_back(LightningStrikes());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.densityAltitude.height = 7000;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.hailstoneSizeQuartersInch = 2;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.frostOnInstrument = true;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, historical) {
    const auto ref = Historical();
    auto test = ref;

    test = ref;
    test.peakWindDirectionDegrees = 270;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.peakWindSpeed.speed = 20;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.peakWindObserved.minute = 20;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.windShift = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.windShiftFrontPassage = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.windShiftBegan.minute = 50;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.temperatureMin6h.temperature = 10;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.temperatureMax6h.temperature = 10;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.temperatureMin24h.temperature = 10;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.temperatureMax24h.temperature = 10;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.pressureTendency = Historical::PressureTendency::STEADY;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.pressureTrend = Historical::PressureTrend::HIGHER;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.pressureChange3h.pressure = 5;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.recentWeather.push_back(Historical::WeatherEvent());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.rainfall10m.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.rainfallSince0900LocalTime.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.precipitationSinceLastReport.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.precipitationTotal1h.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.precipitationFrozen3or6h.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.precipitationFrozen3h.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.precipitationFrozen6h.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.precipitationFrozen24h.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.snow6h.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.snowfallTotal.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.snowfallIncrease1h.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.icing1h.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.icing3h.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.icing6h.amount = 1;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.sunshineDurationMinutes24h = 119;
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, forecast) {
    const auto ref = Forecast();
    auto test = ref;

    test = ref;
    test.prevailing.windCalm = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.prevailingIcing.push_back(IcingForecast());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.prevailingTurbulence.push_back(TurbulenceForecast());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.prevailingVicinity.insert(ObservedPhenomena::CUMULONIMBUS);
    EXPECT_FALSE(ref == test);

    test = ref;
    test.prevailingWsConds = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.trends.push_back(Trend());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.noSignificantChanges = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.minTemperature.push_back(TemperatureForecast());
    EXPECT_FALSE(ref == test);

    test = ref;
    test.maxTemperature.push_back(TemperatureForecast());
    EXPECT_FALSE(ref == test);
}

TEST(ValidateComparisons, simple) {
    const auto ref = Simple();
    auto test = ref;

    test = ref;
    test.report.automated = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.station.icaoCode = "ZZZZ";
    EXPECT_FALSE(ref == test);

    test = ref;
    test.aerodrome.colourCodeBlack = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.current.frostOnInstrument = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.historical.windShift = true;
    EXPECT_FALSE(ref == test);

    test = ref;
    test.forecast.noSignificantChanges = true;
    EXPECT_FALSE(ref == test);
}
