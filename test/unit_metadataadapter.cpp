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

#include "comparisons.hpp"
#include "gtest/gtest.h"
#include "metafsimple.hpp"

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

TEST(MetadataAdapter, setLocation) {
    static const std::string icaoCode = "UKLL";
    metafsimple::Station refStation;
    refStation.icaoCode = icaoCode;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setLocation(icaoCode);

    EXPECT_EQ(report, metafsimple::Report());
    EXPECT_EQ(station, refStation);
}

TEST(MetadataAdapter, setLocationMismatch) {
    static const std::string icaoCode1 = "UKLL";
    static const std::string icaoCode2 = "NZSP";

    metafsimple::Station refStation;
    refStation.icaoCode = icaoCode1;

    metafsimple::Report refReportWarning;
    refReportWarning.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::INCONSISTENT_DATA,
            ""});

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setLocation(icaoCode1);

    EXPECT_EQ(report, metafsimple::Report());
    EXPECT_EQ(station, refStation);

    mda.setLocation(icaoCode2);

    EXPECT_EQ(report, refReportWarning);
    EXPECT_EQ(station, refStation);
}

TEST(MetadataAdapter, setAttributes_metar_nil) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::METAR;
    refReport.missing = true;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::METAR, false);
    mda.setAttributes(true,
                      false,
                      false,
                      false,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_taf_nil) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::TAF;
    refReport.missing = true;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::TAF, false);
    mda.setAttributes(true,
                      false,
                      false,
                      false,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_taf_cnl) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::TAF;
    refReport.cancelled = true;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::TAF, false);
    mda.setAttributes(false,
                      true,
                      false,
                      false,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_metar_cor) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::METAR;
    refReport.correctional = true;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::METAR, false);
    mda.setAttributes(false,
                      false,
                      true,
                      false,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_metar_corNum) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::METAR;
    refReport.correctional = true;
    refReport.correctionNumber = 2;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::METAR, false);
    mda.setAttributes(false,
                      false,
                      true,
                      false,
                      false,
                      false,
                      false,
                      2);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_taf_cor) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::TAF;
    refReport.correctional = true;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::TAF, false);
    mda.setAttributes(false,
                      false,
                      true,
                      false,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_taf_amd) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::TAF;
    refReport.amended = true;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::TAF, false);
    mda.setAttributes(false,
                      false,
                      false,
                      true,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_metar_auto) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::METAR;
    refReport.automated = true;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::METAR, false);
    mda.setAttributes(false,
                      false,
                      false,
                      false,
                      true,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_nospeci) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::METAR;

    metafsimple::Station refStation;
    refStation.noSpeciReports = true;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::METAR, false);
    mda.setAttributes(false,
                      false,
                      false,
                      false,
                      false,
                      true,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, refStation);
}

TEST(MetadataAdapter, setAttributes_maintenance) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::METAR;

    metafsimple::Station refStation;
    refStation.requiresMaintenance = true;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::METAR, false);
    mda.setAttributes(false,
                      false,
                      false,
                      false,
                      false,
                      false,
                      true,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, refStation);
}

