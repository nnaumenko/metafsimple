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

TEST(EssentialsAdapter, skyCondition) {
    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::skyCondition(
        metaf::CloudGroup::Amount::NOT_REPORTED),
    metafsimple::Essentials::SkyCondition::UNKNOWN);

    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::skyCondition(
        metaf::CloudGroup::Amount::NONE_CLR),
    metafsimple::Essentials::SkyCondition::CLEAR_CLR);

    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::skyCondition(
        metaf::CloudGroup::Amount::NONE_SKC),
    metafsimple::Essentials::SkyCondition::CLEAR_SKC);

    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::skyCondition(
        metaf::CloudGroup::Amount::NSC),
    metafsimple::Essentials::SkyCondition::NO_SIGNIFICANT_CLOUD);

    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::skyCondition(
        metaf::CloudGroup::Amount::NCD),
    metafsimple::Essentials::SkyCondition::CLEAR_NCD);

    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::skyCondition(
        metaf::CloudGroup::Amount::FEW),
    metafsimple::Essentials::SkyCondition::CLOUDS);

    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::skyCondition(
        metaf::CloudGroup::Amount::SCATTERED),
    metafsimple::Essentials::SkyCondition::CLOUDS);

    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::skyCondition(
        metaf::CloudGroup::Amount::BROKEN),
    metafsimple::Essentials::SkyCondition::CLOUDS);

    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::skyCondition(
        metaf::CloudGroup::Amount::OVERCAST),
    metafsimple::Essentials::SkyCondition::CLOUDS);

    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::skyCondition(
        metaf::CloudGroup::Amount::VARIABLE_FEW_SCATTERED),
    metafsimple::Essentials::SkyCondition::CLOUDS);

    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::skyCondition(
        metaf::CloudGroup::Amount::VARIABLE_SCATTERED_BROKEN),
    metafsimple::Essentials::SkyCondition::CLOUDS);

    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::skyCondition(
        metaf::CloudGroup::Amount::VARIABLE_BROKEN_OVERCAST),
    metafsimple::Essentials::SkyCondition::CLOUDS);

    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::skyCondition(
        metaf::CloudGroup::Amount::OBSCURED),
    metafsimple::Essentials::SkyCondition::OBSCURED);
}

TEST(EssentialsAdapter, cloudLayerDetail) {
    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::cloudLayerDetail(
        metaf::CloudGroup::ConvectiveType::NONE),
    metafsimple::CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS);

    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::cloudLayerDetail(
        metaf::CloudGroup::ConvectiveType::TOWERING_CUMULUS),
    metafsimple::CloudLayer::Details::TOWERING_CUMULUS);
    
    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::cloudLayerDetail(
        metaf::CloudGroup::ConvectiveType::CUMULONIMBUS),
    metafsimple::CloudLayer::Details::CUMULONIMBUS);
    
    EXPECT_EQ(metafsimple::detail::EssentialsAdapter::cloudLayerDetail(
        metaf::CloudGroup::ConvectiveType::NOT_REPORTED),
    metafsimple::CloudLayer::Details::UNKNOWN);  
}