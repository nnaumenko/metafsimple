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
// Test for report-level data
// METAR/SPECI reports: METAR/SPECI report type, NIL, COR, correctional report 
// number, AUTO, automated station type (AO1, AO1A, AO2, AO2A), maintenance 
// indicator, NOSPECI
// TAF reports: TAF report type, NIL, CNL, COR, AMD
// Note: only report and station data is checked.
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationReportData, metarNil) {
    static const auto rawReport =
        "METAR UKLI 010130Z NIL=";  // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 1, 30};
    refReport.error = Report::Error::NO_ERROR;
    refReport.missing = true;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "UKLI";
    EXPECT_EQ(result.station, refStation);
}

TEST(IntegrationReportData, metarCor) {
    static const auto rawReport =
        "METAR COR UKLL 260230Z 24001MPS 6000 -SHRA SCT040CB BKN040 17/16"
        " Q1014 R31/CLRD// NOSIG=";  // 26 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 2, 30};
    refReport.error = Report::Error::NO_ERROR;
    refReport.correctional = true;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "UKLL";
    EXPECT_EQ(result.station, refStation);
}

TEST(IntegrationReportData, metarCorectionNumber) {
    static const auto rawReport =
        "SPECI CYEG 230506Z CCD 10009KT 20SM TS FEW045CB BKN100 BKN130"
        " 18/17 A2972"
        " RMK CB1AC6AS1 CB TR CBS MOVG NE FRQ LTGIC S VIRGA OVRHD";  
        // 23 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::SPECI;
    refReport.reportTime = Time{23, 5, 6};
    refReport.error = Report::Error::NO_ERROR;
    refReport.correctional = true;
    refReport.correctionNumber = 4;
    refReport.plainText.push_back("CB TR CBS MOVG NE");
    refReport.plainText.push_back("VIRGA OVRHD");
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "CYEG";
    EXPECT_EQ(result.station, refStation);
}

TEST(IntegrationReportData, metarAuto) {
    static const auto rawReport =
        "METAR LIVM 010955Z AUTO 04005KT //// 30/18 Q1013=";  // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 9, 55};
    refReport.error = Report::Error::NO_ERROR;
    refReport.automated = true;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "LIVM";
    EXPECT_EQ(result.station, refStation);
}

TEST(IntegrationReportData, metarAo1) {
    static const auto rawReport =
        "METAR KHZX 010855Z AUTO 00000KT 10SM SCT050 SCT065 OVC090 17/16 A2995"
        " RMK AO1"; // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 8, 55};
    refReport.error = Report::Error::NO_ERROR;
    refReport.automated = true;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KHZX";
    refStation.autoType = Station::AutoType::AO1;
    EXPECT_EQ(result.station, refStation);
}

TEST(IntegrationReportData, metarAo1a) {
    static const auto rawReport =
        "METAR KFFO 051658Z 30008KT 4SM -SN FEW014 OVC019 M05/M07 A2996"
        " RMK AO1A SLP159 P0000 T10471072"; // 5 FEB 2014

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{5, 16, 58};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KFFO";
    refStation.autoType = Station::AutoType::AO1A;
    EXPECT_EQ(result.station, refStation);
}

TEST(IntegrationReportData, metarAo2) {
    static const auto rawReport =
        "METAR KSBP 010929Z AUTO 30003KT 4SM BR SCT004 12/12 A2995"
        " RMK AO2 T01220117"; // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 9, 29};
    refReport.error = Report::Error::NO_ERROR;
    refReport.automated = true;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KSBP";
    refStation.autoType = Station::AutoType::AO2;
    EXPECT_EQ(result.station, refStation);
}

TEST(IntegrationReportData, metarAo2a) {
    static const auto rawReport =
        "KBKF 010858Z 19006KT 10SM CLR 15/09 A3029"
        " RMK AO2A SLP180 T01500089 57013"; // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 8, 58};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "KBKF";
    refStation.autoType = Station::AutoType::AO2A;
    EXPECT_EQ(result.station, refStation);
}

TEST(IntegrationReportData, metarMaintenanceIndicator) {
    static const auto rawReport =
        "METAR ETEB 011156Z AUTO 19006KT 9999 CLR 33/12 A2998"
        " RMK AO2 SLP134 T03290119 10330 20218 58009 $"; // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 11, 56};
    refReport.automated = true;
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ETEB";
    refStation.autoType = Station::AutoType::AO2;
    refStation.requiresMaintenance = true;
    EXPECT_EQ(result.station, refStation);
}

TEST(IntegrationReportData, metarNoSpeci) {
    static const auto rawReport =
        "METAR PAEC 010051Z 00000KT 20SM FEW030 BKN060 22/06 A2980"
        " RMK NOSPECI="; // 1 AUG 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 0, 51};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "PAEC";
    refStation.noSpeciReports = true;
    EXPECT_EQ(result.station, refStation);
}

