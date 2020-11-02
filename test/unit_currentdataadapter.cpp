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

TEST(CurrentDataAdapter, lowClouds) {
    metafsimple::Current result;
    std::vector<metafsimple::Report::Warning> warnings;
    metafsimple::detail::WarningLogger wl(warnings);
    metafsimple::detail::CurrentDataAdapter cda(result, &wl);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::CU_HU_CU_FR,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.lowCloudLayer,
              metafsimple::Current::LowCloudLayer::CU_HU_CU_FR);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::CU_MED_CU_CON,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.lowCloudLayer,
              metafsimple::Current::LowCloudLayer::CU_MED_CU_CON);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::CB_CAL,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.lowCloudLayer,
              metafsimple::Current::LowCloudLayer::CB_CAL);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::SC_CUGEN,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.lowCloudLayer,
              metafsimple::Current::LowCloudLayer::SC_CUGEN);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::SC_NON_CUGEN,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.lowCloudLayer,
              metafsimple::Current::LowCloudLayer::SC_NON_CUGEN);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::ST_NEB_ST_FR,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.lowCloudLayer,
              metafsimple::Current::LowCloudLayer::ST_NEB_ST_FR);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::ST_FR_CU_FR_PANNUS,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.lowCloudLayer,
              metafsimple::Current::LowCloudLayer::ST_FR_CU_FR_PANNUS);

    result = metafsimple::Current();
    cda.setClouds(
        metaf::LowMidHighCloudGroup::LowLayer::CU_SC_NON_CUGEN_DIFFERENT_LEVELS,
        metaf::LowMidHighCloudGroup::MidLayer::NONE,
        metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.lowCloudLayer,
              metafsimple::Current::LowCloudLayer::
                  CU_SC_NON_CUGEN_DIFFERENT_LEVELS);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::CB_CAP,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.lowCloudLayer,
              metafsimple::Current::LowCloudLayer::CB_CAP);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NOT_OBSERVABLE,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.lowCloudLayer,
              metafsimple::Current::LowCloudLayer::UNKNOWN);
}

TEST(CurrentDataAdapter, midClouds) {
    metafsimple::Current result;
    std::vector<metafsimple::Report::Warning> warnings;
    metafsimple::detail::WarningLogger wl(warnings);
    metafsimple::detail::CurrentDataAdapter cda(result, &wl);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::AS_TR,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.midCloudLayer,
              metafsimple::Current::MidCloudLayer::AS_TR);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::AS_OP_NS,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.midCloudLayer,
              metafsimple::Current::MidCloudLayer::AS_OP_NS);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::AC_TR,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.midCloudLayer,
              metafsimple::Current::MidCloudLayer::AC_TR);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::AC_TR_LEN_PATCHES,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.midCloudLayer,
              metafsimple::Current::MidCloudLayer::AC_TR_LEN_PATCHES);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::AC_TR_AC_OP_SPREADING,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.midCloudLayer,
              metafsimple::Current::MidCloudLayer::AC_TR_AC_OP_SPREADING);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::AC_CUGEN_AC_CBGEN,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.midCloudLayer,
              metafsimple::Current::MidCloudLayer::AC_CUGEN_AC_CBGEN);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::
                      AC_DU_AC_OP_AC_WITH_AS_OR_NS,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.midCloudLayer,
              metafsimple::Current::MidCloudLayer::
                  AC_DU_AC_OP_AC_WITH_AS_OR_NS);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::AC_CAS_AC_FLO,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.midCloudLayer,
              metafsimple::Current::MidCloudLayer::AC_CAS_AC_FLO);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::AC_OF_CHAOTIC_SKY,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.midCloudLayer,
              metafsimple::Current::MidCloudLayer::AC_OF_CHAOTIC_SKY);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::NOT_OBSERVABLE,
                  metaf::LowMidHighCloudGroup::HighLayer::NONE);
    EXPECT_EQ(result.midCloudLayer,
              metafsimple::Current::MidCloudLayer::UNKNOWN);
}

