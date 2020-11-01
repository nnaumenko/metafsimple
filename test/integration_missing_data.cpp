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
// Reports indicating missing data: wind, precipitation, rvr, etc.
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationMissingData, wndMisg) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK WND MISG=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::WND_MISG);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, visMisg) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK VIS MISG=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::VIS_MISG);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, rvrMisg) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK RVR MISG=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::RVR_MISG);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, cldMisg) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK CLD MISG=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::CLD_MISG);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, wxMisg) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK WX MISG=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::WX_MISG);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, tMisg) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK T MISG=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::T_MISG);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, tdMisg) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK TD MISG=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::TD_MISG);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, presMisg) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK PRES MISG=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::PRES_MISG);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, icgMisg) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK ICG MISG=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::ICG_MISG);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, pcpnMisg) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK PCPN MISG=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::PCPN_MISG);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, rvrno) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK RVRNO=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::RVRNO);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, pwino) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK PWINO=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::PWINO);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, tsno) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK TSNO=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::TSNO);
    EXPECT_EQ(result.station, refStation);
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, pno) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK PNO=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::PNO);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, fzrano) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK FZRANO=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::FZRANO);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, slpno) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK SLPNO=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::SLPNO);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, tsLtngTempoUnavbl) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK TS/LTNG TEMPO UNAVBL=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::TS_LTNG_TEMPO_UNAVBL);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}

TEST(IntegrationMissingData, densityAltMisg) {
    static const auto rawReport =
        "METAR ZZZZ 302038Z /////KT //// RMK DENSITY ALT MISG=";
    //fake report created for this test

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time{30, 20, 38};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "ZZZZ";
    refStation.missingData.insert(Station::MissingData::DENSITY_ALT_MISG);
    EXPECT_EQ(result.station, refStation);

    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.current, Current());
    EXPECT_EQ(result.forecast, Forecast());    
}