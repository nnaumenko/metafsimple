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

bool testWeather(const std::string& weatherString,
                 const metafsimple::Weather& weatherPhenomena) {
    const auto w = metaf::WeatherPhenomena::fromString(weatherString, true);
    if (!w.has_value()) return false;
    const auto wp = metafsimple::detail::BasicDataAdapter::weather(w.value());
    if (!wp.has_value()) return false;
    if (!(wp == weatherPhenomena)) return false;
    return true;
}

TEST(BasicDataAdapter, weather) {
    std::vector<std::pair<std::string, metafsimple::Weather>> phenomena = {
        // Typical phenomena
        std::pair("MIFG",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::SHALLOW_FOG,
                      {}}),
        std::pair("PRFG",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PARTIAL_FOG,
                      {}}),
        std::pair("BCFG",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PATCHES_FOG,
                      {}}),
        std::pair("FZFG",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::FREEZING_FOG,
                      {}}),
        std::pair("FG",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::FOG,
                      {}}),
        std::pair("DRDU",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::DRIFTING_DUST,
                      {}}),
        std::pair("BLDU",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::BLOWING_DUST,
                      {}}),
        std::pair("DU",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::DUST,
                      {}}),
        std::pair("DRSA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::DRIFTING_SAND,
                      {}}),
        std::pair("BLSA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::BLOWING_SAND,
                      {}}),
        std::pair("SA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::SAND,
                      {}}),
        std::pair("DRSN",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::DRIFTING_SNOW,
                      {}}),
        std::pair("BLSN",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::BLOWING_SNOW,
                      {}}),
        std::pair("BLPY",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::BLOWING_SPRAY,
                      {}}),
        std::pair("IC",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::ICE_CRYSTALS,
                      {}}),
        std::pair("BR",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::MIST,
                      {}}),
        std::pair("FU",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::SMOKE,
                      {}}),
        std::pair("VA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::VOLCANIC_ASH,
                      {}}),
        std::pair("HZ",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::HAZE,
                      {}}),
        std::pair("PO",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::DUST_WHIRLS,
                      {}}),
        std::pair("SQ",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::SQUALLS,
                      {}}),
        std::pair("FC",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::FUNNEL_CLOUD,
                      {}}),
        std::pair("+FC",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::TORNADO,
                      {}}),
        std::pair("DS",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::DUST_STORM,
                      {}}),
        std::pair("SS",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::SAND_STORM,
                      {}}),
        std::pair("DSSS",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::DUST_SAND_STORM,
                      {}}),
        std::pair("+DS",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::HEAVY_DUST_STORM,
                      {}}),
        std::pair("+SS",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::HEAVY_SAND_STORM,
                      {}}),
        std::pair("+DSSS",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::HEAVY_DUST_SAND_STORM,
                      {}}),
        // Special cases: descriptors without phenomena
        std::pair("VCSH",  // Assuming that VC will be ignored during conversion
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PRECIPITATION,
                      {}}),
        std::pair("TS",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::THUNDERSTORM,
                      {}}),
        // Precipitation types
        std::pair("RA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PRECIPITATION_MODERATE,
                      {metafsimple::Weather::Precipitation::RAIN}}),
        std::pair("SN",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PRECIPITATION_MODERATE,
                      {metafsimple::Weather::Precipitation::SNOW}}),
        std::pair("PL",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PRECIPITATION_MODERATE,
                      {metafsimple::Weather::Precipitation::ICE_PELLETS}}),
        std::pair("SG",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PRECIPITATION_MODERATE,
                      {metafsimple::Weather::Precipitation::SNOW_GRAINS}}),
        std::pair("DZ",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PRECIPITATION_MODERATE,
                      {metafsimple::Weather::Precipitation::DRIZZLE}}),
        std::pair("GR",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PRECIPITATION_MODERATE,
                      {metafsimple::Weather::Precipitation::HAIL}}),
        std::pair("GS",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PRECIPITATION_MODERATE,
                      {metafsimple::Weather::Precipitation::SMALL_HAIL}}),
        std::pair("UP",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PRECIPITATION_MODERATE,
                      {metafsimple::Weather::Precipitation::UNDETERMINED}}),
        // Light and heavy precipitation
        std::pair("-RA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PRECIPITATION_LIGHT,
                      {metafsimple::Weather::Precipitation::RAIN}}),
        std::pair("+RA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PRECIPITATION_HEAVY,
                      {metafsimple::Weather::Precipitation::RAIN}}),
        // Showery, freezing precipitation and precipitation with thunderstorm
        std::pair("-SHRA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::
                          SHOWERY_PRECIPITATION_LIGHT,
                      {metafsimple::Weather::Precipitation::RAIN}}),
        std::pair("SHRA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::
                          SHOWERY_PRECIPITATION_MODERATE,
                      {metafsimple::Weather::Precipitation::RAIN}}),
        std::pair("+SHRA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::
                          SHOWERY_PRECIPITATION_HEAVY,
                      {metafsimple::Weather::Precipitation::RAIN}}),
        std::pair("-FZRA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::
                          FREEZING_PRECIPITATION_LIGHT,
                      {metafsimple::Weather::Precipitation::RAIN}}),
        std::pair("FZRA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::
                          FREEZING_PRECIPITATION_MODERATE,
                      {metafsimple::Weather::Precipitation::RAIN}}),
        std::pair("+FZRA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::
                          FREEZING_PRECIPITATION_HEAVY,
                      {metafsimple::Weather::Precipitation::RAIN}}),
        std::pair("-TSRA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::
                          THUNDERSTORM_PRECIPITATION_LIGHT,
                      {metafsimple::Weather::Precipitation::RAIN}}),
        std::pair("TSRA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::
                          THUNDERSTORM_PRECIPITATION_MODERATE,
                      {metafsimple::Weather::Precipitation::RAIN}}),
        std::pair("+TSRA",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::
                          THUNDERSTORM_PRECIPITATION_HEAVY,
                      {metafsimple::Weather::Precipitation::RAIN}}),
        // Mixed precipitation
        std::pair("RASN",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::PRECIPITATION_MODERATE,
                      {metafsimple::Weather::Precipitation::RAIN,
                       metafsimple::Weather::Precipitation::SNOW}}),
        std::pair("-FZRADZ",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::
                          FREEZING_PRECIPITATION_LIGHT,
                      {metafsimple::Weather::Precipitation::RAIN,
                       metafsimple::Weather::Precipitation::DRIZZLE}}),
        std::pair("+TSRAGR",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::
                          THUNDERSTORM_PRECIPITATION_HEAVY,
                      {metafsimple::Weather::Precipitation::RAIN,
                       metafsimple::Weather::Precipitation::HAIL}}),
        std::pair("SHSNPL",
                  metafsimple::Weather{
                      metafsimple::Weather::Phenomena::
                          SHOWERY_PRECIPITATION_MODERATE,
                      {metafsimple::Weather::Precipitation::SNOW,
                       metafsimple::Weather::Precipitation::ICE_PELLETS}}),
    };

    for (const auto& p : phenomena) {
        const auto wStr = std::get<std::string>(p);
        const auto wPh = std::get<metafsimple::Weather>(p);
        EXPECT_TRUE(testWeather(wStr, wPh));
    }
}

