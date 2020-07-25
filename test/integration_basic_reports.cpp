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
// Basic METAR: CAVOK, no trends, no remarks
// Report type METAR, METAR release time, station ICAO code, wind data, CAVOK
// visibility, lack of clouds in current weather essential info, current
// temperature, dew point and humidity, current sea-level pressure
////////////////////////////////////////////////////////////////////////////////

TEST(IntegrationBasicReports, basicMetarFull) {
    static const auto rawReport =
        "METAR SCCH 061700Z 23007KT CAVOK 07/03 Q1016=";

    const auto result = metafsimple::simplify(rawReport);

    const metafsimple::Simple refResult = {
        Report{
            Report::Type::METAR,
            false,                    // missing
            false,                    // cancelled
            false,                    // correctional
            false,                    // amended
            false,                    // automated
            0,                        // correction #
            Time{6, 17, 0},           // report release time: D,H,M
            Time(),                   // report valid from: D,H,M
            Time(),                   // report valid to: D,H,M
            Report::Error::NO_ERROR,  // error
            {},                       // warnings
            {}                        // plain text
        },
        Station{
            "SCCH",                   // ICAO code for station
            Station::AutoType::NONE,  // auto type AO1, AO2...
            false,                    // requires maintenance
            false,                    // no speci reports
            false,                    // no dir variations
            {},                       // missing data
            {},                       // rws no ceiling data
            {},                       // rws no vis data
            {},                       // dirs no ceiling data
            {}                        // dirs with no vis data
        },
        Aerodrome(),  // no aerodrome data in report
        Current{
            Essentials{
                230,                        // wind direction, degrees
                false,                      // wind direction variable
                std::optional<int>(),       // variable wind direction from
                std::optional<int>(),       // variable wind direction to
                Speed{7, Speed::Unit::KT},  // wind speed
                Speed(),                    // gust speed
                false,                      // no wind
                Distance{
                    Distance::Details::MORE_THAN,
                    10000,
                    Distance::Unit::METERS},      // prevailing visibility
                true,                             // CAVOK
                Essentials::SkyCondition::CAVOK,  // sky condition
                {},                               // cloud layers
                Height(),                         // vertical visibility
                {}                                // weather phenomena
            },
            DistanceRange(),                       // variable visibility
            {},                                    // obscurations
            Current::LowCloudLayer::UNKNOWN,       // low clouds
            Current::MidCloudLayer::UNKNOWN,       // mid clouds
            Current::HighCloudLayer::UNKNOWN,      // high clouds
            Temperature{7, Temperature::Unit::C},  // ambient air temperature
            Temperature{3, Temperature::Unit::C},  // dew point
            75,                                    // relative humidity
            Pressure{1016, Pressure::Unit::HPA},   // sea-level pressure
            Pressure(),                            // actual pressure
            Temperature(),                         // sea surface temperature
            WaveHeight(),                          // wave height
            Precipitation(),                       // water equivalent of snow
            Precipitation(),                       // snow depth on ground
            false,                                 // snow increasing rapidly
            {},                                    // wind shear
            {},                                    // phenomena in vicinity
            {},                                    // lightning strikes
            Height(),                              // density altitude
            std::optional<int>(),                  // hailstone size
            false                                  // frost on instrument
        },
        Historical(),  // no historical data in report
        Forecast()     // no forecast in report
    };
    EXPECT_EQ(result, refResult);
}

TEST(IntegrationBasicReports, basicMetarShort) {
    static const auto rawReport =
        "METAR SCCH 061700Z 23007KT CAVOK 07/03 Q1016=";

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::METAR;
    refReport.reportTime = Time {6, 17, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "SCCH";
    EXPECT_EQ(result.station, refStation);

    Current refCurrent;
    refCurrent.weatherData.windDirectionDegrees = 230;
    refCurrent.weatherData.windSpeed = Speed {7, Speed::Unit::KT};
    refCurrent.weatherData.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refCurrent.weatherData.cavok = true;
    refCurrent.weatherData.skyCondition = Essentials::SkyCondition::CAVOK;
    refCurrent.airTemperature = Temperature{7, Temperature::Unit::C};
    refCurrent.dewPoint = Temperature{3, Temperature::Unit::C};
    refCurrent.relativeHumidity = 75;
    refCurrent.pressureSeaLevel = Pressure{1016, Pressure::Unit::HPA};
    EXPECT_EQ(result.current, refCurrent);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.forecast, Forecast());
}

