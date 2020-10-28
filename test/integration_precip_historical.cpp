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

TEST(IntegrationPrecipitationHistorical, precipitationFrozen3h) {
    
}

TEST(IntegrationPrecipitationHistorical, precipitationFrozen6h) {
    
}

TEST(IntegrationPrecipitationHistorical, precipitationFrozen24h) {
    
}

TEST(IntegrationPrecipitationHistorical, snow6h) {
    
}

TEST(IntegrationPrecipitationHistorical, snincr) {
    
}

TEST(IntegrationPrecipitationHistorical, icing1h) {
    
}

TEST(IntegrationPrecipitationHistorical, icing3h) {
    
}

TEST(IntegrationPrecipitationHistorical, icing6h) {
    
}

