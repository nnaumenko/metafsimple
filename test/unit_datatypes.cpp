/*
* Copyright (C) 2020 Nick Naumenko (https://gitlab.com/nnaumenko,
* https:://github.com/nnaumenko)
* All rights reserved.
* This software may be modified and distributed under the terms
* of the MIT license. See the LICENSE file for details.
*/

#include "gtest/gtest.h"
#include "metafsimple.hpp"

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

    static const inline metafsimple::Speed s_8kt{
        8, metafsimple::Speed::Unit::KT};
    static const inline metafsimple::Speed s_6mps{
        6, metafsimple::Speed::Unit::MPS};
    static const inline metafsimple::Speed s_38kmh{
        38, metafsimple::Speed::Unit::KMH};
    static const inline metafsimple::Speed s_19mph{
        19, metafsimple::Speed::Unit::MPH};
    static const inline metafsimple::Speed s_empty;

    static const inline metafsimple::Distance d_4800m{
        metafsimple::Distance::Details::EXACTLY,
        4800,
        metafsimple::Distance::Unit::METERS};
    static const inline metafsimple::Distance d_3sm{
        metafsimple::Distance::Details::EXACTLY,
        3,
        metafsimple::Distance::Unit::STATUTE_MILES};
    static const inline metafsimple::Distance d_3_8sm{
        metafsimple::Distance::Details::EXACTLY,
        6,
        metafsimple::Distance::Unit::STATUTE_MILE_1_16S};
    static const inline metafsimple::Distance d_2_5_16sm = {
        metafsimple::Distance::Details::EXACTLY,
        37,
        metafsimple::Distance::Unit::STATUTE_MILE_1_16S};
    static const inline metafsimple::Distance d_33000ft{
        metafsimple::Distance::Details::EXACTLY,
        33000,
        metafsimple::Distance::Unit::FEET};
    static const inline metafsimple::Distance d_empty;

    static const inline metafsimple::Height h_2000m{
        2000, metafsimple::Height::Unit::METERS};
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

////////////////////////////////////////////////////////////////////////////////

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
    EXPECT_EQ(metafsimple::directionToCardinal(350),
              metafsimple::CardinalDirection::N);
    EXPECT_EQ(metafsimple::directionToCardinal(360),
              metafsimple::CardinalDirection::N);
    EXPECT_EQ(metafsimple::directionToCardinal(360 + 45),
              metafsimple::CardinalDirection::NE);
    EXPECT_EQ(metafsimple::directionToCardinal(-90),
              metafsimple::CardinalDirection::W);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(DataTypes, temperature_toUnit_c) {
    const auto t0 = t_empty.toUnit(metafsimple::Temperature::Unit::C);
    EXPECT_FALSE(t0.has_value());

    const auto t1 = t_m5c.toUnit(metafsimple::Temperature::Unit::C);
    ASSERT_TRUE(t1.has_value());
    EXPECT_NEAR(t1.value(), -5.0, margin);

    const auto t2 = t_11_5c.toUnit(metafsimple::Temperature::Unit::C);
    ASSERT_TRUE(t2.has_value());
    EXPECT_NEAR(t2.value(), 11.5, margin);

    const auto t3 = t_10f.toUnit(metafsimple::Temperature::Unit::C);
    ASSERT_TRUE(t3.has_value());
    EXPECT_NEAR(t3.value(), -12.222, margin);
}

TEST_F(DataTypes, temperature_toUnit_tenths_c) {
    const auto t0 = t_empty.toUnit(metafsimple::Temperature::Unit::TENTH_C);
    EXPECT_FALSE(t0.has_value());

    const auto t1 = t_m5c.toUnit(metafsimple::Temperature::Unit::TENTH_C);
    ASSERT_TRUE(t1.has_value());
    EXPECT_NEAR(t1.value(), -50.0, margin);

    const auto t2 = t_11_5c.toUnit(metafsimple::Temperature::Unit::TENTH_C);
    ASSERT_TRUE(t2.has_value());
    EXPECT_NEAR(t2.value(), 115.0, margin);

    const auto t3 = t_10f.toUnit(metafsimple::Temperature::Unit::TENTH_C);
    ASSERT_TRUE(t3.has_value());
    EXPECT_NEAR(t3.value(), -122.22, margin);
}

