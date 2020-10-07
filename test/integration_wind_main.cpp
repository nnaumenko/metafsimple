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
// Basic METAR report with various wind groups: calm wind, wind speed measured
// in meters per second, variable wind direction, variable wind sector,
// wind with gusts
// Purpose: to confirm on realistic reports where possible, that the wind groups
// are processed correctly
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationWind, calmWind) {
    static const auto rawReport =
        "METAR EPZG 252000Z 00000KT CAVOK 18/18 Q1013=";  // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{25, 20, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPZG";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windCalm = true;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.weatherData.seaLevelPressure = Pressure{1013, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{18, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{18, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationWind, variableWindSector) {
    static const auto rawReport =
        "METAR EPRZ 251500Z 01006KT 330V050 CAVOK 26/14 Q1012=";  // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{25, 15, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPRZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 10;
    refCurrent.weatherData.windSpeed = Speed{6, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 330;
    refCurrent.weatherData.windDirectionVarToDegrees = 50;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1012, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{26, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{14, Temperature::Unit::C};
    refCurrent.relativeHumidity = 47;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationWind, variableWindDirection) {
    static const auto rawReport =
        "METAR EPRZ 251600Z VRB03KT CAVOK 26/14 Q1012=";  // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{25, 16, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPRZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionVariable = true;
    refCurrent.weatherData.windSpeed = Speed{3, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1012, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{26, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{14, Temperature::Unit::C};
    refCurrent.relativeHumidity = 47;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationWind, windGusts) {
    static const auto rawReport =
        "METAR EPGD 211330Z 29019G29KT CAVOK 19/08 Q1017=";  // 21 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{21, 13, 30};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPGD";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 290;
    refCurrent.weatherData.windSpeed = Speed{19, Speed::Unit::KT};
    refCurrent.weatherData.gustSpeed = Speed{29, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1017, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{19, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{8, Temperature::Unit::C};
    refCurrent.relativeHumidity = 48;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationWind, windGustsVariableSector) {
    static const auto rawReport =
        "METAR EPZG 241400Z 25007G18KT 180V300 CAVOK 28/08 Q1008=";
    // 24 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{24, 14, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPZG";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 250;
    refCurrent.weatherData.windSpeed = Speed{7, Speed::Unit::KT};
    refCurrent.weatherData.gustSpeed = Speed{18, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 180;
    refCurrent.weatherData.windDirectionVarToDegrees = 300;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1008, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{28, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{8, Temperature::Unit::C};
    refCurrent.relativeHumidity = 28;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationWind, windInMps) {
    static const auto rawReport =
        "METAR UKLI 230600Z 19001MPS CAVOK 16/14 Q1017 NOSIG=";  // 23 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{23, 6, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "UKLI";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 190;
    refCurrent.weatherData.windSpeed = Speed{1, Speed::Unit::MPS};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1017, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{16, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{14, Temperature::Unit::C};
    refCurrent.relativeHumidity = 87;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());

    Forecast refForecast;
    refForecast.noSignificantChanges = true;
    EXPECT_EQ(result.forecast, refForecast);
}

TEST(IntegrationWind, windNotReported) {
    static const auto rawReport =
        "LIPF 280555Z /////KT CAVOK 21/19 Q1016=";  // 28 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{28, 5, 55};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "LIPF";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1016, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{21, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{19, Temperature::Unit::C};
    refCurrent.relativeHumidity = 88;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationWind, windDirectionNotReported) {
    static const auto rawReport =
        "LIBY 271755Z ///15KT CAVOK 29/14 Q1014"
        " RMK SKC QUK 3 QUL 1 N VIS MAR 20 KM VIS MIN 9999=";  // 27 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{27, 17, 55};
    refReport.error = Report::Error::NO_ERROR;
    refReport.plainText.push_back(
        "SKC QUK 3 QUL 1 N VIS MAR 20 KM VIS MIN 9999");
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "LIBY";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windSpeed = Speed{15, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1014, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{29, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{14, Temperature::Unit::C};
    refCurrent.relativeHumidity = 39;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationWind, variableWindSectorOnly) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 330V050 CAVOK 30/30 Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionVarFromDegrees = 330;
    refCurrent.weatherData.windDirectionVarToDegrees = 50;
    refCurrent.weatherData.visibility =
        Distance{Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    refCurrent.airTemperature = Temperature{30, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{30, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

////////////////////////////////////////////////////////////////////////////////
// Testing for duplicate and inconsistent wind groups without direction sector
// Purpose: to confirm that reports with errors such as wind group repeated
// twice, two different wind groups, etc. are processed as per spec
////////////////////////////////////////////////////////////////////////////////

// The wind group repeated twice: no warning, duplicate group is ignored
TEST(IntegrationWind, duplicateWindGroup) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27008KT 27008KT Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 270;
    refCurrent.weatherData.windSpeed = Speed{8, Speed::Unit::KT};
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// The wind group with gust speed repeated twice: no warning, duplicate group
// is ignored
TEST(IntegrationWind, duplicateWindGroupGusts) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27012G15KT 27012G15KT Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 270;
    refCurrent.weatherData.windSpeed = Speed{12, Speed::Unit::KT};
    refCurrent.weatherData.gustSpeed = Speed{15, Speed::Unit::KT};
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// Two different wind groups, inconsistent wind data: warning is given and
// no wind data included on the report
TEST(IntegrationWind, twoWindGroups) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27008KT 31010KT Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(
        Report::Warning{Report::Warning::Message::DUPLICATED_DATA, "31010KT"});
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// This test is similar to previous one, except the second group reports
// variable wind direction
TEST(IntegrationWind, twoWindGroupsNormalVrb) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27008KT VRB08KT Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(
        Report::Warning{Report::Warning::Message::DUPLICATED_DATA, "VRB08KT"});
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// This test is similar to previous one, only group order is changed
TEST(IntegrationWind, twoWindGroupsVrbNormal) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z VRB08KT 27008KT Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(
        Report::Warning{Report::Warning::Message::DUPLICATED_DATA, "27008KT"});
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// Two wind groups with different gust speed, inconsistent wind data: warning
// is given and no wind data included on the report
TEST(IntegrationWind, twoWindGroupsGustSpeedDifferent) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27012G15KT 27012G16KT Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(
        Report::Warning{Report::Warning::Message::DUPLICATED_DATA,
                        "27012G16KT"});
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// Two inconsistent wind groups, the first group specifies variable wind, the
// second group specifies no wind
TEST(IntegrationWind, twoWindGroupsVrbCalm) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z VRB08KT 00000KT Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(
        Report::Warning{Report::Warning::Message::DUPLICATED_DATA, "00000KT"});
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// This test is similar to previous one, only group order is changed
TEST(IntegrationWind, twoWindGroupsCalmVrb) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 00000KT VRB08KT Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(
        Report::Warning{Report::Warning::Message::DUPLICATED_DATA, "VRB08KT"});
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// Two wind groups, the first group specifies variable wind, the second group
// specifies non-reported wind: no warning given
TEST(IntegrationWind, twoWindGroupsVrbNonReported) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z VRB08KT /////KT Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionVariable = true;
    refCurrent.weatherData.windSpeed = Speed{8, Speed::Unit::KT};
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// This test is similar to previous one, only group order is changed
TEST(IntegrationWind, twoWindGroupsNonReportedVrb) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z /////KT VRB08KT Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionVariable = true;
    refCurrent.weatherData.windSpeed = Speed{8, Speed::Unit::KT};
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

////////////////////////////////////////////////////////////////////////////////
// Testing for duplicate and inconsistent wind groups with variable direction
// sector & variable direction sector groups without main wind group
// Purpose: to confirm that reports with errors such as wind group repeated
// twice, two different wind groups, etc. are processed as per spec
////////////////////////////////////////////////////////////////////////////////

// A wind group followed by variable wind sector and the same wind group
// repeated without variable wind sector: no warning, duplicate group ignored
TEST(IntegrationWind, duplicateWindGroupWithVarSector) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27008KT 200V320 27008KT Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 270;
    refCurrent.weatherData.windDirectionVarFromDegrees = 200;
    refCurrent.weatherData.windDirectionVarFromDegrees = 200;
    refCurrent.weatherData.windDirectionVarToDegrees = 320;
    refCurrent.weatherData.windSpeed = Speed{8, Speed::Unit::KT};
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// Two different wind groups with variable wind sector group located before,
// between, and after wind groups, inconsistent wind data but correct variable
// wind sector data: warning is given and no wind data included on the report
// but variable wind sector data is included normally
TEST(IntegrationWind, twoWindGroupsWithVarSector) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27008KT 200V310 31010KT Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    static const auto rawReportAlt1 =
        "METAR ZZZZ 291704Z 27008KT 31010KT 200V310 Q1015=";
    // fake report created for this test
    const auto resultAlt1 = metafsimple::simplify(rawReportAlt1);
    ASSERT_EQ(resultAlt1.report.warnings.size(), 1u);
    EXPECT_EQ(resultAlt1.report.warnings[0].id, "31010KT 200V310");
    EXPECT_EQ(resultAlt1.station, result.station);
    EXPECT_EQ(resultAlt1.aerodrome, result.aerodrome);
    EXPECT_EQ(resultAlt1.current, result.current);
    EXPECT_EQ(resultAlt1.historical, result.historical);
    EXPECT_EQ(resultAlt1.forecast, result.forecast);
    // The result of processing of rawReport and rawReportAlt1 is almost the
    // same, just different group causes the warning
    // We reset group string in the Report's and compare them
    Report resultReportWithoutWarningId = result.report;
    ASSERT_EQ(resultReportWithoutWarningId.warnings.size(), 1u);
    resultReportWithoutWarningId.warnings[0].id = "";
    Report resultReportAlt1WithoutWarningId = resultAlt1.report;
    ASSERT_EQ(resultReportAlt1WithoutWarningId.warnings.size(), 1u);
    resultReportAlt1WithoutWarningId.warnings[0].id = "";
    EXPECT_EQ(resultReportWithoutWarningId, resultReportAlt1WithoutWarningId);

    static const auto rawReportAlt2 =
        "METAR ZZZZ 291704Z 200V310 27008KT 31010KT Q1015=";
    // fake report created for this test
    const auto resultAlt2 = metafsimple::simplify(rawReportAlt2);
    EXPECT_EQ(resultAlt2, result);

    static const auto rawReportAlt3 =
        "METAR ZZZZ 291704Z 200V310 27008KT Q1015 31010KT=";
    // fake report created for this test
    const auto resultAlt3 = metafsimple::simplify(rawReportAlt3);
    EXPECT_EQ(resultAlt3, result);

    static const auto rawReportAlt4 =
        "METAR ZZZZ 291704Z 27008KT 200V310 Q1015 31010KT=";
    // fake report created for this test
    const auto resultAlt4 = metafsimple::simplify(rawReportAlt4);
    EXPECT_EQ(resultAlt4, result);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(
        Report::Warning{Report::Warning::Message::DUPLICATED_DATA, "31010KT"});
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionVarFromDegrees = 200;
    refCurrent.weatherData.windDirectionVarToDegrees = 310;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// Two identical variable wind sector groups: no warnings, duplicate group
// is ignored
TEST(IntegrationWind, duplicateVariableWindSector) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27008KT 250V300 250V300 Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    static const auto rawReportAlt1 =
        "METAR ZZZZ 291704Z 250V300 27008KT 250V300 Q1015=";
    // fake report created for this test
    const auto resultAlt1 = metafsimple::simplify(rawReportAlt1);
    EXPECT_EQ(resultAlt1, result);

    static const auto rawReportAlt2 =
        "METAR ZZZZ 291704Z 250V300 27008KT 250V300 Q1015=";
    // fake report created for this test
    const auto resultAlt2 = metafsimple::simplify(rawReportAlt2);
    EXPECT_EQ(resultAlt2, result);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 270;
    refCurrent.weatherData.windSpeed = Speed{8, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 250;
    refCurrent.weatherData.windDirectionVarToDegrees = 300;
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// Two different variable wind sector groups, inconsistant wind sector data:
// warning is given and only wind direction and speed is included in the
// result, variable wind sector is ignored
TEST(IntegrationWind, twoVariableWindSectorGroups) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27008KT 250V300 210V360 Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(
        Report::Warning{Report::Warning::Message::DUPLICATED_DATA, "210V360"});
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 270;
    refCurrent.weatherData.windSpeed = Speed{8, Speed::Unit::KT};
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// This test is similar to previous one, only group order is different
TEST(IntegrationWind, twoVariableWindSectorsAroundWindData) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 210V360 27008KT 250V300 Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(
        Report::Warning{Report::Warning::Message::DUPLICATED_DATA,
                        "27008KT 250V300"});
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 270;
    refCurrent.weatherData.windSpeed = Speed{8, Speed::Unit::KT};
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

// A wind group with non-reported wind group: no warning, non-reported
// group ignored
TEST(IntegrationWind, twoWindGroupsNonReported) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27008KT /////KT Q1015=";
    // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    static const auto rawReportAlt =
        "METAR ZZZZ 291704Z /////KT 27008KT Q1015=";
    // fake report created for this test
    const auto resultAlt = metafsimple::simplify(rawReportAlt);
    EXPECT_EQ(resultAlt, result);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 270;
    refCurrent.weatherData.windSpeed = Speed{8, Speed::Unit::KT};
    refCurrent.weatherData.seaLevelPressure =
        Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}
