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

TEST(AerodromeDataAdapter, runwayDeposits) {
    metafsimple::Aerodrome aerodrome;
    std::vector<metafsimple::Report::Warning> warnings;
    metafsimple::detail::WarningLogger wl(warnings);
    metafsimple::detail::AerodromeDataAdapter ada(aerodrome, &wl);

    ada.setRunwayState(
        metaf::Runway::fromString("R01").value(),
        metaf::RunwayStateGroup::Deposits::CLEAR_AND_DRY,
        metaf::RunwayStateGroup::Extent::NOT_REPORTED,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R02").value(),
        metaf::RunwayStateGroup::Deposits::DAMP,
        metaf::RunwayStateGroup::Extent::NOT_REPORTED,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R03").value(),
        metaf::RunwayStateGroup::Deposits::WET_AND_WATER_PATCHES,
        metaf::RunwayStateGroup::Extent::NOT_REPORTED,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R04").value(),
        metaf::RunwayStateGroup::Deposits::RIME_AND_FROST_COVERED,
        metaf::RunwayStateGroup::Extent::NOT_REPORTED,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R05").value(),
        metaf::RunwayStateGroup::Deposits::DRY_SNOW,
        metaf::RunwayStateGroup::Extent::NOT_REPORTED,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R06").value(),
        metaf::RunwayStateGroup::Deposits::WET_SNOW,
        metaf::RunwayStateGroup::Extent::NOT_REPORTED,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R07").value(),
        metaf::RunwayStateGroup::Deposits::SLUSH,
        metaf::RunwayStateGroup::Extent::NOT_REPORTED,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R08").value(),
        metaf::RunwayStateGroup::Deposits::ICE,
        metaf::RunwayStateGroup::Extent::NOT_REPORTED,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R09").value(),
        metaf::RunwayStateGroup::Deposits::COMPACTED_OR_ROLLED_SNOW,
        metaf::RunwayStateGroup::Extent::NOT_REPORTED,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R10").value(),
        metaf::RunwayStateGroup::Deposits::FROZEN_RUTS_OR_RIDGES,
        metaf::RunwayStateGroup::Extent::NOT_REPORTED,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R11").value(),
        metaf::RunwayStateGroup::Deposits::NOT_REPORTED,
        metaf::RunwayStateGroup::Extent::NOT_REPORTED,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );

    EXPECT_TRUE(warnings.empty());

    EXPECT_EQ(aerodrome.runways.at(0).deposits, 
        metafsimple::Aerodrome::RunwayDeposits::CLEAR_AND_DRY);
    EXPECT_EQ(aerodrome.runways.at(1).deposits, 
        metafsimple::Aerodrome::RunwayDeposits::DAMP);
    EXPECT_EQ(aerodrome.runways.at(2).deposits, 
        metafsimple::Aerodrome::RunwayDeposits::WET_AND_WATER_PATCHES);
    EXPECT_EQ(aerodrome.runways.at(3).deposits, 
        metafsimple::Aerodrome::RunwayDeposits::RIME_AND_FROST_COVERED);
    EXPECT_EQ(aerodrome.runways.at(4).deposits, 
        metafsimple::Aerodrome::RunwayDeposits::DRY_SNOW);
    EXPECT_EQ(aerodrome.runways.at(5).deposits, 
        metafsimple::Aerodrome::RunwayDeposits::WET_SNOW);
    EXPECT_EQ(aerodrome.runways.at(6).deposits, 
        metafsimple::Aerodrome::RunwayDeposits::SLUSH);
    EXPECT_EQ(aerodrome.runways.at(7).deposits, 
        metafsimple::Aerodrome::RunwayDeposits::ICE);
    EXPECT_EQ(aerodrome.runways.at(8).deposits, 
        metafsimple::Aerodrome::RunwayDeposits::COMPACTED_OR_ROLLED_SNOW);
    EXPECT_EQ(aerodrome.runways.at(9).deposits, 
        metafsimple::Aerodrome::RunwayDeposits::FROZEN_RUTS_OR_RIDGES);
    EXPECT_EQ(aerodrome.runways.at(10).deposits, 
        metafsimple::Aerodrome::RunwayDeposits::UNKNOWN);
}

