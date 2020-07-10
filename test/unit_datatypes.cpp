/*
* Copyright (C) 2020 Nick Naumenko (https://gitlab.com/nnaumenko,
* https:://github.com/nnaumenko)
* All rights reserved.
* This software may be modified and distributed under the terms
* of the MIT license. See the LICENSE file for details.
*/

#include "metafsimple.hpp"
#include "gtest/gtest.h"

const auto margin = 0.01 / 2;

class DataTypes : public ::testing::Test {
   protected:
    DataTypes() {}

    static const inline metafsimple::Temperature t_m5c{
        -5, metafsimple::Temperature::Unit::C};
    static const inline metafsimple::Temperature t_11_5c{
        115, metafsimple::Temperature::Unit::TENTH_C};
    static const inline metafsimple::Temperature t_10f{
        10, metafsimple::Temperature::Unit::F};
    static const inline metafsimple::Temperature t_empty;

    static const inline metafsimple::Speed s_10kt{
        10, metafsimple::Speed::Unit::KT};
    static const inline metafsimple::Speed s_10mps{
        10, metafsimple::Speed::Unit::MPS};
    static const inline metafsimple::Speed s_10kmh{
        10, metafsimple::Speed::Unit::KMH};
    static const inline metafsimple::Speed s_10mph{
        10, metafsimple::Speed::Unit::MPH};
    static const inline metafsimple::Speed s_empty;

    static const inline metafsimple::Distance d_2000m{
        metafsimple::Distance::Details::EXACTLY,
        2000,
        metafsimple::Distance::Unit::METERS};
    static const inline metafsimple::Distance d_3sm{
        metafsimple::Distance::Details::EXACTLY,
        3,
        metafsimple::Distance::Unit::STATUTE_MILES};
    static const inline metafsimple::Distance d_1_4sm{
        metafsimple::Distance::Details::EXACTLY,
        1,
        metafsimple::Distance::Unit::STATUTE_MILE_1_16S};
    static const inline metafsimple::Distance d_33000ft{
        metafsimple::Distance::Details::EXACTLY,
        33000,
        metafsimple::Distance::Unit::FEET};
    static const inline metafsimple::Distance d_empty;

    static const inline metafsimple::Height h_2000m{
        33000, metafsimple::Height::Unit::METERS};
    static const inline metafsimple::Height h_33000ft{
        33000, metafsimple::Height::Unit::FEET};
    static const inline metafsimple::Height h_empty;

    static const inline metafsimple::Pressure p_994hpa{
        994, metafsimple::Pressure::Unit::HPA};
    static const inline metafsimple::Pressure p_23_34inhg{
        2334, metafsimple::Pressure::Unit::HUNDREDTHS_IN_HG};
    static const inline metafsimple::Pressure p_23_inhg{
        23, metafsimple::Pressure::Unit::IN_HG};
    static const inline metafsimple::Pressure p_750mmhg{
        750, metafsimple::Pressure::Unit::MM_HG};
    static const inline metafsimple::Pressure p_empty;

    static const inline metafsimple::Precipitation prec_8mm{
        8, metafsimple::Precipitation::Unit::MM};
    static const inline metafsimple::Precipitation prec_0_14inhg{
        14, metafsimple::Precipitation::Unit::HUNDREDTHS_IN};
    static const inline metafsimple::Precipitation prec_2in{
        2, metafsimple::Precipitation::Unit::IN};
    static const inline metafsimple::Precipitation prec_empty;

    static const inline metafsimple::WaveHeight wh_59dm{
        59, metafsimple::WaveHeight::Unit::DECIMETERS};
    static const inline metafsimple::WaveHeight wh_3m{
        3, metafsimple::WaveHeight::Unit::METERS};
    static const inline metafsimple::WaveHeight wh_8ft{
        8, metafsimple::WaveHeight::Unit::FEET};
    static const inline metafsimple::WaveHeight wh_4yd{
        4, metafsimple::WaveHeight::Unit::YARDS};
    static const inline metafsimple::WaveHeight wh_empty;
};

