/*
* Copyright (C) 2020 Nick Naumenko (https://gitlab.com/nnaumenko,
* https:://github.com/nnaumenko)
* All rights reserved.
* This software may be modified and distributed under the terms
* of the MIT license. See the LICENSE file for details.
*/

#include "gtest/gtest.h"
#include "metafsimple.hpp"

TEST(ParseSimplifyReport, basicMetar) {
    static const auto rawReport =
        "METAR SCCH 061700Z 23007KT CAVOK 07/03 Q1016=";
    const auto result = metafsimple::simplify(rawReport);

    EXPECT_EQ(result.report.type, metafsimple::Report::Type::METAR);
    EXPECT_FALSE(result.report.missing);
    EXPECT_FALSE(result.report.cancelled);
    EXPECT_FALSE(result.report.correctional);
    EXPECT_FALSE(result.report.amended);
    EXPECT_FALSE(result.report.automated);
    EXPECT_EQ(result.report.correctionNumber, 0);
    EXPECT_EQ(result.report.reportTime.day, std::optional<int>(6));
    EXPECT_EQ(result.report.reportTime.hour, std::optional<int>(17));
    EXPECT_EQ(result.report.reportTime.minute, std::optional<int>(0));
    EXPECT_EQ(result.report.applicableFrom.day, std::optional<int>());
    EXPECT_EQ(result.report.applicableFrom.hour, std::optional<int>());
    EXPECT_EQ(result.report.applicableFrom.minute, std::optional<int>());
    EXPECT_EQ(result.report.applicableUntil.day, std::optional<int>());
    EXPECT_EQ(result.report.applicableUntil.hour, std::optional<int>());
    EXPECT_EQ(result.report.applicableUntil.minute, std::optional<int>());
    EXPECT_EQ(result.report.error, metafsimple::Report::Error::NO_ERROR);
    EXPECT_EQ(result.report.warnings.size(), 0u);
    EXPECT_EQ(result.report.plainText.size(), 0u);

    EXPECT_EQ(result.station.icaoCode, "SCCH");
    EXPECT_EQ(result.station.autoType,
              metafsimple::Station::AutoType::NONE);
    EXPECT_FALSE(result.station.requiresMaintenance);
    EXPECT_FALSE(result.station.noSpeciReports);
    EXPECT_FALSE(result.station.noVisDirectionalVariation);
    EXPECT_EQ(result.station.missingData.size(), 0u);
    EXPECT_EQ(result.station.runwaysNoCeilingData.size(), 0u);
    EXPECT_EQ(result.station.runwaysNoVisData.size(), 0u);
    EXPECT_EQ(result.station.directionsNoCeilingData.size(), 0u);
    EXPECT_EQ(result.station.directionsNoVisData.size(), 0u);

    EXPECT_FALSE(result.aerodrome.snoclo);
    EXPECT_EQ(result.aerodrome.colourCode,
              metafsimple::Aerodrome::ColourCode::NOT_SPECIFIED);
    EXPECT_FALSE(result.aerodrome.colourCodeBlack);
    EXPECT_EQ(result.aerodrome.runways.size(), 0u);
    EXPECT_EQ(result.aerodrome.directions.size(), 0u);
    EXPECT_EQ(result.aerodrome.ceiling.exact.height, std::optional<int>());
    EXPECT_EQ(result.aerodrome.ceiling.maximum.height, std::optional<int>());
    EXPECT_EQ(result.aerodrome.ceiling.minimum.height, std::optional<int>());
    EXPECT_EQ(result.aerodrome.surfaceVisibility.distance,
              std::optional<int>());
    EXPECT_EQ(result.aerodrome.towerVisibility.distance,
              std::optional<int>());

    EXPECT_EQ(result.current.weatherData.windDirectionDegrees,
              std::optional<int>(230));
    EXPECT_FALSE(result.current.weatherData.windDirectionVariable);
    EXPECT_EQ(result.current.weatherData.windDirectionVarFromDegrees,
              std::optional<int>());
    EXPECT_EQ(result.current.weatherData.windDirectionVarToDegrees,
              std::optional<int>());
    EXPECT_EQ(result.current.weatherData.windSpeed.speed,
              std::optional<int>(7));
    EXPECT_EQ(result.current.weatherData.windSpeed.unit,
              metafsimple::Speed::Unit::KT);
    EXPECT_EQ(result.current.weatherData.gustSpeed.speed,
              std::optional<int>());
    EXPECT_FALSE(result.current.weatherData.windCalm);
    EXPECT_EQ(result.current.weatherData.visibility.details,
              metafsimple::Distance::Details::MORE_THAN);
    EXPECT_EQ(result.current.weatherData.visibility.distance,
              std::optional<int>(10000));
    EXPECT_EQ(result.current.weatherData.visibility.unit,
              metafsimple::Distance::Unit::METERS);
    EXPECT_TRUE(result.current.weatherData.cavok);
    EXPECT_EQ(result.current.weatherData.skyCondition,
              metafsimple::Essentials::SkyCondition::CAVOK);
    EXPECT_EQ(result.current.weatherData.cloudLayers.size(), 0u);
    EXPECT_EQ(result.current.weatherData.verticalVisibility.height,
              std::optional<int>());
    EXPECT_EQ(result.current.weatherData.weather.size(), 0u);

    EXPECT_EQ(result.current.variableVisibility.prevailing.distance,
              std::optional<int>());
    EXPECT_EQ(result.current.variableVisibility.minimum.distance,
              std::optional<int>());
    EXPECT_EQ(result.current.variableVisibility.maximum.distance,
              std::optional<int>());
    EXPECT_EQ(result.current.obscurations.size(), 0u);
    EXPECT_EQ(result.current.lowCloudLayer,
              metafsimple::Current::LowCloudLayer::UNKNOWN);
    EXPECT_EQ(result.current.midCloudLayer,
              metafsimple::Current::MidCloudLayer::UNKNOWN);
    EXPECT_EQ(result.current.highCloudLayer,
              metafsimple::Current::HighCloudLayer::UNKNOWN);
    EXPECT_EQ(result.current.airTemperature.temperature,
              std::optional<int>(7));
    EXPECT_EQ(result.current.airTemperature.unit,
              metafsimple::Temperature::Unit::C);
    EXPECT_EQ(result.current.dewPoint.temperature,
              std::optional<int>(3));
    EXPECT_EQ(result.current.dewPoint.unit,
              metafsimple::Temperature::Unit::C);
    EXPECT_EQ(result.current.pressureSeaLevel.pressure, 1016);
    EXPECT_EQ(result.current.pressureSeaLevel.unit,
              metafsimple::Pressure::Unit::HPA);
    EXPECT_EQ(result.current.waveHeight.waveHeight, std::optional<int>());
    EXPECT_EQ(result.current.snowWaterEquivalent.amount, std::optional<int>());
    EXPECT_EQ(result.current.snowDepthOnGround.amount, std::optional<int>());
    EXPECT_FALSE(result.current.snowIncreasingRapidly);
    EXPECT_EQ(result.current.windShear.size(), 0u);
    EXPECT_EQ(result.current.phenomenaInVicinity.size(), 0u);
    EXPECT_EQ(result.current.lightningStrikes.size(), 0u);
    EXPECT_EQ(result.current.densityAltitude.height, std::optional<int>());
    EXPECT_EQ(result.current.hailstoneSizeQuartersInch, std::optional<int>());
    EXPECT_FALSE(result.current.frostOnInstrument);

    EXPECT_EQ(result.historical.peakWindDirectionDegrees, std::optional<int>());
    EXPECT_EQ(result.historical.peakWindSpeed.speed, std::optional<int>());
    EXPECT_EQ(result.historical.peakWindObserved.day, std::optional<int>());
    EXPECT_EQ(result.historical.peakWindObserved.hour, std::optional<int>());
    EXPECT_EQ(result.historical.peakWindObserved.minute, std::optional<int>());
    EXPECT_FALSE(result.historical.windShift);
    EXPECT_FALSE(result.historical.windShiftFrontPassage);
    EXPECT_EQ(result.historical.windShiftBegan.day, std::optional<int>());
    EXPECT_EQ(result.historical.windShiftBegan.hour, std::optional<int>());
    EXPECT_EQ(result.historical.windShiftBegan.minute, std::optional<int>());
    EXPECT_EQ(result.historical.temperatureMin6h.temperature,
              std::optional<int>());
    EXPECT_EQ(result.historical.temperatureMin6h.temperature,
              std::optional<int>());
    EXPECT_EQ(result.historical.temperatureMin24h.temperature,
              std::optional<int>());
    EXPECT_EQ(result.historical.temperatureMin24h.temperature,
              std::optional<int>());
    EXPECT_EQ(result.historical.pressureTendency,
              metafsimple::Historical::PressureTendency::UNKNOWN);
    EXPECT_EQ(result.historical.pressureTrend,
              metafsimple::Historical::PressureTrend::UNKNOWN);
    EXPECT_EQ(result.historical.pressureChange3h.pressure,
              std::optional<int>());
    EXPECT_EQ(result.historical.recentWeather.size(), 0u);
    EXPECT_EQ(result.historical.rainfall10m.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.rainfallSince0900LocalTime.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.precipitationSinceLastReport.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.precipitationTotal1h.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.precipitationFrozen3or6h.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.precipitationFrozen3h.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.precipitationFrozen6h.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.precipitationFrozen24h.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.snow6h.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.snowfallTotal.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.snowfallIncrease1h.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.icing1h.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.icing3h.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.icing6h.amount,
              std::optional<int>());
    EXPECT_EQ(result.historical.sunshineDurationMinutes24h,
              std::optional<int>());

    EXPECT_EQ(result.forecast.trends.size(), 0u);
    EXPECT_EQ(result.forecast.minTemperature.temperature, std::optional<int>());
    EXPECT_EQ(result.forecast.minTemperatureTime.day, std::optional<int>());
    EXPECT_EQ(result.forecast.minTemperatureTime.hour, std::optional<int>());
    EXPECT_EQ(result.forecast.minTemperatureTime.minute, std::optional<int>());
    EXPECT_EQ(result.forecast.maxTemperature.temperature, std::optional<int>());
    EXPECT_EQ(result.forecast.maxTemperatureTime.day, std::optional<int>());
    EXPECT_EQ(result.forecast.maxTemperatureTime.hour, std::optional<int>());
    EXPECT_EQ(result.forecast.maxTemperatureTime.minute, std::optional<int>());
    EXPECT_FALSE(result.forecast.windShearConditions);
    EXPECT_EQ(result.forecast.icing.size(), 0u);
    EXPECT_EQ(result.forecast.turbulence.size(), 0u);
    EXPECT_EQ(result.forecast.lowestQnh.pressure, std::optional<int>());
}