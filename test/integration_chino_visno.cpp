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
// Tests covering VISNO and CHINO indicators for cardinal direction or runway or
// with no details specified
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationVisno, direction) {
    static const auto rawReport =
        "METAR ZZZZ 141752Z /////KT ////SM RMK VISNO E=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{14, 17, 52};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.directionsNoVisData.insert(CardinalDirection::E);
    refStation.missingData.insert(Station::MissingData::VISNO_DIRECTION);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisno, runway) {
    static const auto rawReport =
        "METAR ZZZZ 141752Z /////KT ////SM RMK VISNO RWY32=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{14, 17, 52};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.runwaysNoVisData.insert(Runway{32, Runway::Designator::NONE});
    refStation.missingData.insert(Station::MissingData::VISNO_RUNWAY);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationVisno, noDetails) {
    static const auto rawReport =
        "METAR ZZZZ 141752Z /////KT ////SM RMK VISNO=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{14, 17, 52};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::VISNO);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationChino, direction) {
    static const auto rawReport =
        "METAR ZZZZ 141752Z /////KT ////SM RMK CHINO E=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{14, 17, 52};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.directionsNoCeilingData.insert(CardinalDirection::E);
    refStation.missingData.insert(Station::MissingData::CHINO_DIRECTION);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationChino, runway) {
    static const auto rawReport =
        "METAR ZZZZ 141752Z /////KT ////SM RMK CHINO RWY32=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{14, 17, 52};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.runwaysNoCeilingData.insert(Runway{32, Runway::Designator::NONE});
    refStation.missingData.insert(Station::MissingData::CHINO_RUNWAY);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

TEST(IntegrationChino, noDetails) {
    static const auto rawReport =
        "METAR ZZZZ 141752Z /////KT ////SM RMK CHINO=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{14, 17, 52};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::CHINO);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}