TEST(CurrentDataAdapter, highClouds) {
    metafsimple::Current result;
    std::vector<metafsimple::Report::Warning> warnings;
    metafsimple::detail::WarningLogger wl(warnings);
    metafsimple::detail::CurrentDataAdapter cda(result, &wl);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::CI_FIB_CI_UNC);
    EXPECT_EQ(result.highCloudLayer,
              metafsimple::Current::HighCloudLayer::CI_FIB_CI_UNC);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::CI_SPI_CI_CAS_CI_FLO);
    EXPECT_EQ(result.highCloudLayer,
              metafsimple::Current::HighCloudLayer::CI_SPI_CI_CAS_CI_FLO);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::CI_SPI_CBGEN);
    EXPECT_EQ(result.highCloudLayer,
              metafsimple::Current::HighCloudLayer::CI_SPI_CBGEN);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::
                  CI_FIB_CI_UNC_SPREADING);
    EXPECT_EQ(result.highCloudLayer,
              metafsimple::Current::HighCloudLayer::CI_FIB_CI_UNC_SPREADING);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::
                  CI_CS_LOW_ABOVE_HORIZON);
    EXPECT_EQ(result.highCloudLayer,
              metafsimple::Current::HighCloudLayer::CI_CS_LOW_ABOVE_HORIZON);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::
                  CI_CS_HIGH_ABOVE_HORIZON);
    EXPECT_EQ(result.highCloudLayer,
              metafsimple::Current::HighCloudLayer::CI_CS_HIGH_ABOVE_HORIZON);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::
                  CS_NEB_CS_FIB_COVERING_ENTIRE_SKY);
    EXPECT_EQ(result.highCloudLayer,
              metafsimple::Current::HighCloudLayer::
              CS_NEB_CS_FIB_COVERING_ENTIRE_SKY);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::CS);
    EXPECT_EQ(result.highCloudLayer,
              metafsimple::Current::HighCloudLayer::CS);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::CC);
    EXPECT_EQ(result.highCloudLayer,
              metafsimple::Current::HighCloudLayer::CC);

    result = metafsimple::Current();
    cda.setClouds(metaf::LowMidHighCloudGroup::LowLayer::NONE,
                  metaf::LowMidHighCloudGroup::MidLayer::NONE,
                  metaf::LowMidHighCloudGroup::HighLayer::NOT_OBSERVABLE);
    EXPECT_EQ(result.highCloudLayer,
              metafsimple::Current::HighCloudLayer::UNKNOWN);
}

