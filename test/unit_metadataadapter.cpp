/*
* Copyright (C) 2020 Nick Naumenko (https://gitlab.com/nnaumenko,
* https:://github.com/nnaumenko)
* All rights reserved.
* This software may be modified and distributed under the terms
* of the MIT license. See the LICENSE file for details.
*/
#include <algorithm>
#include <set>
#include <vector>

#include "gtest/gtest.h"
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

bool operator==(const metafsimple::CloudLayer &lhs,
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

TEST(MetadataAdapter, setReportType_METAR) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::METAR;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportType(metaf::ReportType::METAR, false);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setReportType_SPECI) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::SPECI;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportType(metaf::ReportType::METAR, true);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setReportType_TAF) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::TAF;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportType(metaf::ReportType::TAF, false);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setReportType_TAF_SPECI) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::TAF;
    refReport.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::SPECI_IN_TAF, ""});

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportType(metaf::ReportType::TAF, true);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setReportType_UNKNOWN) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::ERROR;
    refReport.error = metafsimple::Report::Error::UNKNOWN_REPORT_TYPE;

    metafsimple::Report report1;
    metafsimple::Station station1;
    metafsimple::detail::WarningLogger wl1(report1.warnings);
    metafsimple::detail::MetadataAdapter mda1(report1, station1, &wl1);
    mda1.setReportType(metaf::ReportType::UNKNOWN, true);
    EXPECT_EQ(report1, refReport);
    EXPECT_EQ(station1, metafsimple::Station());

    metafsimple::Report report2;
    metafsimple::Station station2;
    metafsimple::detail::WarningLogger wl2(report2.warnings);
    metafsimple::detail::MetadataAdapter mda2(report2, station2, &wl2);
    mda2.setReportType(metaf::ReportType::UNKNOWN, true);
    EXPECT_EQ(report2, refReport);
    EXPECT_EQ(station2, metafsimple::Station());
}

TEST(MetadataAdapter, setSetReportError_NONE) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::NO_ERROR;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(metaf::ReportError::NONE);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setSetReportError_EMPTY_REPORT) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::EMPTY_REPORT;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(metaf::ReportError::EMPTY_REPORT);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setSetReportError_EXPECTED_REPORT_TYPE_OR_LOCATION) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::REPORT_HEADER_FORMAT;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(metaf::ReportError::EXPECTED_REPORT_TYPE_OR_LOCATION);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setSetReportError_EXPECTED_LOCATION) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::REPORT_HEADER_FORMAT;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(metaf::ReportError::EXPECTED_LOCATION);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setSetReportError_EXPECTED_REPORT_TIME) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::REPORT_HEADER_FORMAT;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(metaf::ReportError::EXPECTED_REPORT_TIME);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setSetReportError_EXPECTED_TIME_SPAN) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::REPORT_HEADER_FORMAT;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(metaf::ReportError::EXPECTED_TIME_SPAN);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setSetReportError_UNEXPECTED_REPORT_END) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::UNEXPECTED_REPORT_END;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(metaf::ReportError::UNEXPECTED_REPORT_END);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setSetReportError_UNEXPECTED_GROUP_AFTER_NIL) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::NIL_OR_CNL_FORMAT;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(metaf::ReportError::UNEXPECTED_GROUP_AFTER_NIL);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setSetReportError_UNEXPECTED_GROUP_AFTER_CNL) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::NIL_OR_CNL_FORMAT;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(metaf::ReportError::UNEXPECTED_GROUP_AFTER_CNL);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setSetReportError_UNEXPECTED_NIL_OR_CNL_IN_REPORT_BODY) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::NIL_OR_CNL_FORMAT;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(
        metaf::ReportError::UNEXPECTED_NIL_OR_CNL_IN_REPORT_BODY);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setSetReportError_AMD_ALLOWED_IN_TAF_ONLY) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::GROUP_NOT_ALLOWED;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(metaf::ReportError::AMD_ALLOWED_IN_TAF_ONLY);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setSetReportError_CNL_ALLOWED_IN_TAF_ONLY) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::NIL_OR_CNL_FORMAT;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(metaf::ReportError::CNL_ALLOWED_IN_TAF_ONLY);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter,
     setSetReportError_MAINTENANCE_INDICATOR_ALLOWED_IN_METAR_ONLY) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::GROUP_NOT_ALLOWED;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(
        metaf::ReportError::MAINTENANCE_INDICATOR_ALLOWED_IN_METAR_ONLY);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setSetReportError_REPORT_TOO_LARGE) {
    metafsimple::Report refReport;
    refReport.error = metafsimple::Report::Error::REPORT_TOO_LARGE;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportError(metaf::ReportError::REPORT_TOO_LARGE);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}
