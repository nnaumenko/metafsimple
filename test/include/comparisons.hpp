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

static inline bool operator==(const metafsimple::Runway &lhs,
                              const metafsimple::Runway &rhs) {
    return lhs.number == rhs.number && lhs.designator == rhs.designator;
}

static inline bool operator==(const metafsimple::Time &lhs,
                              const metafsimple::Time &rhs) {
    return lhs.day == rhs.day &&
           lhs.hour == rhs.hour &&
           lhs.minute == rhs.minute;
}

static inline bool operator==(const metafsimple::Temperature &lhs,
                              const metafsimple::Temperature &rhs) {
    return lhs.temperature == rhs.temperature && lhs.unit == rhs.unit;
}

static inline bool operator==(const metafsimple::Speed &lhs,
                              const metafsimple::Speed &rhs) {
    return lhs.speed == rhs.speed && lhs.unit == rhs.unit;
}

static inline bool operator==(const metafsimple::Distance &lhs,
                              const metafsimple::Distance &rhs) {
    return lhs.details == rhs.details &&
           lhs.distance == rhs.distance &&
           lhs.unit == rhs.unit;
}

static inline bool operator==(const metafsimple::DistanceRange &lhs,
                              const metafsimple::DistanceRange &rhs) {
    return lhs.prevailing == rhs.prevailing &&
           lhs.minimum == rhs.minimum &&
           lhs.maximum == rhs.maximum;
}

static inline bool operator==(const metafsimple::Height &lhs,
                              const metafsimple::Height &rhs) {
    return lhs.height == rhs.height && lhs.unit == rhs.unit;
}

static inline bool operator==(const metafsimple::Ceiling &lhs,
                              const metafsimple::Ceiling &rhs) {
    return lhs.exact == rhs.exact &&
           lhs.minimum == rhs.minimum &&
           lhs.maximum == rhs.maximum;
}

static inline bool operator==(const metafsimple::Pressure &lhs,
                              const metafsimple::Pressure &rhs) {
    return lhs.pressure == rhs.pressure && lhs.unit == rhs.unit;
}

static inline bool operator==(const metafsimple::Precipitation &lhs,
                              const metafsimple::Precipitation &rhs) {
    return lhs.amount == rhs.amount && lhs.unit == rhs.unit;
}

static inline bool operator==(const metafsimple::WaveHeight &lhs,
                              const metafsimple::WaveHeight &rhs) {
    return lhs.waveHeight == rhs.waveHeight && lhs.unit == rhs.unit;
}

static inline bool operator==(const metafsimple::Weather &lhs,
                              const metafsimple::Weather &rhs) {
    return lhs.phenomena == rhs.phenomena &&
           lhs.precipitation == rhs.precipitation;
}

static inline bool operator==(const metafsimple::CloudLayer &lhs,
                const metafsimple::CloudLayer &rhs) {
    return lhs.amount == rhs.amount &&
           lhs.height == rhs.height &&
           lhs.details == rhs.details &&
           lhs.okta == rhs.okta;
}

static inline bool operator==(const metafsimple::Vicinity &lhs,
                              const metafsimple::Vicinity &rhs) {
    return lhs.phenomena == rhs.phenomena &&
           lhs.distance == rhs.distance &&
           lhs.moving == rhs.moving &&
           lhs.directions == rhs.directions;
}

static inline bool operator==(const metafsimple::LightningStrikes &lhs,
                              const metafsimple::LightningStrikes &rhs) {
    return lhs.frequency == rhs.frequency &&
           lhs.type == rhs.type &&
           lhs.directions == rhs.directions &&
           lhs.distance == rhs.distance;
}

static inline bool operator==(const metafsimple::IcingForecast &lhs,
                              const metafsimple::IcingForecast &rhs) {
    return lhs.severity == rhs.severity &&
           lhs.type == rhs.type &&
           lhs.minHeight == rhs.minHeight &&
           lhs.maxHeight == rhs.maxHeight;
}

static inline bool operator==(const metafsimple::TurbulenceForecast &lhs,
                              const metafsimple::TurbulenceForecast &rhs) {
    return lhs.frequency == rhs.frequency &&
           lhs.location == rhs.location &&
           lhs.severity == rhs.severity &&
           lhs.minHeight == rhs.minHeight &&
           lhs.maxHeight == rhs.maxHeight;
}

static inline bool operator==(const metafsimple::Essentials &lhs,
                              const metafsimple::Essentials &rhs) {
    return lhs.windDirectionDegrees == rhs.windDirectionDegrees &&
           lhs.windDirectionVariable == rhs.windDirectionVariable &&
           lhs.windDirectionVarFromDegrees == rhs.windDirectionVarFromDegrees &&
           lhs.windDirectionVarToDegrees == rhs.windDirectionVarToDegrees &&
           lhs.windSpeed == rhs.windSpeed &&
           lhs.gustSpeed == rhs.gustSpeed &&
           lhs.windCalm == rhs.windCalm &&
           lhs.visibility == rhs.visibility &&
           lhs.cavok == rhs.cavok &&
           lhs.skyCondition == rhs.skyCondition &&
           lhs.cloudLayers == rhs.cloudLayers &&
           lhs.verticalVisibility == rhs.verticalVisibility &&
           lhs.weather == rhs.weather;
}

static inline bool operator==(const metafsimple::Trend &lhs,
                              const metafsimple::Trend &rhs) {
    return lhs.type == rhs.type &&
           lhs.probability == rhs.probability;  // &&
    lhs.timeFrom == rhs.timeFrom &&lhs.timeUntil == rhs.timeUntil &&lhs.timeAt == rhs.timeAt &&lhs.forecast == rhs.forecast;
}

static inline bool operator==(const metafsimple::Report::Warning &lhs,
                              const metafsimple::Report::Warning &rhs) {
    return lhs.message == rhs.message && lhs.id == rhs.id;
}

static inline bool operator==(const metafsimple::Report &lhs,
                              const metafsimple::Report &rhs) {
    return lhs.type == rhs.type &&
           lhs.missing == rhs.missing &&
           lhs.cancelled == rhs.cancelled &&
           lhs.correctional == rhs.correctional &&
           lhs.amended == rhs.amended &&
           lhs.automated == rhs.automated &&
           lhs.correctionNumber == rhs.correctionNumber &&
           lhs.reportTime == rhs.reportTime &&
           lhs.applicableFrom == rhs.applicableFrom &&
           lhs.applicableUntil == rhs.applicableUntil &&
           lhs.error == rhs.error &&
           lhs.warnings == rhs.warnings &&
           lhs.plainText == rhs.plainText;
}

static inline bool operator==(const metafsimple::Station &lhs,
                              const metafsimple::Station &rhs) {
    return lhs.icaoCode == rhs.icaoCode &&
           lhs.autoType == rhs.autoType &&
           lhs.requiresMaintenance == rhs.requiresMaintenance &&
           lhs.noSpeciReports == rhs.noSpeciReports &&
           lhs.noVisDirectionalVariation == rhs.noVisDirectionalVariation &&
           lhs.missingData == rhs.missingData &&
           lhs.runwaysNoCeilingData == rhs.runwaysNoCeilingData &&
           lhs.runwaysNoVisData == rhs.runwaysNoVisData &&
           lhs.directionsNoCeilingData == rhs.directionsNoCeilingData &&
           lhs.directionsNoVisData == rhs.directionsNoVisData;
}

}  // namespace metafsimple

#endif // #ifdef COMPARISONS_HPP