TEST(AerodromeDataAdapter, runwayExtent) {
    metafsimple::Aerodrome aerodrome;
    std::vector<metafsimple::Report::Warning> warnings;
    metafsimple::detail::WarningLogger wl(warnings);
    metafsimple::detail::AerodromeDataAdapter ada(aerodrome, &wl);

    ada.setRunwayState(
        metaf::Runway::fromString("R01").value(),
        metaf::RunwayStateGroup::Deposits::NOT_REPORTED,
        metaf::RunwayStateGroup::Extent::LESS_THAN_10_PERCENT,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R02").value(),
        metaf::RunwayStateGroup::Deposits::NOT_REPORTED,
        metaf::RunwayStateGroup::Extent::FROM_11_TO_25_PERCENT,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R03").value(),
        metaf::RunwayStateGroup::Deposits::NOT_REPORTED,
        metaf::RunwayStateGroup::Extent::FROM_26_TO_50_PERCENT,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R04").value(),
        metaf::RunwayStateGroup::Deposits::NOT_REPORTED,
        metaf::RunwayStateGroup::Extent::MORE_THAN_51_PERCENT,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R05").value(),
        metaf::RunwayStateGroup::Deposits::NOT_REPORTED,
        metaf::RunwayStateGroup::Extent::NOT_REPORTED,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );

    EXPECT_TRUE(warnings.empty());

    EXPECT_EQ(aerodrome.runways.at(0).contaminationExtent, 
        metafsimple::Aerodrome::RunwayContamExtent::LESS_THAN_11_PERCENT);
    EXPECT_EQ(aerodrome.runways.at(1).contaminationExtent, 
        metafsimple::Aerodrome::RunwayContamExtent::FROM_11_TO_25_PERCENT);
    EXPECT_EQ(aerodrome.runways.at(2).contaminationExtent, 
        metafsimple::Aerodrome::RunwayContamExtent::FROM_26_TO_50_PERCENT);
    EXPECT_EQ(aerodrome.runways.at(3).contaminationExtent, 
        metafsimple::Aerodrome::RunwayContamExtent::MORE_THAN_50_PERCENT);
    EXPECT_EQ(aerodrome.runways.at(4).contaminationExtent, 
        metafsimple::Aerodrome::RunwayContamExtent::UNKNOWN);
}

TEST(AerodromeDataAdapter, runwayExtentReservedValues) {
    metafsimple::Aerodrome aerodrome;
    std::vector<metafsimple::Report::Warning> warnings;
    metafsimple::detail::WarningLogger wl(warnings);
    metafsimple::detail::AerodromeDataAdapter ada(aerodrome, &wl);

    ada.setRunwayState(
        metaf::Runway::fromString("R01").value(),
        metaf::RunwayStateGroup::Deposits::NOT_REPORTED,
        metaf::RunwayStateGroup::Extent::RESERVED_3,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R02").value(),
        metaf::RunwayStateGroup::Deposits::NOT_REPORTED,
        metaf::RunwayStateGroup::Extent::RESERVED_4,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R03").value(),
        metaf::RunwayStateGroup::Deposits::NOT_REPORTED,
        metaf::RunwayStateGroup::Extent::RESERVED_6,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R04").value(),
        metaf::RunwayStateGroup::Deposits::NOT_REPORTED,
        metaf::RunwayStateGroup::Extent::RESERVED_7,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );
    ada.setRunwayState(
        metaf::Runway::fromString("R05").value(),
        metaf::RunwayStateGroup::Deposits::NOT_REPORTED,
        metaf::RunwayStateGroup::Extent::RESERVED_8,
        metaf::Precipitation(),
        metaf::SurfaceFriction()
    );

    EXPECT_TRUE(warnings.empty());

    EXPECT_EQ(aerodrome.runways.at(0).contaminationExtent, 
        metafsimple::Aerodrome::RunwayContamExtent::UNKNOWN);
    EXPECT_EQ(aerodrome.runways.at(1).contaminationExtent, 
        metafsimple::Aerodrome::RunwayContamExtent::UNKNOWN);
    EXPECT_EQ(aerodrome.runways.at(2).contaminationExtent, 
        metafsimple::Aerodrome::RunwayContamExtent::UNKNOWN);
    EXPECT_EQ(aerodrome.runways.at(3).contaminationExtent, 
        metafsimple::Aerodrome::RunwayContamExtent::UNKNOWN);
    EXPECT_EQ(aerodrome.runways.at(4).contaminationExtent, 
        metafsimple::Aerodrome::RunwayContamExtent::UNKNOWN);
}
