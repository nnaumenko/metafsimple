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

TEST(BasicDataAdapter, cloudLayerAmount) {
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::cloudLayerAmount(
        metaf::CloudGroup::Amount::NOT_REPORTED),
        metafsimple::CloudLayer::Amount::UNKNOWN);
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::cloudLayerAmount(
        metaf::CloudGroup::Amount::NONE_CLR),
        metafsimple::CloudLayer::Amount::UNKNOWN);
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::cloudLayerAmount(
        metaf::CloudGroup::Amount::NONE_SKC),
        metafsimple::CloudLayer::Amount::UNKNOWN);
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::cloudLayerAmount(
        metaf::CloudGroup::Amount::NSC),
        metafsimple::CloudLayer::Amount::UNKNOWN);
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::cloudLayerAmount(
        metaf::CloudGroup::Amount::NCD),
        metafsimple::CloudLayer::Amount::UNKNOWN);
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::cloudLayerAmount(
        metaf::CloudGroup::Amount::FEW),
        metafsimple::CloudLayer::Amount::FEW);
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::cloudLayerAmount(
        metaf::CloudGroup::Amount::SCATTERED),
        metafsimple::CloudLayer::Amount::SCATTERED);
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::cloudLayerAmount(
        metaf::CloudGroup::Amount::BROKEN),
        metafsimple::CloudLayer::Amount::BROKEN);
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::cloudLayerAmount(
        metaf::CloudGroup::Amount::OVERCAST),
        metafsimple::CloudLayer::Amount::OVERCAST);
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::cloudLayerAmount(
        metaf::CloudGroup::Amount::VARIABLE_FEW_SCATTERED),
        metafsimple::CloudLayer::Amount::VARIABLE_FEW_SCATTERED);
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::cloudLayerAmount(
        metaf::CloudGroup::Amount::VARIABLE_SCATTERED_BROKEN),
        metafsimple::CloudLayer::Amount::VARIABLE_SCATTERED_BROKEN);
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::cloudLayerAmount(
        metaf::CloudGroup::Amount::VARIABLE_BROKEN_OVERCAST),
        metafsimple::CloudLayer::Amount::VARIABLE_BROKEN_OVERCAST);
}

TEST(BasicDataAdapter, weatherPhenomenaIncorrect) {
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::weatherPhenomena(
        metaf::WeatherPhenomena::Qualifier::NONE,
        metaf::WeatherPhenomena::Descriptor::SHALLOW,
        {metaf::WeatherPhenomena::Weather::RAIN}),
        std::optional<metafsimple::Weather::Phenomena>());
}

TEST(BasicDataAdapter, weatherPhenomenaRecent) {
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::weatherPhenomena(
        metaf::WeatherPhenomena::Qualifier::RECENT,
        metaf::WeatherPhenomena::Descriptor::THUNDERSTORM,
        {}),
        metafsimple::Weather::Phenomena::THUNDERSTORM);
}

TEST(BasicDataAdapter, weatherPhenomenaVicinity) {
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::weatherPhenomena(
        metaf::WeatherPhenomena::Qualifier::VICINITY,
        metaf::WeatherPhenomena::Descriptor::NONE,
        {metaf::WeatherPhenomena::Weather::FUNNEL_CLOUD}),
        metafsimple::Weather::Phenomena::FUNNEL_CLOUD);
}

TEST(BasicDataAdapter, precipitationPhenomenaIncorrect) {
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::precipitationPhenomena(
        metaf::WeatherPhenomena::Qualifier::LIGHT,
        metaf::WeatherPhenomena::Descriptor::SHALLOW),
    std::optional<metafsimple::Weather::Phenomena>());
}

TEST(BasicDataAdapter, weatherPrecipitationIncorrect) {
    EXPECT_EQ(metafsimple::detail::BasicDataAdapter::weatherPrecipitation(
        metaf::WeatherPhenomena::Weather::ICE_CRYSTALS),
    std::optional<metafsimple::Weather::Precipitation>());
}