TEST(CurrentDataAdapter, phenomenaInVicinity) {
    metafsimple::Current result;
    std::vector<metafsimple::Report::Warning> warnings;
    metafsimple::detail::WarningLogger wl(warnings);
    metafsimple::detail::CurrentDataAdapter cda(result, &wl);

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::THUNDERSTORM,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::CUMULONIMBUS,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::CUMULONIMBUS_MAMMATUS,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::TOWERING_CUMULUS,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    cda.addPhenomenaInVicinity(
        metaf::VicinityGroup::Type::ALTOCUMULUS_CASTELLANUS,
        metaf::Distance(),
        std::vector<metaf::Direction>{},
        metaf::Direction());

    cda.addPhenomenaInVicinity(
        metaf::VicinityGroup::Type::STRATOCUMULUS_STANDING_LENTICULAR,
        metaf::Distance(),
        std::vector<metaf::Direction>{},
        metaf::Direction());

    cda.addPhenomenaInVicinity(
        metaf::VicinityGroup::Type::ALTOCUMULUS_STANDING_LENTICULAR,
        metaf::Distance(),
        std::vector<metaf::Direction>{},
        metaf::Direction());

    cda.addPhenomenaInVicinity(
        metaf::VicinityGroup::Type::CIRROCUMULUS_STANDING_LENTICULAR,
        metaf::Distance(),
        std::vector<metaf::Direction>{},
        metaf::Direction());

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::ROTOR_CLOUD,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::VIRGA,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    cda.addPhenomenaInVicinity(
        metaf::VicinityGroup::Type::PRECIPITATION_IN_VICINITY,
        metaf::Distance(),
        std::vector<metaf::Direction>{},
        metaf::Direction());

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::FOG,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::FOG_SHALLOW,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::FOG_PATCHES,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::HAZE,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::SMOKE,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::BLOWING_SNOW,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::BLOWING_SAND,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    cda.addPhenomenaInVicinity(metaf::VicinityGroup::Type::BLOWING_DUST,
                               metaf::Distance(),
                               std::vector<metaf::Direction>{},
                               metaf::Direction());

    EXPECT_TRUE(warnings.empty());

    EXPECT_EQ(result.phenomenaInVicinity.size(), 19u);
    EXPECT_EQ(result.phenomenaInVicinity.at(0).phenomena,
              metafsimple::ObservedPhenomena::THUNDERSTORM);
    EXPECT_EQ(result.phenomenaInVicinity.at(1).phenomena,
              metafsimple::ObservedPhenomena::CUMULONIMBUS);
    EXPECT_EQ(result.phenomenaInVicinity.at(2).phenomena,
              metafsimple::ObservedPhenomena::CUMULONIMBUS_MAMMATUS);
    EXPECT_EQ(result.phenomenaInVicinity.at(3).phenomena,
              metafsimple::ObservedPhenomena::TOWERING_CUMULUS);
    EXPECT_EQ(result.phenomenaInVicinity.at(4).phenomena,
              metafsimple::ObservedPhenomena::ALTOCUMULUS_CASTELLANUS);
    EXPECT_EQ(result.phenomenaInVicinity.at(5).phenomena,
              metafsimple::ObservedPhenomena::STRATOCUMULUS_STANDING_LENTICULAR);
    EXPECT_EQ(result.phenomenaInVicinity.at(6).phenomena,
              metafsimple::ObservedPhenomena::ALTOCUMULUS_STANDING_LENTICULAR);
    EXPECT_EQ(result.phenomenaInVicinity.at(7).phenomena,
              metafsimple::ObservedPhenomena::CIRROCUMULUS_STANDING_LENTICULAR);
    EXPECT_EQ(result.phenomenaInVicinity.at(8).phenomena,
              metafsimple::ObservedPhenomena::ROTOR_CLOUD);
    EXPECT_EQ(result.phenomenaInVicinity.at(9).phenomena,
              metafsimple::ObservedPhenomena::VIRGA);
    EXPECT_EQ(result.phenomenaInVicinity.at(10).phenomena,
              metafsimple::ObservedPhenomena::PRECIPITATION);
    EXPECT_EQ(result.phenomenaInVicinity.at(11).phenomena,
              metafsimple::ObservedPhenomena::FOG);
    EXPECT_EQ(result.phenomenaInVicinity.at(12).phenomena,
              metafsimple::ObservedPhenomena::FOG_SHALLOW);
    EXPECT_EQ(result.phenomenaInVicinity.at(13).phenomena,
              metafsimple::ObservedPhenomena::FOG_PATCHES);
    EXPECT_EQ(result.phenomenaInVicinity.at(14).phenomena,
              metafsimple::ObservedPhenomena::HAZE);
    EXPECT_EQ(result.phenomenaInVicinity.at(15).phenomena,
              metafsimple::ObservedPhenomena::SMOKE);
    EXPECT_EQ(result.phenomenaInVicinity.at(16).phenomena,
              metafsimple::ObservedPhenomena::BLOWING_SNOW);
    EXPECT_EQ(result.phenomenaInVicinity.at(17).phenomena,
              metafsimple::ObservedPhenomena::BLOWING_SAND);
    EXPECT_EQ(result.phenomenaInVicinity.at(18).phenomena,
              metafsimple::ObservedPhenomena::BLOWING_DUST);
}
