/*
* Copyright (C) 2020 Nick Naumenko (https://gitlab.com/nnaumenko,
* https:://github.com/nnaumenko)
* All rights reserved.
* This software may be modified and distributed under the terms
* of the MIT license. See the LICENSE file for details.
*/

#include "gtest/gtest.h"
#include "metafsimple.hpp"
#include "comparisons.hpp"

using namespace metafsimple;

TEST(ParseSimplifyReport, basicMetar) {
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
                Speed(),  // gust speed
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