TEST(BasicDataAdapter, phenomenaInVicinity) {
    const auto thunderstorm =
        metafsimple::detail::BasicDataAdapter::vicinityPhenomena(
            metafsimple::Weather{
                metafsimple::Weather::Phenomena::THUNDERSTORM, {}});
    EXPECT_EQ(thunderstorm.value(),
              metafsimple::ObservedPhenomena::THUNDERSTORM);

    const auto fog =
        metafsimple::detail::BasicDataAdapter::vicinityPhenomena(
            metafsimple::Weather{
                metafsimple::Weather::Phenomena::FOG, {}});
    EXPECT_EQ(fog.value(),
              metafsimple::ObservedPhenomena::FOG);

    const auto precipitation =
        metafsimple::detail::BasicDataAdapter::vicinityPhenomena(
            metafsimple::Weather{
                metafsimple::Weather::Phenomena::PRECIPITATION, {}});
    EXPECT_EQ(precipitation.value(),
              metafsimple::ObservedPhenomena::PRECIPITATION);

    const auto dustWhirls =
        metafsimple::detail::BasicDataAdapter::vicinityPhenomena(
            metafsimple::Weather{
                metafsimple::Weather::Phenomena::DUST_WHIRLS, {}});
    EXPECT_EQ(dustWhirls.value(),
              metafsimple::ObservedPhenomena::DUST_WHIRLS);

    const auto funnelCloud =
        metafsimple::detail::BasicDataAdapter::vicinityPhenomena(
            metafsimple::Weather{
                metafsimple::Weather::Phenomena::FUNNEL_CLOUD, {}});
    EXPECT_EQ(funnelCloud.value(),
              metafsimple::ObservedPhenomena::FUNNEL_CLOUD);

    const auto blowindDust =
        metafsimple::detail::BasicDataAdapter::vicinityPhenomena(
            metafsimple::Weather{
                metafsimple::Weather::Phenomena::BLOWING_DUST, {}});
    EXPECT_EQ(blowindDust.value(),
              metafsimple::ObservedPhenomena::BLOWING_DUST);

    const auto blowindSand =
        metafsimple::detail::BasicDataAdapter::vicinityPhenomena(
            metafsimple::Weather{
                metafsimple::Weather::Phenomena::BLOWING_SAND, {}});
    EXPECT_EQ(blowindSand.value(),
              metafsimple::ObservedPhenomena::BLOWING_SAND);

    const auto blowindSnow =
        metafsimple::detail::BasicDataAdapter::vicinityPhenomena(
            metafsimple::Weather{
                metafsimple::Weather::Phenomena::BLOWING_SNOW, {}});
    EXPECT_EQ(blowindSnow.value(),
              metafsimple::ObservedPhenomena::BLOWING_SNOW);

    const auto sandStorm =
        metafsimple::detail::BasicDataAdapter::vicinityPhenomena(
            metafsimple::Weather{
                metafsimple::Weather::Phenomena::SAND_STORM, {}});
    EXPECT_EQ(sandStorm.value(),
              metafsimple::ObservedPhenomena::SAND_STORM);

    const auto dustStorm =
        metafsimple::detail::BasicDataAdapter::vicinityPhenomena(
            metafsimple::Weather{
                metafsimple::Weather::Phenomena::DUST_STORM, {}});
    EXPECT_EQ(dustStorm.value(),
              metafsimple::ObservedPhenomena::DUST_STORM);

    const auto volcanicAsh =
        metafsimple::detail::BasicDataAdapter::vicinityPhenomena(
            metafsimple::Weather{
                metafsimple::Weather::Phenomena::VOLCANIC_ASH, {}});
    EXPECT_EQ(volcanicAsh.value(),
              metafsimple::ObservedPhenomena::VOLCANIC_ASH);

    const auto invalidPhenomena =
        metafsimple::detail::BasicDataAdapter::vicinityPhenomena(
            metafsimple::Weather{
                metafsimple::Weather::Phenomena::SQUALLS, {}});
    EXPECT_FALSE(invalidPhenomena.has_value());
}
