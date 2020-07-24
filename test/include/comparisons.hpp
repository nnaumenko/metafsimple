/*
* Copyright (C) 2020 Nick Naumenko (https://gitlab.com/nnaumenko,
* https:://github.com/nnaumenko)
* All rights reserved.
* This software may be modified and distributed under the terms
* of the MIT license. See the LICENSE file for details.
*/

#ifndef COMPARISONS_HPP
#define COMPARISONS_HPP

#include "metafsimple.hpp"

namespace metafsimple {

static inline bool operator==(const Runway &lhs, const Runway &rhs) {
    if (lhs.number != rhs.number) return false;
    if (lhs.designator != rhs.designator) return false;
    return true;
}

static inline bool operator==(const Time &lhs, const Time &rhs) {
    if (lhs.day != rhs.day) return false;
    if (lhs.hour != rhs.hour) return false;
    if (lhs.minute != rhs.minute) return false;
    return true;
}

static inline bool operator==(const Temperature &lhs, const Temperature &rhs) {
    if (lhs.temperature != rhs.temperature) return false;
    if (lhs.unit != rhs.unit) return false;
    return true;
}

static inline bool operator==(const Speed &lhs, const Speed &rhs) {
    if (lhs.speed != rhs.speed) return false;
    if (lhs.unit != rhs.unit) return false;
    return true;
}

static inline bool operator==(const Distance &lhs, const Distance &rhs) {
    if (lhs.details != rhs.details) return false;
    if (lhs.distance != rhs.distance) return false;
    if (lhs.unit != rhs.unit) return false;
    return true;
}

static inline bool operator==(const DistanceRange &lhs,
                              const DistanceRange &rhs) {
    if (!(lhs.prevailing == rhs.prevailing)) return false;
    if (!(lhs.minimum == rhs.minimum)) return false;
    if (!(lhs.maximum == rhs.maximum)) return false;
    return true;
}

static inline bool operator==(const Height &lhs, const Height &rhs) {
    if (lhs.height != rhs.height) return false;
    if (lhs.unit != rhs.unit) return false;
    return true;
}

static inline bool operator==(const Ceiling &lhs, const Ceiling &rhs) {
    if (!(lhs.exact == rhs.exact)) return false;
    if (!(lhs.minimum == rhs.minimum)) return false;
    if (!(lhs.maximum == rhs.maximum)) return false;
    return true;
}

static inline bool operator==(const Pressure &lhs, const Pressure &rhs) {
    if (lhs.pressure != rhs.pressure) return false;
    if (lhs.unit != rhs.unit) return false;
    return true;
}

static inline bool operator==(const Precipitation &lhs,
                              const Precipitation &rhs) {
    if (lhs.amount != rhs.amount) return false;
    if (lhs.unit != rhs.unit) return false;
    return true;
}

static inline bool operator==(const WaveHeight &lhs, const WaveHeight &rhs) {
    if (lhs.waveHeight != rhs.waveHeight) return false;
    if (lhs.unit != rhs.unit) return false;
    return true;
}

static inline bool operator==(const Weather &lhs, const Weather &rhs) {
    if (lhs.phenomena != rhs.phenomena) return false;
    if (lhs.precipitation != rhs.precipitation) return false;
    return true;
}

static inline bool operator==(const CloudLayer &lhs, const CloudLayer &rhs) {
    if (lhs.amount != rhs.amount) return false;
    if (!(lhs.height == rhs.height)) return false;
    if (lhs.details != rhs.details) return false;
    if (lhs.okta != rhs.okta) return false;
    return true;
}

static inline bool operator==(const Vicinity &lhs, const Vicinity &rhs) {
    if (lhs.phenomena != rhs.phenomena) return false;
    if (!(lhs.distance == rhs.distance)) return false;
    if (lhs.moving != rhs.moving) return false;
    if (lhs.directions != rhs.directions) return false;
    return true;
}

static inline bool operator==(const LightningStrikes &lhs,
                              const LightningStrikes &rhs) {
    if (lhs.frequency != rhs.frequency) return false;
    if (lhs.type != rhs.type) return false;
    if (lhs.directions != rhs.directions) return false;
    if (!(lhs.distance == rhs.distance)) return false;
    return true;
}

static inline bool operator==(const IcingForecast &lhs,
                              const IcingForecast &rhs) {
    if (lhs.severity != rhs.severity) return false;
    if (lhs.type != rhs.type) return false;
    if (!(lhs.minHeight == rhs.minHeight)) return false;
    if (!(lhs.maxHeight == rhs.maxHeight)) return false;
    return true;
}

static inline bool operator==(const TurbulenceForecast &lhs,
                              const TurbulenceForecast &rhs) {
    if (lhs.frequency == rhs.frequency) return false;
    if (lhs.location == rhs.location) return false;
    if (lhs.severity == rhs.severity) return false;
    if (!(lhs.minHeight == rhs.minHeight)) return false;
    if (!(lhs.maxHeight == rhs.maxHeight)) return false;
    return true;
}

static inline bool operator==(const Essentials &lhs, const Essentials &rhs) {
    if (lhs.windDirectionDegrees != rhs.windDirectionDegrees) return false;
    if (lhs.windDirectionVariable != rhs.windDirectionVariable) return false;
    if (lhs.windDirectionVarFromDegrees != rhs.windDirectionVarFromDegrees)
        return false;
    if (lhs.windDirectionVarToDegrees != rhs.windDirectionVarToDegrees)
        return false;
    if (!(lhs.windSpeed == rhs.windSpeed)) return false;
    if (!(lhs.gustSpeed == rhs.gustSpeed)) return false;
    if (lhs.windCalm != rhs.windCalm) return false;
    if (!(lhs.visibility == rhs.visibility)) return false;
    if (lhs.cavok != rhs.cavok) return false;
    if (lhs.skyCondition != rhs.skyCondition) return false;
    if (lhs.cloudLayers != rhs.cloudLayers) return false;
    if (!(lhs.verticalVisibility == rhs.verticalVisibility)) return false;
    if (lhs.weather != rhs.weather) return false;
    return true;
}

static inline bool operator==(const Trend &lhs, const Trend &rhs) {
    if (lhs.type != rhs.type) return false;
    if (lhs.probability != rhs.probability) return false;
    if (!(lhs.timeFrom == rhs.timeFrom)) return false;
    if (!(lhs.timeUntil == rhs.timeUntil)) return false;
    if (!(lhs.timeAt == rhs.timeAt)) return false;
    if (!(lhs.forecast == rhs.forecast)) return false;
    return true;
}

static inline bool operator==(const Report::Warning &lhs,
                              const Report::Warning &rhs) {
    if (lhs.message != rhs.message) return false;
    if (lhs.id != rhs.id) return false;
    return true;
}

static inline bool operator==(const Report &lhs, const Report &rhs) {
    if (lhs.type != rhs.type) return false;
    if (lhs.missing != rhs.missing) return false;
    if (lhs.cancelled != rhs.cancelled) return false;
    if (lhs.correctional != rhs.correctional) return false;
    if (lhs.amended != rhs.amended) return false;
    if (lhs.automated != rhs.automated) return false;
    if (lhs.correctionNumber != rhs.correctionNumber) return false;
    if (!(lhs.reportTime == rhs.reportTime)) return false;
    if (!(lhs.applicableFrom == rhs.applicableFrom)) return false;
    if (!(lhs.applicableUntil == rhs.applicableUntil)) return false;
    if (lhs.error != rhs.error) return false;
    if (lhs.warnings != rhs.warnings) return false;
    if (lhs.plainText != rhs.plainText) return false;
    return true;
}

static inline bool operator==(const Station &lhs, const Station &rhs) {
    if (lhs.icaoCode != rhs.icaoCode) return false;
    if (lhs.autoType != rhs.autoType) return false;
    if (lhs.requiresMaintenance != rhs.requiresMaintenance) return false;
    if (lhs.noSpeciReports != rhs.noSpeciReports) return false;
    if (lhs.noVisDirectionalVariation != rhs.noVisDirectionalVariation)
        return false;
    if (lhs.missingData != rhs.missingData) return false;
    if (lhs.runwaysNoCeilingData != rhs.runwaysNoCeilingData) return false;
    if (lhs.runwaysNoVisData != rhs.runwaysNoVisData) return false;
    if (lhs.directionsNoCeilingData != rhs.directionsNoCeilingData)
        return false;
    if (lhs.directionsNoVisData != rhs.directionsNoVisData) return false;
    return true;
}

static inline bool operator==(const Aerodrome::RunwayData &lhs,
                              const Aerodrome::RunwayData &rhs) {
    if (!(lhs.runway == rhs.runway)) return false;
    if (lhs.notOperational != rhs.notOperational) return false;
    if (lhs.snoclo != rhs.snoclo) return false;
    if (lhs.clrd != rhs.clrd) return false;
    if (lhs.windShearLowerLayers != rhs.windShearLowerLayers) return false;
    if (lhs.deposits != rhs.deposits) return false;
    if (lhs.contaminationExtent != rhs.contaminationExtent) return false;
    if (!(lhs.depositDepth == rhs.depositDepth)) return false;
    if (lhs.coefficient != rhs.coefficient) return false;
    if (lhs.surfaceFrictionUnreliable != rhs.surfaceFrictionUnreliable)
        return false;
    if (!(lhs.visualRange == rhs.visualRange)) return false;
    if (lhs.visualRangeTrend != rhs.visualRangeTrend) return false;
    if (!(lhs.ceiling == rhs.ceiling)) return false;
    if (!(lhs.visibility == rhs.visibility)) return false;
    return true;
}

static inline bool operator==(const Aerodrome::DirectionData &lhs,
                              const Aerodrome::DirectionData &rhs) {
    if (lhs.cardinalDirection != rhs.cardinalDirection) return false;
    if (!(lhs.ceiling == rhs.ceiling)) return false;
    if (!(lhs.visibility == rhs.visibility)) return false;
    return true;
}

static inline bool operator==(const Aerodrome &lhs, const Aerodrome &rhs) {
    if (lhs.snoclo != rhs.snoclo) return false;
    if (lhs.colourCode != rhs.colourCode) return false;
    if (lhs.colourCodeBlack != rhs.colourCodeBlack) return false;
    if (lhs.runways != rhs.runways) return false;
    if (lhs.directions != rhs.directions) return false;
    if (!(lhs.ceiling == rhs.ceiling)) return false;
    if (!(lhs.surfaceVisibility == rhs.surfaceVisibility)) return false;
    if (!(lhs.towerVisibility == rhs.towerVisibility)) return false;
    return true;
}

static inline bool operator==(const Current::WindShear &lhs,
                              const Current::WindShear &rhs) {
    if (!(lhs.height == rhs.height)) return false;
    if (lhs.directionDegrees != rhs.directionDegrees) return false;
    if (!(lhs.windSpeed == rhs.windSpeed)) return false;
    return true;
}

static inline bool operator==(const Current &lhs, const Current &rhs) {
    if (!(lhs.weatherData == rhs.weatherData)) return false;
    if (!(lhs.variableVisibility == rhs.variableVisibility)) return false;
    if (lhs.obscurations != rhs.obscurations) return false;
    if (lhs.lowCloudLayer != rhs.lowCloudLayer) return false;
    if (lhs.midCloudLayer != rhs.midCloudLayer) return false;
    if (lhs.highCloudLayer != rhs.highCloudLayer) return false;
    if (!(lhs.airTemperature == rhs.airTemperature)) return false;
    if (!(lhs.dewPoint == rhs.dewPoint)) return false;
    if (lhs.relativeHumidity != rhs.relativeHumidity) return false;
    if (!(lhs.pressureSeaLevel == rhs.pressureSeaLevel)) return false;
    if (!(lhs.pressureGroundLevel == rhs.pressureGroundLevel)) return false;
    if (!(lhs.seaSurfaceTemperature == rhs.seaSurfaceTemperature)) return false;
    if (!(lhs.waveHeight == rhs.waveHeight)) return false;
    if (!(lhs.snowWaterEquivalent == rhs.snowWaterEquivalent)) return false;
    if (!(lhs.snowDepthOnGround == rhs.snowDepthOnGround)) return false;
    if (lhs.snowIncreasingRapidly != rhs.snowIncreasingRapidly) return false;
    if (lhs.windShear != rhs.windShear) return false;
    if (lhs.phenomenaInVicinity != rhs.phenomenaInVicinity) return false;
    if (lhs.lightningStrikes != rhs.lightningStrikes) return false;
    if (!(lhs.densityAltitude == rhs.densityAltitude)) return false;
    if (lhs.hailstoneSizeQuartersInch != rhs.hailstoneSizeQuartersInch)
        return false;
    if (lhs.frostOnInstrument != rhs.frostOnInstrument) return false;
    return true;
}

static inline bool operator==(const Historical::WeatherEvent &lhs,
                              const Historical::WeatherEvent &rhs) {
    if (lhs.event == rhs.event) return false;
    if (lhs.time == rhs.time) return false;
    if (lhs.weather == rhs.weather) return false;
    return true;
}

static inline bool operator==(const Historical &lhs, const Historical &rhs) {
    if (lhs.peakWindDirectionDegrees != rhs.peakWindDirectionDegrees)
        return false;
    if (!(lhs.peakWindSpeed == rhs.peakWindSpeed)) return false;
    if (!(lhs.peakWindObserved == rhs.peakWindObserved)) return false;
    if (lhs.windShift != rhs.windShift) return false;
    if (lhs.windShiftFrontPassage != rhs.windShiftFrontPassage) return false;
    if (!(lhs.windShiftBegan == rhs.windShiftBegan)) return false;
    if (!(lhs.temperatureMin6h == rhs.temperatureMin6h)) return false;
    if (!(lhs.temperatureMax6h == rhs.temperatureMax6h)) return false;
    if (!(lhs.temperatureMin24h == rhs.temperatureMin24h)) return false;
    if (!(lhs.temperatureMax24h == rhs.temperatureMax24h)) return false;
    if (lhs.pressureTendency != rhs.pressureTendency) return false;
    if (lhs.pressureTrend != rhs.pressureTrend) return false;
    if (!(lhs.pressureChange3h == rhs.pressureChange3h)) return false;
    if (!(lhs.recentWeather == rhs.recentWeather)) return false;
    if (!(lhs.rainfall10m == rhs.rainfall10m)) return false;
    if (!(lhs.rainfallSince0900LocalTime == rhs.rainfallSince0900LocalTime))
        return false;
    if (!(lhs.precipitationSinceLastReport == rhs.precipitationSinceLastReport))
        return false;
    if (!(lhs.precipitationTotal1h == rhs.precipitationTotal1h)) return false;
    if (!(lhs.precipitationFrozen3or6h == rhs.precipitationFrozen3or6h))
        return false;
    if (!(lhs.precipitationFrozen3h == rhs.precipitationFrozen3h)) return false;
    if (!(lhs.precipitationFrozen6h == rhs.precipitationFrozen6h)) return false;
    if (!(lhs.precipitationFrozen24h == rhs.precipitationFrozen24h)) return false;
    if (!(lhs.snow6h == rhs.snow6h)) return false;
    if (!(lhs.snowfallTotal == rhs.snowfallTotal)) return false;
    if (!(lhs.snowfallIncrease1h == rhs.snowfallIncrease1h)) return false;
    if (!(lhs.icing1h == rhs.icing1h)) return false;
    if (!(lhs.icing3h == rhs.icing3h)) return false;
    if (!(lhs.icing6h == rhs.icing6h)) return false;
    if (lhs.sunshineDurationMinutes24h != rhs.sunshineDurationMinutes24h)
        return false;
    return true;
}

static inline bool operator==(const Forecast &lhs, const Forecast &rhs) {
    if (!(lhs.trends == rhs.trends)) return false;
    if (lhs.noSignificantChanges != rhs.noSignificantChanges) return false;
    if (lhs.windShearConditions != rhs.windShearConditions) return false;
    if (!(lhs.minTemperature == rhs.minTemperature)) return false;
    if (!(lhs.minTemperatureTime == rhs.minTemperatureTime)) return false;
    if (!(lhs.maxTemperature == rhs.maxTemperature)) return false;
    if (!(lhs.maxTemperatureTime == rhs.maxTemperatureTime)) return false;
    if (lhs.icing != rhs.icing) return false;
    if (lhs.turbulence != rhs.turbulence) return false;
    if (!(lhs.lowestQnh == rhs.lowestQnh)) return false;
    return true;
}

static inline bool operator==(const Simple &lhs, const Simple &rhs) {
    if (!(lhs.report == rhs.report)) return false;
    if (!(lhs.station == rhs.station)) return false;
    if (!(lhs.aerodrome == rhs.aerodrome)) return false;
    if (!(lhs.current == rhs.current)) return false;
    if (!(lhs.historical == rhs.historical)) return false;
    if (!(lhs.forecast == rhs.forecast)) return false;
    return true;
}

}  // namespace metafsimple

#endif  // #ifdef COMPARISONS_HPP
