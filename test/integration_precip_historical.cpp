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
// Tests for various historical precipitation groups specified in remarks
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationPrecipitationHistorical, precipitationTotal1h) {
    static const auto rawReport =
        "METAR ZZZZ 262116Z /////KT //// RMK P0018=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 21, 16};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.precipitationTotal1h = 
        Precipitation {18, Precipitation::Unit::HUNDREDTHS_IN};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationPrecipitationHistorical, precipitationFrozen3or6h) {
    static const auto rawReport =
        "METAR ZZZZ 261936Z /////KT //// RMK 60217=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 19, 36};
    refReport.error = Report::Error::NO_ERROR;
    refReport.warnings.push_back(Report::Warning {
        Report::Warning::Message::INVALID_TIME,
        "60217"
    });
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.precipitationFrozen3or6h = 
        Precipitation {217, Precipitation::Unit::HUNDREDTHS_IN};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());     
}

TEST(IntegrationPrecipitationHistorical, precipitationFrozen3h) {
    static const auto rawReport =
        "METAR ZZZZ 262056Z /////KT //// RMK 60217=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 20, 56};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.precipitationFrozen3h = 
        Precipitation {217, Precipitation::Unit::HUNDREDTHS_IN};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());     
}

TEST(IntegrationPrecipitationHistorical, precipitationFrozen6h) {
    static const auto rawReport =
        "METAR ZZZZ 261800Z /////KT //// RMK 60217=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{26, 18, 00};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.precipitationFrozen6h = 
        Precipitation {217, Precipitation::Unit::HUNDREDTHS_IN};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());     
}

TEST(IntegrationPrecipitationHistorical, precipitationFrozen24h) {
    static const auto rawReport =
        "METAR ZZZZ 011200Z /////KT //// RMK 70125=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 12, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.precipitationFrozen24h = 
        Precipitation {125, Precipitation::Unit::HUNDREDTHS_IN};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());     
}

TEST(IntegrationPrecipitationHistorical, snow6h) {
    static const auto rawReport =
        "METAR ZZZZ 011200Z /////KT //// RMK 931011=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 12, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.snow6h = 
        Precipitation {110, Precipitation::Unit::HUNDREDTHS_IN};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());     
}

TEST(IntegrationPrecipitationHistorical, snincr) {
    static const auto rawReport =
        "METAR ZZZZ 011200Z /////KT //// RMK SNINCR 4/12=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 12, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.snowIncreasingRapidly = true;
    EXPECT_EQ(result.current, refCurrent);

    Historical refHistorical;
    refHistorical.snowfallTotal = 
        Precipitation {12, Precipitation::Unit::IN};
    refHistorical.snowfallIncrease1h = 
        Precipitation {4, Precipitation::Unit::IN};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.forecast, Forecast());     
}

TEST(IntegrationPrecipitationHistorical, icing1h) {
    static const auto rawReport =
        "METAR ZZZZ 011200Z /////KT //// RMK I1024=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 12, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.icing1h = 
        Precipitation {24, Precipitation::Unit::HUNDREDTHS_IN};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());     
}

TEST(IntegrationPrecipitationHistorical, icing3h) {
    static const auto rawReport =
        "METAR ZZZZ 011200Z /////KT //// RMK I3024=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 12, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.icing3h = 
        Precipitation {24, Precipitation::Unit::HUNDREDTHS_IN};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());     
}

TEST(IntegrationPrecipitationHistorical, icing6h) {
    static const auto rawReport =
        "METAR ZZZZ 011200Z /////KT //// RMK I6024=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{1, 12, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    EXPECT_EQ(result.station, refStation);

    Historical refHistorical;
    refHistorical.icing6h = 
        Precipitation {24, Precipitation::Unit::HUNDREDTHS_IN};
    EXPECT_EQ(result.historical, refHistorical);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());     
}