TEST(MetadataAdapter, setAttributes_none) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::METAR;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::METAR, false);
    mda.setAttributes(false,
                      false,
                      false,
                      false,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_error) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::ERROR;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    report.type = metafsimple::Report::Type::ERROR;
    mda.setAttributes(false,
                      false,
                      true,
                      false,
                      true,
                      true,
                      true,
                      1);

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    mda.setAttributes(false,
                      false,
                      false,
                      true,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    mda.setAttributes(true,
                      false,
                      false,
                      false,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    mda.setAttributes(false,
                      true,
                      false,
                      false,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    mda.setAttributes(false,
                      false,
                      false,
                      true,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_nil_cnl) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::TAF;
    refReport.missing = true;
    refReport.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::BOTH_NIL_AND_CNL, ""});

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::TAF, false);
    mda.setAttributes(true,
                      true,
                      false,
                      false,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_amd_cor) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::TAF;
    refReport.correctional = true;
    refReport.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::BOTH_AMD_AND_COR, ""});

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportType(metaf::ReportType::TAF, false);
    mda.setAttributes(false,
                      false,
                      true,
                      true,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_amd_metar) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::METAR;
    refReport.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::AMD_IN_NON_TAF, ""});

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportType(metaf::ReportType::METAR, false);
    mda.setAttributes(false,
                      false,
                      false,
                      true,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_amd_speci) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::SPECI;
    refReport.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::AMD_IN_NON_TAF, ""});

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportType(metaf::ReportType::METAR, true);
    mda.setAttributes(false,
                      false,
                      false,
                      true,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_cnl_metar) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::METAR;
    refReport.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::CNL_IN_NON_TAF, ""});

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportType(metaf::ReportType::METAR, false);
    mda.setAttributes(false,
                      true,
                      false,
                      false,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAttributes_cnl_speci) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::SPECI;
    refReport.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::CNL_IN_NON_TAF, ""});

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportType(metaf::ReportType::METAR, true);
    mda.setAttributes(false,
                      true,
                      false,
                      false,
                      false,
                      false,
                      false,
                      std::optional<unsigned int>());

    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAutoType_AO1) {
    metafsimple::Station refStation;
    refStation.autoType = metafsimple::Station::AutoType::AO1;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setAutoType(true, false, false, false);
    EXPECT_EQ(report, metafsimple::Report());
    EXPECT_EQ(station, refStation);
}

TEST(MetadataAdapter, setAutoType_AO2) {
    metafsimple::Station refStation;
    refStation.autoType = metafsimple::Station::AutoType::AO2;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setAutoType(false, true, false, false);
    EXPECT_EQ(report, metafsimple::Report());
    EXPECT_EQ(station, refStation);
}

TEST(MetadataAdapter, setAutoType_AO1A) {
    metafsimple::Station refStation;
    refStation.autoType = metafsimple::Station::AutoType::AO1A;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setAutoType(false, false, true, false);
    EXPECT_EQ(report, metafsimple::Report());
    EXPECT_EQ(station, refStation);
}

TEST(MetadataAdapter, setAutoType_AO2A) {
    metafsimple::Station refStation;
    refStation.autoType = metafsimple::Station::AutoType::AO2A;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setAutoType(false, false, false, true);
    EXPECT_EQ(report, metafsimple::Report());
    EXPECT_EQ(station, refStation);
}

