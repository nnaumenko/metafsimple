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
////////////////////////////////////////////////////////////////////////////////

TEST(ParseSimplifyReportWind, calmWind) {
    static const auto rawReport =
        "METAR EPZG 252000Z 00000KT CAVOK 18/18 Q1013="; // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {25, 20, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPZG";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windCalm = true;
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{18, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{18, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.pressureSeaLevel = Pressure{1013, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, variableWindSector) {
    static const auto rawReport =
        "METAR EPRZ 251500Z 01006KT 330V050 CAVOK 26/14 Q1012="; // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {25, 15, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPRZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 10;
    refCurrent.weatherData.windSpeed = Speed {6, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 330;
    refCurrent.weatherData.windDirectionVarToDegrees = 50;
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{26, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{14, Temperature::Unit::C};
    refCurrent.relativeHumidity = 47;
    refCurrent.pressureSeaLevel = Pressure{1012, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, variableWindDirection) {
    static const auto rawReport =
        "METAR EPRZ 251600Z VRB03KT CAVOK 26/14 Q1012="; // 25 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {25, 16, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPRZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionVariable = true;
    refCurrent.weatherData.windSpeed = Speed {3, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{26, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{14, Temperature::Unit::C};
    refCurrent.relativeHumidity = 47;
    refCurrent.pressureSeaLevel = Pressure{1012, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, windGusts) {
    static const auto rawReport =
        "METAR EPGD 211330Z 29019G29KT CAVOK 19/08 Q1017="; // 21 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {21, 13, 30};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPGD";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 290;
    refCurrent.weatherData.windSpeed = Speed {19, Speed::Unit::KT};
    refCurrent.weatherData.gustSpeed = Speed {29, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{19, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{8, Temperature::Unit::C};
    refCurrent.relativeHumidity = 48;
    refCurrent.pressureSeaLevel = Pressure{1017, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, windGustsVariableSector) {
    static const auto rawReport =
        "METAR EPZG 241400Z 25007G18KT 180V300 CAVOK 28/08 Q1008="; 
        // 24 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {24, 14, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "EPZG";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 250;
    refCurrent.weatherData.windSpeed = Speed {7, Speed::Unit::KT};
    refCurrent.weatherData.gustSpeed = Speed {18, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 180;
    refCurrent.weatherData.windDirectionVarToDegrees = 300;
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{28, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{8, Temperature::Unit::C};
    refCurrent.relativeHumidity = 28;
    refCurrent.pressureSeaLevel = Pressure{1008, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, windInMps) {
    static const auto rawReport =
        "METAR UKLI 230600Z 19001MPS CAVOK 16/14 Q1017 NOSIG="; // 23 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {23, 6, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "UKLI";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 190;
    refCurrent.weatherData.windSpeed = Speed {1, Speed::Unit::MPS};
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{16, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{14, Temperature::Unit::C};
    refCurrent.relativeHumidity = 87;
    refCurrent.pressureSeaLevel = Pressure{1017, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());

    Forecast refForecast;
    refForecast.noSignificantChanges = true;
    EXPECT_EQ(result.forecast, refForecast);
}

TEST(ParseSimplifyReportWind, windNotReported) {
    static const auto rawReport =
        "LIPF 280555Z /////KT CAVOK 21/19 Q1016="; // 28 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {28, 5, 55};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "LIPF";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{21, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{19, Temperature::Unit::C};
    refCurrent.relativeHumidity = 88;
    refCurrent.pressureSeaLevel = Pressure{1016, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, windDirectionNotReported) {
    static const auto rawReport =
        "LIBY 271755Z ///15KT CAVOK 29/14 Q1014"
        " RMK SKC QUK 3 QUL 1 N VIS MAR 20 KM VIS MIN 9999="; // 27 JUL 2020

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {27, 17, 55};
    refReport.error = Report::Error::NO_ERROR;
    refReport.plainText.push_back(
        "SKC QUK 3 QUL 1 N VIS MAR 20 KM VIS MIN 9999");
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "LIBY";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windSpeed = Speed {15, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{29, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{14, Temperature::Unit::C};
    refCurrent.relativeHumidity = 39;
    refCurrent.pressureSeaLevel = Pressure{1014, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, variableWindSectorOnly) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 330V050 CAVOK 30/30 Q1015="; 
        // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionVarFromDegrees = 330;
    refCurrent.weatherData.windDirectionVarToDegrees = 50;
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{30, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{30, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.pressureSeaLevel = Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, duplicateWindGroup) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27008KT 27008KT CAVOK 30/30 Q1015="; 
        // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(
        Report::Warning {Report::Warning::Message::DUPLICATED_DATA, "27008KT"});
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 270;
    refCurrent.weatherData.windSpeed = Speed {8, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{30, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{30, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.pressureSeaLevel = Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, twoWindGroups) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27008KT 31010KT CAVOK 30/30 Q1015="; 
        // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(
        Report::Warning {Report::Warning::Message::DUPLICATED_DATA, "31010KT"});
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 270;
    refCurrent.weatherData.windSpeed = Speed {8, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{30, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{30, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.pressureSeaLevel = Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, duplicateVariableWindSector) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27008KT 250V300 250V300 CAVOK 30/30 Q1015="; 
        // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(
        Report::Warning {Report::Warning::Message::DUPLICATED_DATA, "250V300"});
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 270;
    refCurrent.weatherData.windSpeed = Speed {8, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 250;
    refCurrent.weatherData.windDirectionVarToDegrees = 300;
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{30, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{30, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.pressureSeaLevel = Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(ParseSimplifyReportWind, twoVariableWindSectorGroups) {
    static const auto rawReport =
        "METAR ZZZZ 291704Z 27008KT 250V300 210V360 CAVOK 30/30 Q1015="; 
        // fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {29, 17, 4};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(
        Report::Warning {Report::Warning::Message::DUPLICATED_DATA, "210V360"});
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 270;
    refCurrent.weatherData.windSpeed = Speed {8, Speed::Unit::KT};
    refCurrent.weatherData.windDirectionVarFromDegrees = 250;
    refCurrent.weatherData.windDirectionVarToDegrees = 300;
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{30, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{30, Temperature::Unit::C};
    refCurrent.relativeHumidity = 100;
    refCurrent.pressureSeaLevel = Pressure{1015, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}
