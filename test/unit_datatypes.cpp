/*
* Copyright (C) 2020 Nick Naumenko (https://gitlab.com/nnaumenko,
* https:://github.com/nnaumenko)
* All rights reserved.
* This software may be modified and distributed under the terms
* of the MIT license. See the LICENSE file for details.
*/

#include <metafsimple.hpp>

#include "gtest/gtest.h"

class DataTypes : public ::testing::Test {
   protected:
    DataTypes() {}

    static const inline metafsimple::Temperature t_m5c{
        -11, metafsimple::Temperature::Unit::C};
    static const inline metafsimple::Temperature t_11_5c{
        115, metafsimple::Temperature::Unit::TENTH_C};
    static const inline metafsimple::Temperature t_10f{
        10, metafsimple::Temperature::Unit::C};
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
/*
TEST_F(DataTypes, directionToCardinal) {
    //TODO
}

TEST_F(DataTypes, temperature_toUnit_c) {
    //TODO
}

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

TEST_F(DataTypes, waveheight_toUnit_yards) {
    //TODO
}
*/