TEST_F(DataTypes, temperature_toUnit_f) {
    const auto t0 = t_empty.toUnit(metafsimple::Temperature::Unit::F);
    EXPECT_FALSE(t0.has_value());

    const auto t1 = t_m5c.toUnit(metafsimple::Temperature::Unit::F);
    ASSERT_TRUE(t1.has_value());
    EXPECT_NEAR(t1.value(), 23.0, margin);

    const auto t2 = t_11_5c.toUnit(metafsimple::Temperature::Unit::F);
    ASSERT_TRUE(t2.has_value());
    EXPECT_NEAR(t2.value(), 52.7, margin);

    const auto t3 = t_10f.toUnit(metafsimple::Temperature::Unit::F);
    ASSERT_TRUE(t3.has_value());
    EXPECT_NEAR(t3.value(), 10.0, margin);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(DataTypes, speed_toUnit_kt) {
    const auto s0 = s_empty.toUnit(metafsimple::Speed::Unit::KT);
    EXPECT_FALSE(s0.has_value());

    const auto s1 = s_8kt.toUnit(metafsimple::Speed::Unit::KT);
    ASSERT_TRUE(s1.has_value());
    EXPECT_NEAR(s1.value(), 8.0, margin);

    const auto s2 = s_6mps.toUnit(metafsimple::Speed::Unit::KT);
    ASSERT_TRUE(s2.has_value());
    EXPECT_NEAR(s2.value(), 11.6630, margin);

    const auto s3 = s_38kmh.toUnit(metafsimple::Speed::Unit::KT);
    ASSERT_TRUE(s3.has_value());
    EXPECT_NEAR(s3.value(), 20.5184, margin);

    const auto s4 = s_19mph.toUnit(metafsimple::Speed::Unit::KT);
    ASSERT_TRUE(s4.has_value());
    EXPECT_NEAR(s4.value(), 16.5106, margin);
}

TEST_F(DataTypes, speed_toUnit_mps) {
    const auto s0 = s_empty.toUnit(metafsimple::Speed::Unit::MPS);
    EXPECT_FALSE(s0.has_value());

    const auto s1 = s_8kt.toUnit(metafsimple::Speed::Unit::MPS);
    ASSERT_TRUE(s1.has_value());
    EXPECT_NEAR(s1.value(), 4.1156, margin);

    const auto s2 = s_6mps.toUnit(metafsimple::Speed::Unit::MPS);
    ASSERT_TRUE(s2.has_value());
    EXPECT_NEAR(s2.value(), 6.0, margin);

    const auto s3 = s_38kmh.toUnit(metafsimple::Speed::Unit::MPS);
    ASSERT_TRUE(s3.has_value());
    EXPECT_NEAR(s3.value(), 10.5556, margin);

    const auto s4 = s_19mph.toUnit(metafsimple::Speed::Unit::MPS);
    ASSERT_TRUE(s4.has_value());
    EXPECT_NEAR(s4.value(), 8.4938, margin);
}

TEST_F(DataTypes, speed_toUnit_kmh) {
    const auto s0 = s_empty.toUnit(metafsimple::Speed::Unit::KMH);
    EXPECT_FALSE(s0.has_value());

    const auto s1 = s_8kt.toUnit(metafsimple::Speed::Unit::KMH);
    ASSERT_TRUE(s1.has_value());
    EXPECT_NEAR(s1.value(), 14.816, margin);

    const auto s2 = s_6mps.toUnit(metafsimple::Speed::Unit::KMH);
    ASSERT_TRUE(s2.has_value());
    EXPECT_NEAR(s2.value(), 21.6, margin);

    const auto s3 = s_38kmh.toUnit(metafsimple::Speed::Unit::KMH);
    ASSERT_TRUE(s3.has_value());
    EXPECT_NEAR(s3.value(), 38.0, margin);

    const auto s4 = s_19mph.toUnit(metafsimple::Speed::Unit::KMH);
    ASSERT_TRUE(s4.has_value());
    EXPECT_NEAR(s4.value(), 30.5775, margin);
}

TEST_F(DataTypes, speed_toUnit_mph) {
    const auto s0 = s_empty.toUnit(metafsimple::Speed::Unit::MPH);
    EXPECT_FALSE(s0.has_value());

    const auto s1 = s_8kt.toUnit(metafsimple::Speed::Unit::MPH);
    ASSERT_TRUE(s1.has_value());
    EXPECT_NEAR(s1.value(), 9.2062, margin);

    const auto s2 = s_6mps.toUnit(metafsimple::Speed::Unit::MPH);
    ASSERT_TRUE(s2.has_value());
    EXPECT_NEAR(s2.value(), 13.4216, margin);

    const auto s3 = s_38kmh.toUnit(metafsimple::Speed::Unit::MPH);
    ASSERT_TRUE(s3.has_value());
    EXPECT_NEAR(s3.value(), 23.6121, margin);

    const auto s4 = s_19mph.toUnit(metafsimple::Speed::Unit::MPH);
    ASSERT_TRUE(s4.has_value());
    EXPECT_NEAR(s4.value(), 19.0, margin);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(DataTypes, distance_toUnit_meters) {
    const auto d0 = d_empty.toUnit(metafsimple::Distance::Unit::METERS);
    EXPECT_FALSE(d0.has_value());

    const auto d1 = d_4800m.toUnit(metafsimple::Distance::Unit::METERS);
    ASSERT_TRUE(d1.has_value());
    EXPECT_NEAR(d1.value(), 4800.0, margin);

    const auto d2 = d_3sm.toUnit(metafsimple::Distance::Unit::METERS);
    ASSERT_TRUE(d2.has_value());
    EXPECT_NEAR(d2.value(), 4828.032, margin);

    const auto d3 = d_3_8sm.toUnit(metafsimple::Distance::Unit::METERS);
    ASSERT_TRUE(d3.has_value());
    EXPECT_NEAR(d3.value(), 603.504, margin);

    const auto d4 = d_33000ft.toUnit(metafsimple::Distance::Unit::METERS);
    ASSERT_TRUE(d4.has_value());
    EXPECT_NEAR(d4.value(), 10058.4, margin);
}

TEST_F(DataTypes, distance_toUnit_statute_mile) {
    const auto d0 = d_empty.toUnit(metafsimple::Distance::Unit::STATUTE_MILES);
    EXPECT_FALSE(d0.has_value());

    const auto d1 = d_4800m.toUnit(metafsimple::Distance::Unit::STATUTE_MILES);
    ASSERT_TRUE(d1.has_value());
    EXPECT_NEAR(d1.value(), 2.9826, margin);

    const auto d2 = d_3sm.toUnit(metafsimple::Distance::Unit::STATUTE_MILES);
    ASSERT_TRUE(d2.has_value());
    EXPECT_NEAR(d2.value(), 3.0, margin);

    const auto d3 = d_3_8sm.toUnit(metafsimple::Distance::Unit::STATUTE_MILES);
    ASSERT_TRUE(d3.has_value());
    EXPECT_NEAR(d3.value(), 0.375, margin);

    const auto d4 =
        d_33000ft.toUnit(metafsimple::Distance::Unit::STATUTE_MILES);
    ASSERT_TRUE(d4.has_value());
    EXPECT_NEAR(d4.value(), 6.25, margin);
}

TEST_F(DataTypes, distance_toUnit_statute_mile_1_16) {
    const auto d0 =
        d_empty.toUnit(metafsimple::Distance::Unit::STATUTE_MILE_1_16S);
    EXPECT_FALSE(d0.has_value());

    const auto d1 =
        d_4800m.toUnit(metafsimple::Distance::Unit::STATUTE_MILE_1_16S);
    ASSERT_TRUE(d1.has_value());
    EXPECT_NEAR(d1.value(), 47.7216, margin);

    const auto d2 =
        d_3sm.toUnit(metafsimple::Distance::Unit::STATUTE_MILE_1_16S);
    ASSERT_TRUE(d2.has_value());
    EXPECT_NEAR(d2.value(), 48.0, margin);

    const auto d3 =
        d_3_8sm.toUnit(metafsimple::Distance::Unit::STATUTE_MILE_1_16S);
    ASSERT_TRUE(d3.has_value());
    EXPECT_NEAR(d3.value(), 6.0, margin);

    const auto d4 =
        d_33000ft.toUnit(metafsimple::Distance::Unit::STATUTE_MILE_1_16S);
    ASSERT_TRUE(d4.has_value());
    EXPECT_NEAR(d4.value(), 100.0, margin);
}

TEST_F(DataTypes, distance_toUnit_feet) {
    const auto d0 = d_empty.toUnit(metafsimple::Distance::Unit::FEET);
    EXPECT_FALSE(d0.has_value());

    const auto d1 = d_4800m.toUnit(metafsimple::Distance::Unit::FEET);
    ASSERT_TRUE(d1.has_value());
    EXPECT_NEAR(d1.value(), 15748.03, margin);

    const auto d2 = d_3sm.toUnit(metafsimple::Distance::Unit::FEET);
    ASSERT_TRUE(d2.has_value());
    EXPECT_NEAR(d2.value(), 15840.0, margin);

    const auto d3 = d_3_8sm.toUnit(metafsimple::Distance::Unit::FEET);
    ASSERT_TRUE(d3.has_value());
    EXPECT_NEAR(d3.value(), 1980.0, margin);

    const auto d4 = d_33000ft.toUnit(metafsimple::Distance::Unit::FEET);
    ASSERT_TRUE(d4.has_value());
    EXPECT_NEAR(d4.value(), 33000.0, margin);
}

TEST_F(DataTypes, distance_miles_int_miles_fraction) {
    ASSERT_FALSE(d_empty.milesInt().has_value());
    EXPECT_EQ(d_empty.milesFraction(),
              metafsimple::Distance::Fraction::F_0);

    ASSERT_TRUE(d_2_5_16sm.milesInt().has_value());
    EXPECT_EQ(d_2_5_16sm.milesInt().value(), 2);
    EXPECT_EQ(d_2_5_16sm.milesFraction(),
              metafsimple::Distance::Fraction::F_5_16);

    ASSERT_TRUE(d_3_8sm.milesInt().has_value());
    EXPECT_EQ(d_3_8sm.milesInt().value(), 0);
    EXPECT_EQ(d_3_8sm.milesFraction(),
              metafsimple::Distance::Fraction::F_3_8);

    ASSERT_TRUE(d_3sm.milesInt().has_value());
    EXPECT_EQ(d_3sm.milesInt(), 3);
    EXPECT_EQ(d_3sm.milesFraction(),
              metafsimple::Distance::Fraction::F_0);

    ASSERT_TRUE(d_4800m.milesInt().has_value());
    EXPECT_EQ(d_4800m.milesInt(), 2);
    EXPECT_EQ(d_4800m.milesFraction(),
              metafsimple::Distance::Fraction::F_15_16);

    ASSERT_TRUE(d_33000ft.milesInt().has_value());
    EXPECT_EQ(d_33000ft.milesInt(), 6);
    EXPECT_EQ(d_33000ft.milesFraction(),
              metafsimple::Distance::Fraction::F_1_4);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(DataTypes, height_toUnit_meters) {
    const auto h0 = h_empty.toUnit(metafsimple::Height::Unit::METERS);
    EXPECT_FALSE(h0.has_value());

    const auto h1 = h_2000m.toUnit(metafsimple::Height::Unit::METERS);
    ASSERT_TRUE(h1.has_value());
    EXPECT_NEAR(h1.value(), 2000.0, margin);

    const auto h2 = h_33000ft.toUnit(metafsimple::Height::Unit::METERS);
    ASSERT_TRUE(h2.has_value());
    EXPECT_NEAR(h2.value(), 10058.4, margin);
}

TEST_F(DataTypes, height_toUnit_feet) {
    const auto h0 = h_empty.toUnit(metafsimple::Height::Unit::FEET);
    EXPECT_FALSE(h0.has_value());

    const auto h1 = h_2000m.toUnit(metafsimple::Height::Unit::FEET);
    ASSERT_TRUE(h1.has_value());
    EXPECT_NEAR(h1.value(), 6561.680, margin);

    const auto h2 = h_33000ft.toUnit(metafsimple::Height::Unit::FEET);
    ASSERT_TRUE(h2.has_value());
    EXPECT_NEAR(h2.value(), 33000.0, margin);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(DataTypes, pressure_toUnit_hpa) {
    const auto p0 = p_empty.toUnit(metafsimple::Pressure::Unit::HPA);
    EXPECT_FALSE(p0.has_value());

    const auto p1 = p_994hpa.toUnit(metafsimple::Pressure::Unit::HPA);
    ASSERT_TRUE(p1.has_value());
    EXPECT_NEAR(p1.value(), 994.0, margin);

    const auto p2 = p_23_inhg.toUnit(metafsimple::Pressure::Unit::HPA);
    ASSERT_TRUE(p2.has_value());
    EXPECT_NEAR(p2.value(), 778.8694, margin);

    const auto p3 = p_23_34inhg.toUnit(metafsimple::Pressure::Unit::HPA);
    ASSERT_TRUE(p3.has_value());
    EXPECT_NEAR(p3.value(), 790.3831, margin);

    const auto p4 = p_750mmhg.toUnit(metafsimple::Pressure::Unit::HPA);
    ASSERT_TRUE(p4.has_value());
    EXPECT_NEAR(p4.value(), 999.9179, margin);
}

TEST_F(DataTypes, pressure_toUnit_hundredths_inhg) {
    const auto p0 =
        p_empty.toUnit(metafsimple::Pressure::Unit::HUNDREDTHS_IN_HG);
    EXPECT_FALSE(p0.has_value());

    const auto p1 =
        p_994hpa.toUnit(metafsimple::Pressure::Unit::HUNDREDTHS_IN_HG);
    ASSERT_TRUE(p1.has_value());
    EXPECT_NEAR(p1.value(), 2935.2792, margin);

    const auto p2 =
        p_23_inhg.toUnit(metafsimple::Pressure::Unit::HUNDREDTHS_IN_HG);
    ASSERT_TRUE(p2.has_value());
    EXPECT_NEAR(p2.value(), 2300.0, margin);

    const auto p3 =
        p_23_34inhg.toUnit(metafsimple::Pressure::Unit::HUNDREDTHS_IN_HG);
    ASSERT_TRUE(p3.has_value());
    EXPECT_NEAR(p3.value(), 2334.0, margin);

    const auto p4 =
        p_750mmhg.toUnit(metafsimple::Pressure::Unit::HUNDREDTHS_IN_HG);
    ASSERT_TRUE(p4.has_value());
    EXPECT_NEAR(p4.value(), 2952.7559, margin);
}

TEST_F(DataTypes, pressure_toUnit_inhg) {
    const auto p0 = p_empty.toUnit(metafsimple::Pressure::Unit::IN_HG);
    EXPECT_FALSE(p0.has_value());

    const auto p1 = p_994hpa.toUnit(metafsimple::Pressure::Unit::IN_HG);
    ASSERT_TRUE(p1.has_value());
    EXPECT_NEAR(p1.value(), 29.35, margin);

    const auto p2 = p_23_inhg.toUnit(metafsimple::Pressure::Unit::IN_HG);
    ASSERT_TRUE(p2.has_value());
    EXPECT_NEAR(p2.value(), 23.00, margin);

    const auto p3 = p_23_34inhg.toUnit(metafsimple::Pressure::Unit::IN_HG);
    ASSERT_TRUE(p3.has_value());
    EXPECT_NEAR(p3.value(), 23.34, margin);

    const auto p4 = p_750mmhg.toUnit(metafsimple::Pressure::Unit::IN_HG);
    ASSERT_TRUE(p4.has_value());
    EXPECT_NEAR(p4.value(), 29.5276, margin);
}

TEST_F(DataTypes, pressure_toUnit_mmhg) {
    const auto p0 = p_empty.toUnit(metafsimple::Pressure::Unit::MM_HG);
    EXPECT_FALSE(p0.has_value());

    const auto p1 = p_994hpa.toUnit(metafsimple::Pressure::Unit::MM_HG);
    ASSERT_TRUE(p1.has_value());
    EXPECT_NEAR(p1.value(), 745.5612, margin);

    const auto p2 = p_23_inhg.toUnit(metafsimple::Pressure::Unit::MM_HG);
    ASSERT_TRUE(p2.has_value());
    EXPECT_NEAR(p2.value(), 584.2, margin);

    const auto p3 = p_23_34inhg.toUnit(metafsimple::Pressure::Unit::MM_HG);
    ASSERT_TRUE(p3.has_value());
    EXPECT_NEAR(p3.value(), 592.836, margin);

    const auto p4 = p_750mmhg.toUnit(metafsimple::Pressure::Unit::MM_HG);
    ASSERT_TRUE(p4.has_value());
    EXPECT_NEAR(p4.value(), 750.0, margin);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(DataTypes, precipitation_toUnit_mm) {
    const auto p0 = prec_empty.toUnit(metafsimple::Precipitation::Unit::MM);
    EXPECT_FALSE(p0.has_value());

    const auto p1 = prec_8mm.toUnit(metafsimple::Precipitation::Unit::MM);
    ASSERT_TRUE(p1.has_value());
    EXPECT_NEAR(p1.value(), 8.0, margin);

    const auto p2 = prec_2in.toUnit(metafsimple::Precipitation::Unit::MM);
    ASSERT_TRUE(p2.has_value());
    EXPECT_NEAR(p2.value(), 50.8, margin);

    const auto p3 = prec_0_14inhg.toUnit(metafsimple::Precipitation::Unit::MM);
    ASSERT_TRUE(p3.has_value());
    EXPECT_NEAR(p3.value(), 3.556, margin);
}

TEST_F(DataTypes, precipitation_toUnit_hundredths_in) {
    const auto p0 = prec_empty.toUnit(metafsimple::Precipitation::Unit::HUNDREDTHS_IN);
    EXPECT_FALSE(p0.has_value());

    const auto p1 = prec_8mm.toUnit(metafsimple::Precipitation::Unit::HUNDREDTHS_IN);
    ASSERT_TRUE(p1.has_value());
    EXPECT_NEAR(p1.value(), 31.4961, margin);

    const auto p2 = prec_2in.toUnit(metafsimple::Precipitation::Unit::HUNDREDTHS_IN);
    ASSERT_TRUE(p2.has_value());
    EXPECT_NEAR(p2.value(), 200.0, margin);

    const auto p3 = prec_0_14inhg.toUnit(metafsimple::Precipitation::Unit::HUNDREDTHS_IN);
    ASSERT_TRUE(p3.has_value());
    EXPECT_NEAR(p3.value(), 14.0, margin);
}

TEST_F(DataTypes, precipitation_toUnit_in) {
    const auto p0 = prec_empty.toUnit(metafsimple::Precipitation::Unit::IN);
    EXPECT_FALSE(p0.has_value());

    const auto p1 = prec_8mm.toUnit(metafsimple::Precipitation::Unit::IN);
    ASSERT_TRUE(p1.has_value());
    EXPECT_NEAR(p1.value(), 0.315, margin);

    const auto p2 = prec_2in.toUnit(metafsimple::Precipitation::Unit::IN);
    ASSERT_TRUE(p2.has_value());
    EXPECT_NEAR(p2.value(), 2.0, margin);

    const auto p3 = prec_0_14inhg.toUnit(metafsimple::Precipitation::Unit::IN);
    ASSERT_TRUE(p3.has_value());
    EXPECT_NEAR(p3.value(), 0.14, margin);
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(DataTypes, waveheight_toUnit_decimeters) {
    const auto w0 = wh_empty.toUnit(metafsimple::WaveHeight::Unit::DECIMETERS);
    EXPECT_FALSE(w0.has_value());

    const auto w1 = wh_59dm.toUnit(metafsimple::WaveHeight::Unit::DECIMETERS);
    ASSERT_TRUE(w1.has_value());
    EXPECT_NEAR(w1.value(), 59.0, margin);

    const auto w2 = wh_3m.toUnit(metafsimple::WaveHeight::Unit::DECIMETERS);
    ASSERT_TRUE(w2.has_value());
    EXPECT_NEAR(w2.value(), 30.0, margin);

    const auto w3 = wh_8ft.toUnit(metafsimple::WaveHeight::Unit::DECIMETERS);
    ASSERT_TRUE(w3.has_value());
    EXPECT_NEAR(w3.value(), 24.384, margin);

    const auto w4 = wh_4yd.toUnit(metafsimple::WaveHeight::Unit::DECIMETERS);
    ASSERT_TRUE(w4.has_value());
    EXPECT_NEAR(w4.value(), 36.576, margin);
}

TEST_F(DataTypes, waveheight_toUnit_meters) {
    const auto w0 = wh_empty.toUnit(metafsimple::WaveHeight::Unit::METERS);
    EXPECT_FALSE(w0.has_value());

    const auto w1 = wh_59dm.toUnit(metafsimple::WaveHeight::Unit::METERS);
    ASSERT_TRUE(w1.has_value());
    EXPECT_NEAR(w1.value(), 5.9, margin);

    const auto w2 = wh_3m.toUnit(metafsimple::WaveHeight::Unit::METERS);
    ASSERT_TRUE(w2.has_value());
    EXPECT_NEAR(w2.value(), 3.0, margin);

    const auto w3 = wh_8ft.toUnit(metafsimple::WaveHeight::Unit::METERS);
    ASSERT_TRUE(w3.has_value());
    EXPECT_NEAR(w3.value(), 2.4384, margin);

    const auto w4 = wh_4yd.toUnit(metafsimple::WaveHeight::Unit::METERS);
    ASSERT_TRUE(w4.has_value());
    EXPECT_NEAR(w4.value(), 3.6576, margin);
}

TEST_F(DataTypes, waveheight_toUnit_feet) {
    const auto w0 = wh_empty.toUnit(metafsimple::WaveHeight::Unit::FEET);
    EXPECT_FALSE(w0.has_value());

    const auto w1 = wh_59dm.toUnit(metafsimple::WaveHeight::Unit::FEET);
    ASSERT_TRUE(w1.has_value());
    EXPECT_NEAR(w1.value(), 19.3569, margin);

    const auto w2 = wh_3m.toUnit(metafsimple::WaveHeight::Unit::FEET);
    ASSERT_TRUE(w2.has_value());
    EXPECT_NEAR(w2.value(), 9.8425, margin);

    const auto w3 = wh_8ft.toUnit(metafsimple::WaveHeight::Unit::FEET);
    ASSERT_TRUE(w3.has_value());
    EXPECT_NEAR(w3.value(), 8.0, margin);

    const auto w4 = wh_4yd.toUnit(metafsimple::WaveHeight::Unit::FEET);
    ASSERT_TRUE(w4.has_value());
    EXPECT_NEAR(w4.value(), 12.0, margin);
}

TEST_F(DataTypes, waveheight_toUnit_yards) {
    const auto w0 = wh_empty.toUnit(metafsimple::WaveHeight::Unit::YARDS);
    EXPECT_FALSE(w0.has_value());

    const auto w1 = wh_59dm.toUnit(metafsimple::WaveHeight::Unit::YARDS);
    ASSERT_TRUE(w1.has_value());
    EXPECT_NEAR(w1.value(), 6.4523, margin);

    const auto w2 = wh_3m.toUnit(metafsimple::WaveHeight::Unit::YARDS);
    ASSERT_TRUE(w2.has_value());
    EXPECT_NEAR(w2.value(), 3.2808, margin);

    const auto w3 = wh_8ft.toUnit(metafsimple::WaveHeight::Unit::YARDS);
    ASSERT_TRUE(w3.has_value());
    EXPECT_NEAR(w3.value(), 2.6667, margin);

    const auto w4 = wh_4yd.toUnit(metafsimple::WaveHeight::Unit::YARDS);
    ASSERT_TRUE(w4.has_value());
    EXPECT_NEAR(w4.value(), 4.0, margin);
}

TEST_F(DataTypes, waveHeight_stateOfSurface) {
    EXPECT_EQ(wh_empty.stateOfSurface(),
              metafsimple::WaveHeight::StateOfSurface::NOT_SPECIFIED);

    static const metafsimple::WaveHeight whm1{
        -1,
        metafsimple::WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(whm1.stateOfSurface(),
              metafsimple::WaveHeight::StateOfSurface::NOT_SPECIFIED);

    static const metafsimple::WaveHeight wh0{
        0,
        metafsimple::WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(wh0.stateOfSurface(),
              metafsimple::WaveHeight::StateOfSurface::CALM_GLASSY);

    static const metafsimple::WaveHeight wh1{
        1,
        metafsimple::WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(wh1.stateOfSurface(),
              metafsimple::WaveHeight::StateOfSurface::CALM_RIPPLED);

    static const metafsimple::WaveHeight wh5{
        5,
        metafsimple::WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(wh5.stateOfSurface(),
              metafsimple::WaveHeight::StateOfSurface::SMOOTH);

    static const metafsimple::WaveHeight wh12{
        12,
        metafsimple::WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(wh12.stateOfSurface(),
              metafsimple::WaveHeight::StateOfSurface::SLIGHT);

    static const metafsimple::WaveHeight wh25{
        25,
        metafsimple::WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(wh25.stateOfSurface(),
              metafsimple::WaveHeight::StateOfSurface::MODERATE);

    static const metafsimple::WaveHeight wh40{
        40,
        metafsimple::WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(wh40.stateOfSurface(),
              metafsimple::WaveHeight::StateOfSurface::ROUGH);

    static const metafsimple::WaveHeight wh60{
        60,
        metafsimple::WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(wh60.stateOfSurface(),
              metafsimple::WaveHeight::StateOfSurface::VERY_ROUGH);

    static const metafsimple::WaveHeight wh90{
        90,
        metafsimple::WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(wh90.stateOfSurface(),
              metafsimple::WaveHeight::StateOfSurface::HIGH);

    static const metafsimple::WaveHeight wh140{
        140,
        metafsimple::WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(wh140.stateOfSurface(),
              metafsimple::WaveHeight::StateOfSurface::VERY_HIGH);

    static const metafsimple::WaveHeight wh141{
        141,
        metafsimple::WaveHeight::Unit::DECIMETERS};
    EXPECT_EQ(wh141.stateOfSurface(),
              metafsimple::WaveHeight::StateOfSurface::PHENOMENAL);
}

TEST_F(DataTypes, brakingAction) {
    metafsimple::Aerodrome::RunwayData rd;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::UNKNOWN);

    rd.coefficient = 0;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::POOR);
    rd.coefficient = 25;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::POOR);

    rd.coefficient = 26;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::MEDIUM_POOR);
    rd.coefficient = 29;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::MEDIUM_POOR);

    rd.coefficient = 30;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::MEDIUM);
    rd.coefficient = 35;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::MEDIUM);

    rd.coefficient = 36;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::MEDIUM_GOOD);
    rd.coefficient = 40;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::MEDIUM_GOOD);

    rd.coefficient = 41;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::GOOD);
    rd.coefficient = 100;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::GOOD);

    rd.coefficient = -1;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::UNKNOWN);
    rd.coefficient = 101;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::UNKNOWN);

    rd = metafsimple::Aerodrome::RunwayData();
    rd.surfaceFrictionUnreliable = true;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::UNRELIABLE);

    rd.coefficient = 40;
    EXPECT_EQ(rd.brakingAction(),
              metafsimple::Aerodrome::BrakingAction::UNRELIABLE);
}