TEST(MetadataAdapter, setAutoType_none) {
    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    report = metafsimple::Report();
    mda.setAutoType(false, false, false, false);
    EXPECT_EQ(report, metafsimple::Report());
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setAutoType_invalid) {
    metafsimple::Report refReport;
    refReport.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::INVALID_AUTOTYPE, ""});

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    report = metafsimple::Report();
    mda.setAutoType(true, true, false, false);
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setAutoType(true, false, true, false);
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setAutoType(true, false, false, true);
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setAutoType(false, true, true, false);
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setAutoType(false, true, false, true);
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setAutoType(false, false, true, true);
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setAutoType(false, true, true, true);
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setAutoType(true, false, true, true);
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setAutoType(true, true, false, true);
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setAutoType(true, true, true, false);
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setAutoType(true, true, true, true);
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setReportTime) {
    metafsimple::Report refReport;
    refReport.reportTime = metafsimple::Time{16, 19, 30};

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    mda.setReportTime(metaf::MetafTime(16, 19, 30));
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setReportTime_metar_no_report_time) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::METAR;
    refReport.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::
                NO_REPORT_TIME_IN_METAR,
            ""});

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::METAR, false);
    mda.setReportTime(std::optional<metaf::MetafTime>());
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setReportTime_speci_no_report_time) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::SPECI;
    refReport.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::
                NO_REPORT_TIME_IN_METAR,
            ""});

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::METAR, true);
    mda.setReportTime(std::optional<metaf::MetafTime>());
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setApplicableTime_taf) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::TAF;
    refReport.applicableFrom = metafsimple::Time{16, 14, 00};
    refReport.applicableUntil = metafsimple::Time{17, 02, 00};

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::TAF, false);
    mda.setApplicableTime(metaf::MetafTime(16, 14, 00),
                          metaf::MetafTime(17, 02, 00));
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setApplicableTime_taf_error) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::TAF;
    refReport.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::NO_APPLICABLE_TIME_IN_TAF,
            ""});

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    report = metafsimple::Report();
    mda.setReportType(metaf::ReportType::TAF, false);
    mda.setApplicableTime(metaf::MetafTime(16, 14, 00),
                          std::optional<metaf::MetafTime>());
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setReportType(metaf::ReportType::TAF, false);
    mda.setApplicableTime(metaf::MetafTime(16, 14, 00),
                          std::optional<metaf::MetafTime>());
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setReportType(metaf::ReportType::TAF, false);
    mda.setApplicableTime(std::optional<metaf::MetafTime>(),
                          metaf::MetafTime(17, 02, 00));
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setReportType(metaf::ReportType::TAF, false);
    mda.setApplicableTime(std::optional<metaf::MetafTime>(),
                          metaf::MetafTime(17, 02, 00));
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setReportType(metaf::ReportType::TAF, false);
    mda.setApplicableTime(std::optional<metaf::MetafTime>(),
                          std::optional<metaf::MetafTime>());
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setApplicableTime_metar) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::METAR;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::METAR, false);
    mda.setApplicableTime(std::optional<metaf::MetafTime>(),
                          std::optional<metaf::MetafTime>());
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}

TEST(MetadataAdapter, setApplicableTime_speci) {
    metafsimple::Report refReport;
    refReport.type = metafsimple::Report::Type::SPECI;

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);
    mda.setReportType(metaf::ReportType::METAR, true);
    mda.setApplicableTime(std::optional<metaf::MetafTime>(),
                          std::optional<metaf::MetafTime>());
    EXPECT_EQ(report, refReport);
    EXPECT_EQ(station, metafsimple::Station());
}



TEST(MetadataAdapter, setApplicableTime_metar_error) {
    metafsimple::Report refReportMetar;
    refReportMetar.type = metafsimple::Report::Type::METAR;
    refReportMetar.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::APPLICABLE_TIME_IN_METAR,
            ""});

    metafsimple::Report refReportSpeci;
    refReportSpeci.type = metafsimple::Report::Type::SPECI;
    refReportSpeci.warnings.push_back(
        metafsimple::Report::Warning{
            metafsimple::Report::Warning::Message::APPLICABLE_TIME_IN_METAR,
            ""});

    metafsimple::Report report;
    metafsimple::Station station;
    metafsimple::detail::WarningLogger wl(report.warnings);
    metafsimple::detail::MetadataAdapter mda(report, station, &wl);

    report = metafsimple::Report();
    mda.setReportType(metaf::ReportType::METAR, false);
    mda.setApplicableTime(metaf::MetafTime(16, 14, 00),
                          std::optional<metaf::MetafTime>());
    EXPECT_EQ(report, refReportMetar);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setReportType(metaf::ReportType::METAR, true);
    mda.setApplicableTime(metaf::MetafTime(16, 14, 00),
                          std::optional<metaf::MetafTime>());
    EXPECT_EQ(report, refReportSpeci);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setReportType(metaf::ReportType::METAR, false);
    mda.setApplicableTime(std::optional<metaf::MetafTime>(),
                          metaf::MetafTime(17, 02, 00));
    EXPECT_EQ(report, refReportMetar);
    EXPECT_EQ(station, metafsimple::Station());

    report = metafsimple::Report();
    mda.setReportType(metaf::ReportType::METAR, true);
    mda.setApplicableTime(std::optional<metaf::MetafTime>(),
                          metaf::MetafTime(17, 02, 00));
    EXPECT_EQ(report, refReportSpeci);
    EXPECT_EQ(station, metafsimple::Station());
}