////////////////////////////////////////////////////////////////////////////////
// Basic TAF: CAVOK, only one trend, no min/max temperature forecast, no remarks
// Report type TAF, release and applicable time, station ICAO code, prevailing 
// weather trend: wind data and CAVOK
////////////////////////////////////////////////////////////////////////////////

TEST(ParseSimplifyReport, basicTafFull) {
    static const auto rawReport =
        "TAF LICG 250500Z 2506/2515 24008KT CAVOK=";

    const auto result = metafsimple::simplify(rawReport);

    const metafsimple::Simple refResult = {
        Report{
            Report::Type::TAF,
            false,                    // missing
            false,                    // cancelled
            false,                    // correctional
            false,                    // amended
            false,                    // automated
            0,                        // correction #
            Time{25, 05, 0},          // report release time: D,H,M
            Time{25, 06, 0},          // report valid from: D,H,M
            Time{25, 15, 0},          // report valid to: D,H,M
            Report::Error::NO_ERROR,  // error
            {},                       // warnings
            {}                        // plain text
        },
        Station{
            "LICG",                   // ICAO code for station
            Station::AutoType::NONE,  // auto type AO1, AO2...
            false,                    // requires maintenance
            false,                    // no speci reports
            false,                    // no dir variations
            {},                       // missing data
            {},                       // rws no ceiling data
            {},                       // rws no vis data
            {},                       // dirs no ceiling data
            {}                        // dirs with no vis data
        },
        Aerodrome(),   // no aerodrome data in report
        Current(),     // no current weather data in report
        Historical(),  // no historical data in report
        Forecast{
            Essentials{
                240,                        // wind direction, degrees
                false,                      // wind direction variable
                std::optional<int>(),       // variable wind dir from
                std::optional<int>(),       // variable wind dir to
                Speed{8, Speed::Unit::KT},  // wind speed
                Speed(),                    // gust speed
                false,                      // no wind
                Distance{Distance::Details::MORE_THAN,
                         10000,
                         Distance::Unit::METERS},  // prevailing vis
                true,                              // CAVOK
                Essentials::SkyCondition::CAVOK,   // sky condition
                {},                                // cloud layers
                Height(),                          // vertical visibility
                {}                                 // weather phenomena
            },                                     // prevailing trend

            {},             // trends
            false,          // no significant changes (NOSIG)
            false,          // wind shear conditions (WSCONDS)
            Temperature(),  // min temperature
            Time(),         // min tempeprature expected at
            Temperature(),  // max temperature
            Time(),         // max tempeprature expected at
            {},             // icing forecast
            {},             // turbulence forecast
            Pressure()      // lowest forecast sea-level pressure
        }

    };
    EXPECT_EQ(result, refResult);
}

TEST(IntegrationBasicReports, basicTafShort) {
    static const auto rawReport =
        "TAF LICG 250500Z 2506/2515 24008KT CAVOK=";

    const auto result = metafsimple::simplify(rawReport);

    Report refReport;
    refReport.type = Report::Type::TAF;
    refReport.reportTime = Time {25, 5, 0};
    refReport.applicableFrom = Time {25, 6, 0};
    refReport.applicableUntil = Time {25, 15, 0};
    refReport.error = Report::Error::NO_ERROR;
    EXPECT_EQ(result.report, refReport);

    Station refStation;
    refStation.icaoCode = "LICG";
    EXPECT_EQ(result.station, refStation);

    Forecast refForecast;
    refForecast.prevailing.windDirectionDegrees = 240;
    refForecast.prevailing.windSpeed = Speed {8, Speed::Unit::KT};
    refForecast.prevailing.visibility =
        Distance{ Distance::Details::MORE_THAN, 10000, Distance::Unit::METERS};
    refForecast.prevailing.cavok = true;
    refForecast.prevailing.skyCondition = Essentials::SkyCondition::CAVOK;
    EXPECT_EQ(result.forecast, refForecast);

    EXPECT_EQ(result.aerodrome, Aerodrome());
    EXPECT_EQ(result.historical, Historical());
    EXPECT_EQ(result.current, Current());
}