TEST_F(DataTypes, directionToCardinal) {
    EXPECT_EQ(metafsimple::directionToCardinal(std::optional<int>()),
              metafsimple::CardinalDirection::NOT_SPECIFIED);
    EXPECT_EQ(metafsimple::directionToCardinal(0),
              metafsimple::CardinalDirection::N);
    EXPECT_EQ(metafsimple::directionToCardinal(45),
              metafsimple::CardinalDirection::NE);
    EXPECT_EQ(metafsimple::directionToCardinal(90),
              metafsimple::CardinalDirection::E);
    EXPECT_EQ(metafsimple::directionToCardinal(135),
              metafsimple::CardinalDirection::SE);
    EXPECT_EQ(metafsimple::directionToCardinal(180),
              metafsimple::CardinalDirection::S);
    EXPECT_EQ(metafsimple::directionToCardinal(225),
              metafsimple::CardinalDirection::SW);
    EXPECT_EQ(metafsimple::directionToCardinal(270),
              metafsimple::CardinalDirection::W);
    EXPECT_EQ(metafsimple::directionToCardinal(315),
              metafsimple::CardinalDirection::NW);
    EXPECT_EQ(metafsimple::directionToCardinal(360),
              metafsimple::CardinalDirection::N);
    EXPECT_EQ(metafsimple::directionToCardinal(360 + 45),
              metafsimple::CardinalDirection::NE);
    EXPECT_EQ(metafsimple::directionToCardinal(-90),
              metafsimple::CardinalDirection::W);
}

TEST_F(DataTypes, temperature_toUnit_c) {
    const auto t0 = t_empty.toUnit(metafsimple::Temperature::Unit::C);
    EXPECT_FALSE(t0.has_value()); 

    const auto t1 = t_m5c.toUnit(metafsimple::Temperature::Unit::C);
    ASSERT_TRUE(t1.has_value()); 
    EXPECT_NEAR(*t1, -5.0, margin);

    const auto t2 = t_11_5c.toUnit(metafsimple::Temperature::Unit::C);
    ASSERT_TRUE(t2.has_value()); 
    EXPECT_NEAR(*t2, 11.5, margin);

    const auto t3 = t_10f.toUnit(metafsimple::Temperature::Unit::C);
    ASSERT_TRUE(t3.has_value()); 
    EXPECT_NEAR(*t3, -12.222, margin);
}

/*
TEST_F(DataTypes, temperature_toUnit_tenths_c) {
    //TODO
}

TEST_F(DataTypes, temperature_toUnit_f) {
    //TODO
}

TEST_F(DataTypes, speed_toUnit_kt) {
    //TODO
}

TEST_F(DataTypes, speed_toUnit_mps) {
    //TODO
}

TEST_F(DataTypes, speed_toUnit_kmh) {
    //TODO
}

TEST_F(DataTypes, speed_toUnit_mph) {
    //TODO
}

TEST_F(DataTypes, distance_toUnit_meters) {
    //TODO
}

TEST_F(DataTypes, distance_toUnit_statute_mile) {
    //TODO
}

TEST_F(DataTypes, distance_toUnit_statute_mile_1_16) {
    //TODO
}

TEST_F(DataTypes, distance_toUnit_feet) {
    //TODO
}

TEST_F(DataTypes, height_toUnit_meters) {
    //TODO
}

TEST_F(DataTypes, height_toUnit_feet) {
    //TODO
}

TEST_F(DataTypes, pressure_toUnit_hpa) {
    //TODO
}

TEST_F(DataTypes, pressure_toUnit_hundredths_inhg) {
    //TODO
}

TEST_F(DataTypes, pressure_toUnit_inhg) {
    //TODO
}

TEST_F(DataTypes, pressure_toUnit_mmhg) {
    //TODO
}

TEST_F(DataTypes, precipitation_toUnit_mm) {
    //TODO
}

TEST_F(DataTypes, precipitation_toUnit_hundredths_in) {
    //TODO
}

TEST_F(DataTypes, precipitation_toUnit_in) {
    //TODO
}

TEST_F(DataTypes, waveheight_toUnit_decimeters) {
    //TODO
}

TEST_F(DataTypes, waveheight_toUnit_meters) {
    //TODO
}

TEST_F(DataTypes, waveheight_toUnit_feet) {
    //TODO
}

TEST_F(DataTypes, waveheight_toUnit_yards){
    //TODO
} */