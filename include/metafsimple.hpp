/*
* Copyright (C) 2020 Nick Naumenko (https://gitlab.com/nnaumenko,
* https:://github.com/nnaumenko)
* All rights reserved.
* This software may be modified and distributed under the terms
* of the MIT license. See the LICENSE file for details.
*/

#ifndef METAFSIMPLE_HPP
#define METAFSIMPLE_HPP

#include <cassert>
#include <optional>
#include <set>
#include <vector>

#include "metaf.hpp"

namespace metafsimple {

// Metaf-simple library version
struct Version {
    inline static const int major = 0;
    inline static const int minor = 2;
    inline static const int patch = 4;
    inline static const char tag[] = "";
};

// Cardinal direction, including cardinal and ordinal directions, overhead,
// all quadrants (all directions), unknown direction and unspecified direction
enum class CardinalDirection {
    NOT_SPECIFIED,
    N,
    S,
    W,
    E,
    NW,
    SW,
    NE,
    SE,
    OVERHEAD,
    ALL_QUADRANTS,
    UNKNOWN
};

// Convert value in degrees to cardinal direction. Negative values and values
// above 360 degrees are valid. Empty std::optional results in
// CardinalDirection::NOT_SPECIFIED
inline CardinalDirection directionToCardinal(std::optional<int> degrees);

// Runway identification: runway heading and designator to distinguish
// parallel runways.
struct Runway {
    enum class Designator {
        NONE,
        LEFT,
        CENTER,
        RIGHT
    };
    int number = 0;
    Designator designator;
};

// Day-hour-minute time; day is optional
struct Time {
    std::optional<int> day;
    std::optional<int> hour;
    std::optional<int> minute;
};

// Temperature value in degrees Celsius, 1/10s degrees Celsius or degrees
// Fahrenheit
struct Temperature {
    enum class Unit {
        C,
        TENTH_C,
        F
    };
    std::optional<int> temperature;
    Unit unit = Unit::C;
    inline std::optional<double> toUnit(Unit u) const;
};

// Speed value in knots, meters per second, kilometers per hour, miles per hour
struct Speed {
    enum class Unit {
        KT,
        MPS,
        KMH,
        MPH
    };
    std::optional<int> speed;
    Unit unit = Unit::KT;
    inline std::optional<double> toUnit(Unit u) const;
};

// Distance in meters, statute miles, 1/16s of statute mile, or feet; distance
// value may be augmented by relation 'less than' or 'more than'
struct Distance {
    enum class Unit {
        METERS,
        STATUTE_MILES,
        STATUTE_MILE_1_16S,
        FEET
    };
    enum class Details {
        EXACTLY,    // Distance is exactly as specified value
        LESS_THAN,  // Distance is less than specified value
        MORE_THAN   // Distance is more than specified value
    };
    // Fraction of value in miles, in 1/16s of statute mile
    enum class Fraction {
        F_0 = 0,
        F_1_16 = 1,
        F_1_8 = 2,
        F_3_16 = 3,
        F_1_4 = 4,
        F_5_16 = 5,
        F_3_8 = 6,
        F_7_16 = 7,
        F_1_2 = 8,
        F_9_16 = 9,
        F_5_8 = 10,
        F_11_16 = 11,
        F_3_4 = 12,
        F_13_16 = 13,
        F_7_8 = 14,
        F_15_16 = 15,
    };
    Details details = Details::EXACTLY;
    std::optional<int> distance;
    Unit unit = Unit::METERS;
    inline std::optional<double> toUnit(Unit u) const;
    inline std::optional<int> milesInt() const;
    inline Fraction milesFraction() const;
};

// Prevailing distance and/or minimum/maximum distance range
struct DistanceRange {
    Distance prevailing;
    Distance minimum;
    Distance maximum;
};

// Height in meters or feet
struct Height {
    enum class Unit {
        METERS,
        FEET
    };
    std::optional<int> height;
    Unit unit = Unit::FEET;
    inline std::optional<double> toUnit(Unit u) const;
};

// Ceiling as a fixed and/or variable height value
struct Ceiling {
    Height exact;
    Height minimum;
    Height maximum;
};

// Pressure in hectopascals, inches mercury or millimeters mercury
struct Pressure {
    enum class Unit {
        HPA,
        IN_HG,
        HUNDREDTHS_IN_HG,
        MM_HG
    };
    std::optional<int> pressure;
    Unit unit = Unit::HPA;
    inline std::optional<double> toUnit(Unit u) const;
};

// Precipitation or accumulation in millimeters, inches or 1/100s of inch
struct Precipitation {
    enum class Unit {
        MM,
        IN,
        HUNDREDTHS_IN
    };
    std::optional<int> amount;
    Unit unit = Unit::MM;
    inline std::optional<double> toUnit(Unit u) const;
};

// Wave height expressed as a descriptive state of sea surface or numerical wave
// height value in meters, decimeters, feet and yards
struct WaveHeight {
    enum class Unit {
        METERS,
        DECIMETERS,
        FEET,
        YARDS
    };
    enum class StateOfSurface {
        NOT_SPECIFIED,
        CALM_GLASSY,
        CALM_RIPPLED,
        SMOOTH,
        SLIGHT,
        MODERATE,
        ROUGH,
        VERY_ROUGH,
        HIGH,
        VERY_HIGH,
        PHENOMENAL,
    };
    std::optional<int> waveHeight;
    Unit unit = Unit::DECIMETERS;
    inline std::optional<double> toUnit(Unit u) const;
    inline StateOfSurface stateOfSurface() const;
};

// Weather, either a weather phenomena or one or more kinds of precipitation
struct Weather {
    enum class Phenomena {
        UNKNOWN,
        NO_SIGNIFICANT_WEATHER,
        SHALLOW_FOG,
        PARTIAL_FOG,
        PATCHES_FOG,
        FREEZING_FOG,
        FOG,
        DRIFTING_DUST,
        BLOWING_DUST,
        DUST,
        DRIFTING_SAND,
        BLOWING_SAND,
        SAND,
        DRIFTING_SNOW,
        BLOWING_SNOW,
        BLOWING_SPRAY,
        ICE_CRYSTALS,
        MIST,
        SMOKE,
        VOLCANIC_ASH,
        HAZE,
        DUST_WHIRLS,
        SQUALLS,
        FUNNEL_CLOUD,
        TORNADO,
        SAND_STORM,
        DUST_STORM,
        DUST_SAND_STORM,
        HEAVY_SAND_STORM,
        HEAVY_DUST_STORM,
        HEAVY_DUST_SAND_STORM,
        PRECIPITATION,
        PRECIPITATION_LIGHT,
        PRECIPITATION_MODERATE,
        PRECIPITATION_HEAVY,
        SHOWERY_PRECIPITATION_LIGHT,
        SHOWERY_PRECIPITATION_MODERATE,
        SHOWERY_PRECIPITATION_HEAVY,
        FREEZING_PRECIPITATION_LIGHT,
        FREEZING_PRECIPITATION_MODERATE,
        FREEZING_PRECIPITATION_HEAVY,
        THUNDERSTORM,
        THUNDERSTORM_PRECIPITATION_LIGHT,
        THUNDERSTORM_PRECIPITATION_MODERATE,
        THUNDERSTORM_PRECIPITATION_HEAVY
    };
    enum class Precipitation {
        DRIZZLE,
        RAIN,
        SNOW,
        SNOW_GRAINS,
        ICE_PELLETS,
        HAIL,
        SMALL_HAIL,
        UNDETERMINED
    };
    Phenomena phenomena;
    std::set<Precipitation> precipitation;
};

// Cloud layer data including cloud amount, base height and cloud type details;
// also may be used for ground-based or aloft obscurations
struct CloudLayer {
    enum class Amount {
        UNKNOWN,
        FEW,
        SCATTERED,
        BROKEN,
        OVERCAST,
        VARIABLE_FEW_SCATTERED,
        VARIABLE_SCATTERED_BROKEN,
        VARIABLE_BROKEN_OVERCAST
    };
    enum class Details {
        UNKNOWN,
        NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS,
        CUMULONIMBUS,
        TOWERING_CUMULUS,
        CUMULUS,
        CUMULUS_FRACTUS,
        STRATOCUMULUS,
        NIMBOSTRATUS,
        STRATUS,
        STRATUS_FRACTUS,
        ALTOSTRATUS,
        ALTOCUMULUS,
        ALTOCUMULUS_CASTELLANUS,
        CIRRUS,
        CIRROSTRATUS,
        CIRROCUMULUS,
        BLOWING_SNOW,
        BLOWING_DUST,
        BLOWING_SAND,
        ICE_CRYSTALS,
        RAIN,
        DRIZZLE,
        SNOW,
        ICE_PELLETS,
        SMOKE,
        FOG,
        MIST,
        HAZE,
        VOLCANIC_ASH
    };
    Amount amount = Amount::UNKNOWN;
    Height height;
    Details details = Details::UNKNOWN;
    std::optional<int> okta;
};

// Phenomena observed in vicinity, including phenomena type, directions where
// it is observed, optional distance, and optional moving direction
struct Vicinity {
    enum class Phenomena {
        THUNDERSTORM,
        CUMULONIMBUS,
        CUMULONIMBUS_MAMMATUS,
        TOWERING_CUMULUS,
        ALTOCUMULUS_CASTELLANUS,
        STRATOCUMULUS_STANDING_LENTICULAR,
        ALTOCUMULUS_STANDING_LENTICULAR,
        CIRROCUMULUS_STANDING_LENTICULAR,
        ROTOR_CLOUD,
        VIRGA,
        PRECIPITATION,
        FOG,
        FOG_SHALLOW,
        FOG_PATCHES,
        HAZE,
        SMOKE,
        BLOWING_SNOW,
        BLOWING_SAND,
        BLOWING_DUST,
        DUST_WHIRLS,
        SAND_STORM,
        DUST_STORM,
        VOLCANIC_ASH,
        FUNNEL_CLOUD
    };
    Phenomena phenomena;
    DistanceRange distance;
    CardinalDirection moving;
    std::set<CardinalDirection> directions;
};

// Lightning strike information, including frequency, type, distance and
// directions where lightning strikes are observed
struct LightningStrikes {
    enum class Type {
        IN_CLOUD,
        CLOUD_CLOUD,
        CLOUD_GROUND,
        CLOUD_AIR
    };
    enum class Frequency {
        UNKNOWN,
        OCCASIONAL,
        FREQUENT,
        CONSTANT
    };
    Frequency frequency;
    std::set<Type> type;
    DistanceRange distance;
    std::set<CardinalDirection> directions;
};

// Essential weather data, specified in current weather and in forecast trends
struct Essentials {
    enum class SkyCondition {
        UNKNOWN,
        CLEAR_CLR,
        CLEAR_SKC,
        CLEAR_NCD,
        NO_SIGNIFICANT_CLOUD,
        CAVOK,
        CLOUDS,
        OBSCURED
    };
    std::optional<int> windDirectionDegrees;
    bool windDirectionVariable = false;
    std::optional<int> windDirectionVarFromDegrees;
    std::optional<int> windDirectionVarToDegrees;
    Speed windSpeed;
    Speed gustSpeed;
    bool windCalm = false;
    Distance visibility;
    bool cavok = false;
    SkyCondition skyCondition = SkyCondition::UNKNOWN;
    std::vector<CloudLayer> cloudLayers;
    Height verticalVisibility;
    std::vector<Weather> weather;
};

// Icing forecast including severity, type and height range where icing occurs
struct IcingForecast {
    enum class Severity {
        NONE_OR_TRACE,
        LIGHT,
        MODERATE,
        SEVERE
    };
    enum class Type {
        NONE,
        RIME_IN_CLOUD,
        CLEAR_IN_PRECIPITATION,
        MIXED
    };
    Severity severity;
    Type type;
    Height minHeight;
    Height maxHeight;
};

// Turbulence forecast including severity, location, frequency and height range
// where turbulence occurs
struct TurbulenceForecast {
    enum class Severity {
        NONE,
        LIGHT,
        MODERATE,
        SEVERE,
        EXTREME
    };
    enum class Location {
        NONE,
        IN_CLOUD,
        IN_CLEAR_AIR
    };
    enum class Frequency {
        NONE,
        FREQUENT,
        OCCASIONAL
    };
    Severity severity;
    Location location;
    Frequency frequency;
    Height minHeight;
    Height maxHeight;
};

// Weather trend
struct Trend {
    enum class Type {
        BECMG,
        TEMPO,
        INTER,
        TIMED,
        PROB
    };
    Type type = Type::TEMPO;
    std::optional<int> probability;
    Time timeFrom;
    Time timeUntil;
    Time timeAt;
    Essentials forecast;
};

// METAR, SPECI or TAF report information, including type of report, report
// release time, time when the report is applicable, errors encountered when
// parsing the report, warnings encountered when processing report data, and
// plain text data in the report
struct Report {
    // Report type
    enum class Type {
        ERROR,
        METAR,
        SPECI,
        TAF
    };
    // Report parsing/syntax error (error means that report data are missing)
    enum class Error {
        NO_ERROR,               // No error: report parsed with no issues
        NO_REPORT_PARSED,       // No report was parsed yet; no data present
        EMPTY_REPORT,           // Attempting to parse an empty report
        UNKNOWN_REPORT_TYPE,    // Parsed report type is 'unknown report type'
        REPORT_TOO_LARGE,       // Attempting to parse too large report
        UNEXPECTED_REPORT_END,  // Report ended unexpectedly
        REPORT_HEADER_FORMAT,   // Syntax error in report header
        NIL_OR_CNL_FORMAT,      // Syntax error in NIL or CNL report
        GROUP_NOT_ALLOWED       // Report contains invalid group for this report
    };
    // Report data warning (warning means inconsistent, duplicate or missing
    // data)
    struct Warning {
        enum class Message {
            SPECI_IN_TAF,
            BOTH_NIL_AND_CNL,
            BOTH_AMD_AND_COR,
            CNL_IN_NON_TAF,
            AMD_IN_NON_TAF,
            NO_REPORT_TIME_IN_METAR,
            APPLICABLE_TIME_IN_METAR,
            NO_APPLICABLE_TIME_IN_TAF,
            INCONSISTENT_CORRECTION_NUMBER,
            INCONSISTENT_DATA,
            DUPLICATED_DATA,
            REQUIRED_DATA_MISSING,
            INVALID_GROUP,
            INVALID_AUTOTYPE,
            INVALID_DIRECTION_SECTOR,
            INVALID_DISTANCE_RANGE,
            INVALID_3H_6H_REPORT_TIME,
            INVALID_WEATHER_PHENOMENA,
            INVALID_LIGHTNING_TYPE
        };
        Message message;
        std::string id;
    };
    Type type = Type::ERROR;
    bool missing = false;
    bool cancelled = false;
    bool correctional = false;
    bool amended = false;
    bool automated = false;
    int correctionNumber = 0;
    Time reportTime;
    Time applicableFrom;
    Time applicableUntil;
    Error error = Error::NO_REPORT_PARSED;
    std::vector<Warning> warnings;
    std::vector<std::string> plainText;
};

// Station info, including location ICAO code, auto type and missing data
struct Station {
    enum class AutoType {
        NONE,
        AO1,
        AO1A,
        AO2,
        AO2A
    };
    enum class MissingData {
        WND_MISG,
        VIS_MISG,
        RVR_MISG,
        RVRNO,
        VISNO,
        VISNO_RUNWAY,
        VISNO_DIRECTION,
        CHINO,
        CHINO_RUNWAY,
        CHINO_DIRECTION,
        PWINO,
        TSNO,
        PNO,
        FZRANO,
        SLPNO,
        TS_LTNG_TEMPO_UNAVBL,
        CLD_MISG,
        WX_MISG,
        T_MISG,
        TD_MISG,
        PRES_MISG,
        ICG_MISG,
        PCPN_MISG
    };
    std::string icaoCode;
    AutoType autoType = AutoType::NONE;
    bool requiresMaintenance = false;
    bool noSpeciReports = false;
    bool noVisDirectionalVariation = false;
    std::set<MissingData> missingData;
    std::set<Runway> runwaysNoCeilingData;
    std::set<Runway> runwaysNoVisData;
    std::set<CardinalDirection> directionsNoCeilingData;
    std::set<CardinalDirection> directionsNoVisData;
};

// Aerodrome-related info, colour code, runway and directional visibility,
// runway visual range, runway surface state, ceiling, surface and tower
// visibility, etc.
struct Aerodrome {
    enum class ColourCode {
        NOT_SPECIFIED,
        BLUE,
        WHITE,
        GREEN,
        YELLOW1,
        YELLOW2,
        AMBER,
        RED
    };
    // Runway visual ranger
    enum class RvrTrend {
        UNKNOWN,
        DOWNWARD,
        NEUTRAL,
        UPWARD
    };
    // Deposits on the runway
    enum class RunwayDeposits {
        UNKNOWN,
        CLEAR_AND_DRY,
        DAMP,
        WET_AND_WATER_PATCHES,
        RIME_AND_FROST_COVERED,
        DRY_SNOW,
        WET_SNOW,
        SLUSH,
        ICE,
        COMPACTED_OR_ROLLED_SNOW,
        FROZEN_RUTS_OR_RIDGES,
    };
    // Runway contamination extent with the deposits
    enum class RunwayContamExtent {
        UNKNOWN,
        NO_DEPOSITS,
        LESS_THAN_11_PERCENT,
        FROM_11_TO_25_PERCENT,
        FROM_26_TO_50_PERCENT,
        MORE_THAN_50_PERCENT,
    };
    // Descriptive braking action
    enum class BrakingAction {
        POOR,
        MEDIUM_POOR,
        MEDIUM,
        MEDIUM_GOOD,
        GOOD,
        UNRELIABLE,
        UNKNOWN
    };
    // State of runway surface, including type of deposits on the runway, runway
    // contamination extent by the deposits, depth of deposits, and surface
    // friction coefficient
    struct RunwayData {
        Runway runway;
        bool notOperational = false;
        bool snoclo = false;
        bool clrd = false;
        bool windShearLowerLayers = false;
        RunwayDeposits deposits = RunwayDeposits::UNKNOWN;
        RunwayContamExtent contaminationExtent = RunwayContamExtent::UNKNOWN;
        Precipitation depositDepth;
        std::optional<int> coefficient;  //in 1/100s
        bool surfaceFrictionUnreliable = false;
        inline BrakingAction brakingAction() const;
        DistanceRange visualRange;
        RvrTrend visualRangeTrend = RvrTrend::UNKNOWN;
        Ceiling ceiling;
        DistanceRange visibility;
    };
    struct DirectionData {
        CardinalDirection cardinalDirection = CardinalDirection::NOT_SPECIFIED;
        DistanceRange visibility;
        Ceiling ceiling;
    };
    bool snoclo = false;
    ColourCode colourCode = ColourCode::NOT_SPECIFIED;
    bool colourCodeBlack = false;
    std::vector<RunwayData> runways;
    std::vector<DirectionData> directions;
    Ceiling ceiling;
    Distance surfaceVisibility;
    Distance towerVisibility;
};

// Current weather data; includes essential weather data plus all non-trend
// and non-historical data specified in METAR
struct Current {
    struct WindShear {
        Height height;
        int directionDegrees;
        Speed windSpeed;
    };
    // Descriptive low cloud layer type according to International Cloud Atlas
    enum class LowCloudLayer {
        NO_CLOUDS,
        CU_HU_CU_FR,
        CU_MED_CU_CON,
        CB_CAL,
        SC_CUGEN,
        SC_NON_CUGEN,
        ST_NEB_ST_FR,
        ST_FR_CU_FR_PANNUS,
        CU_SC_NON_CUGEN_DIFFERENT_LEVELS,
        CB_CAP,
        UNKNOWN
    };
    // Descriptive mid cloud layer type according to International Cloud Atlas
    enum class MidCloudLayer {
        NO_CLOUDS,
        AS_TR,
        AS_OP_NS,
        AC_TR,
        AC_TR_LEN_PATCHES,
        AC_TR_AC_OP_SPREADING,
        AC_CUGEN_AC_CBGEN,
        AC_DU_AC_OP_AC_WITH_AS_OR_NS,
        AC_CAS_AC_FLO,
        AC_OF_CHAOTIC_SKY,
        UNKNOWN
    };
    // Descriptive high cloud layer type according to International Cloud Atlas
    enum class HighCloudLayer {
        NO_CLOUDS,
        CI_FIB_CI_UNC,
        CI_SPI_CI_CAS_CI_FLO,
        CI_SPI_CBGEN,
        CI_FIB_CI_UNC_SPREADING,
        CI_CS_LOW_ABOVE_HORIZON,
        CI_CS_HIGH_ABOVE_HORIZON,
        CS_NEB_CS_FIB_COVERING_ENTIRE_SKY,
        CS,
        CC,
        UNKNOWN
    };
    Essentials weatherData;
    DistanceRange variableVisibility;
    std::vector<CloudLayer> obscurations;
    LowCloudLayer lowCloudLayer = LowCloudLayer::UNKNOWN;
    MidCloudLayer midCloudLayer = MidCloudLayer::UNKNOWN;
    HighCloudLayer highCloudLayer = HighCloudLayer::UNKNOWN;
    Temperature airTemperature;
    Temperature dewPoint;
    std::optional<int> relativeHumidity;
    Pressure pressureSeaLevel;
    Pressure pressureGroundLevel;
    Temperature seaSurfaceTemperature;
    WaveHeight waveHeight;
    Precipitation snowWaterEquivalent;
    Precipitation snowDepthOnGround;
    bool snowIncreasingRapidly = false;
    std::vector<WindShear> windShear;
    std::vector<Vicinity> phenomenaInVicinity;
    std::vector<LightningStrikes> lightningStrikes;
    Height densityAltitude;
    std::optional<int> hailstoneSizeQuartersInch;
    bool frostOnInstrument = false;
};

// Data accumulated for previous periods of time and specified in METAR
struct Historical {
    // Pressure tendency over time
    enum class PressureTendency {
        UNKNOWN,
        INCREASING_THEN_DECREASING,
        INCREASING_MORE_SLOWLY,
        INCREASING,
        INCREASING_MORE_RAPIDLY,
        STEADY,
        DECREASING_THEN_INCREASING,
        DECREASING_MORE_SLOWLY,
        DECREASING,
        DECREASING_MORE_RAPIDLY,
        RISING_RAPIDLY,
        FALLING_RAPIDLY
    };

    // Pressure trend
    enum class PressureTrend {
        UNKNOWN,
        HIGHER,
        HIGHER_OR_SAME,
        SAME,
        LOWER_OR_SAME,
        LOWER
    };
    // Weather event type
    enum class Event {
        BEGAN,
        ENDED
    };
    // Weather event
    struct WeatherEvent {
        Event event;
        Weather weather;
        Time time;
    };
    std::optional<int> peakWindDirectionDegrees;
    Speed peakWindSpeed;
    Time peakWindObserved;
    bool windShift = false;
    bool windShiftFrontPassage = false;
    Time windShiftBegan;
    Temperature temperatureMin6h;
    Temperature temperatureMax6h;
    Temperature temperatureMin24h;
    Temperature temperatureMax24h;
    PressureTendency pressureTendency = PressureTendency::UNKNOWN;
    PressureTrend pressureTrend = PressureTrend::UNKNOWN;
    Pressure pressureChange3h;
    std::vector<WeatherEvent> recentWeather;
    Precipitation rainfall10m;
    Precipitation rainfallSince0900LocalTime;
    Precipitation precipitationSinceLastReport;
    Precipitation precipitationTotal1h;
    Precipitation precipitationFrozen3or6h;
    Precipitation precipitationFrozen3h;
    Precipitation precipitationFrozen6h;
    Precipitation precipitationFrozen24h;
    Precipitation snow6h;
    Precipitation snowfallTotal;
    Precipitation snowfallIncrease1h;
    Precipitation icing1h;
    Precipitation icing3h;
    Precipitation icing6h;
    std::optional<int> sunshineDurationMinutes24h;
};

// Forecast data including weather trends (each trend has Essentials),
// minimum and maximum temperature, pressure, icing and turbulence forecast, etc
struct Forecast {
    Essentials prevailing;
    std::vector<Trend> trends;
    bool noSignificantChanges = false;
    bool windShearConditions = false;
    Temperature minTemperature;
    Time minTemperatureTime;
    Temperature maxTemperature;
    Time maxTemperatureTime;
    std::vector<IcingForecast> icing;
    std::vector<TurbulenceForecast> turbulence;
    Pressure lowestQnh;
};

// Structure generated after processing METAR, SPECI or TAF reports, contains
// collated data of types specified above;
struct Simple {
    Report report;
    Station station;
    Aerodrome aerodrome;
    Current current;
    Historical historical;
    Forecast forecast;
};

// Needed to use std::set<Runway>
inline bool operator<(const Runway &l, const Runway &r) {
    return ((l.number * 10 + static_cast<int>(l.designator)) <
            (r.number * 10 + static_cast<int>(r.designator)));
}

std::optional<double> Temperature::toUnit(Unit u) const {
    const auto convertC = [](Unit uu, double c) {
        switch (uu) {
            case Unit::C:
                return c;
            case Unit::TENTH_C:
                return (c * 10.0);
            case Unit::F:
                return (c * 1.8 + 32);
        }
    };
    if (!temperature.has_value()) return std::optional<double>();
    switch (unit) {
        case Unit::C:
            return convertC(u, *temperature);
        case Unit::TENTH_C:
            return convertC(u, *temperature / 10.0);
        case Unit::F:
            return convertC(u, (*temperature - 32) / 1.8);
    }
}

std::optional<double> Speed::toUnit(Unit u) const {
    static const auto ktPerMps = 1.943844;
    static const auto kmhPerMps = 3.6;
    static const auto mphPerMps = 2.236936;
    auto convertMps = [](Unit uu, double mps) {
        switch (uu) {
            case Unit::KT:
                return mps * ktPerMps;
            case Unit::MPS:
                return mps;
            case Unit::KMH:
                return mps * kmhPerMps;
            case Unit::MPH:
                return mps * mphPerMps;
        }
    };
    if (!speed.has_value()) return std::optional<double>();
    switch (unit) {
        case Unit::KT:
            return convertMps(u, *speed / ktPerMps);
        case Unit::MPS:
            return convertMps(u, *speed);
        case Unit::KMH:
            return convertMps(u, *speed / kmhPerMps);
        case Unit::MPH:
            return convertMps(u, *speed / mphPerMps);
    }
}

std::optional<double> Distance::toUnit(Unit u) const {
    static const auto metersPerMile = 1609.344;
    static const auto metersPerFoot = 0.3048;
    auto convertMeters = [](Unit uu, double m) {
        switch (uu) {
            case Unit::METERS:
                return m;
            case Unit::STATUTE_MILES:
                return (m / metersPerMile);
            case Unit::STATUTE_MILE_1_16S:
                return (m / metersPerMile * 16.0);
            case Unit::FEET:
                return (m / metersPerFoot);
        }
    };
    if (!distance.has_value()) return std::optional<double>();
    switch (unit) {
        case Unit::METERS:
            return convertMeters(u, *distance);
        case Unit::STATUTE_MILES:
            return convertMeters(u, *distance * metersPerMile);
        case Unit::STATUTE_MILE_1_16S:
            return convertMeters(u, *distance * metersPerMile / 16.0);
        case Unit::FEET:
            return convertMeters(u, *distance * metersPerFoot);
    }
}

std::optional<int> Distance::milesInt() const {
    const auto t = toUnit(Unit::STATUTE_MILES);
    if (!t.has_value()) return std::optional<int>();
    return std::floor(*t);
}

Distance::Fraction Distance::milesFraction() const {
    const auto miles = toUnit(Unit::STATUTE_MILE_1_16S);
    if (!miles.has_value()) return Fraction::F_0;
    return static_cast<Fraction>(static_cast<int>(std::floor(*miles)) % 16);
}

std::optional<double> Height::toUnit(Unit u) const {
    static const auto metersPerFoot = 0.3048;
    auto convertFeet = [](Unit uu, double m) {
        switch (uu) {
            case Unit::METERS:
                return m * metersPerFoot;
            case Unit::FEET:
                return m;
        }
    };
    if (!height.has_value()) return std::optional<double>();
    switch (unit) {
        case Unit::METERS:
            return convertFeet(u, *height / metersPerFoot);
        case Unit::FEET:
            return convertFeet(u, *height);
    }
}

std::optional<double> Pressure::toUnit(Unit u) const {
    static const auto hpaPerInHg = 33.8639;
    static const auto hpaPerMmHg = 1.3332239;
    auto convertHpa = [](Unit uu, double hpa) {
        switch (uu) {
            case Unit::HPA:
                return hpa;
            case Unit::IN_HG:
                return (hpa / hpaPerInHg);
            case Unit::HUNDREDTHS_IN_HG:
                return (hpa / hpaPerInHg * 100.0);
            case Unit::MM_HG:
                return (hpa / hpaPerMmHg);
        }
    };
    if (!pressure.has_value()) return std::optional<double>();
    switch (unit) {
        case Unit::HPA:
            return convertHpa(u, *pressure);
        case Unit::IN_HG:
            return convertHpa(u, *pressure * hpaPerInHg);
        case Unit::HUNDREDTHS_IN_HG:
            return convertHpa(u, *pressure * hpaPerInHg / 100.0);
        case Unit::MM_HG:
            return convertHpa(u, *pressure * hpaPerMmHg);
    }
}

std::optional<double> Precipitation::toUnit(Unit u) const {
    static const auto mmPerInch = 25.4;
    auto convertMm = [](Unit uu, double mm) {
        switch (uu) {
            case Unit::MM:
                return mm;
            case Unit::IN:
                return (mm / mmPerInch);
            case Unit::HUNDREDTHS_IN:
                return (mm / mmPerInch * 100.0);
        }
    };
    if (!amount.has_value()) return std::optional<double>();
    switch (unit) {
        case Unit::MM:
            return convertMm(u, *amount);
        case Unit::IN:
            return convertMm(u, *amount * mmPerInch);
        case Unit::HUNDREDTHS_IN:
            return convertMm(u, *amount * mmPerInch / 100.0);
    }
}

std::optional<double> WaveHeight::toUnit(Unit u) const {
    static const auto decimetersPerMeter = 10.0;
    static const auto feetPerMeter = 1.0 / 0.3048;
    static const auto yardsPerMeter = 1.0 / 0.9144;
    auto convertDecimeters = [](Unit uu, double dm) {
        switch (uu) {
            case Unit::DECIMETERS:
                return dm;
            case Unit::METERS:
                return (dm / decimetersPerMeter);
            case Unit::FEET:
                return (dm / decimetersPerMeter * feetPerMeter);
            case Unit::YARDS:
                return (dm / decimetersPerMeter * yardsPerMeter);
        }
    };
    if (!waveHeight.has_value()) return std::optional<double>();
    switch (unit) {
        case Unit::DECIMETERS:
            return convertDecimeters(u, *waveHeight);
        case Unit::METERS:
            return convertDecimeters(u, *waveHeight * decimetersPerMeter);
        case Unit::FEET:
            return convertDecimeters(u, *waveHeight *
                                            decimetersPerMeter /
                                            feetPerMeter);
        case Unit::YARDS:
            return convertDecimeters(u, *waveHeight *
                                            decimetersPerMeter /
                                            yardsPerMeter);
    }
}

WaveHeight::StateOfSurface WaveHeight::stateOfSurface() const {
    const auto ht = toUnit(Unit::DECIMETERS);
    if (!ht.has_value()) return StateOfSurface::NOT_SPECIFIED;
    // See Table 3700 in Manual on Codes (WMO No. 306)
    const auto h = static_cast<int>(std::round(*ht));
    if (h < 0) return StateOfSurface::NOT_SPECIFIED;
    if (!h) return StateOfSurface::CALM_GLASSY;
    if (h == 1) return StateOfSurface::CALM_RIPPLED;
    if (h <= 5) return StateOfSurface::SMOOTH;
    if (h <= 12) return StateOfSurface::SLIGHT;
    if (h <= 25) return StateOfSurface::MODERATE;
    if (h <= 40) return StateOfSurface::ROUGH;
    if (h <= 60) return StateOfSurface::VERY_ROUGH;
    if (h <= 90) return StateOfSurface::HIGH;
    if (h <= 140) return StateOfSurface::VERY_HIGH;
    return StateOfSurface::PHENOMENAL;
}

CardinalDirection directionToCardinal(std::optional<int> degrees) {
    if (!degrees.has_value()) return CardinalDirection::NOT_SPECIFIED;
    const int fullCircle = 360;         // 360 degrees: full circle
    const int octant = fullCircle / 8;  // 45 degrees: octant
    const int half = octant / 2 + 1;    // 23 degrees (int): half octant
    auto d = *degrees % fullCircle;
    if (d < 0) d += fullCircle;
    if (d <= half) return CardinalDirection::N;
    if (d <= (half + octant)) return CardinalDirection::NE;
    if (d <= (half + octant * 2)) return CardinalDirection::E;
    if (d <= (half + octant * 3)) return CardinalDirection::SE;
    if (d <= (half + octant * 4)) return CardinalDirection::S;
    if (d <= (half + octant * 5)) return CardinalDirection::SW;
    if (d <= (half + octant * 6)) return CardinalDirection::W;
    if (d <= (half + octant * 7)) return CardinalDirection::NW;
    return CardinalDirection::N;
}

Aerodrome::BrakingAction Aerodrome::RunwayData::brakingAction() const {
    if (surfaceFrictionUnreliable) return BrakingAction::UNRELIABLE;
    if (!coefficient.has_value()) return BrakingAction::UNKNOWN;
    if (*coefficient < 0 || *coefficient > 100) return BrakingAction::UNKNOWN;
    if (*coefficient <= 25) return BrakingAction::POOR;
    if (*coefficient <= 29) return BrakingAction::MEDIUM_POOR;
    if (*coefficient <= 35) return BrakingAction::MEDIUM;
    if (*coefficient <= 40) return BrakingAction::MEDIUM_GOOD;
    return BrakingAction::GOOD;
}

}  // namespace metafsimple

namespace metafsimple::detail {

class WarningLogger {
   public:
    WarningLogger() = delete;
    WarningLogger(std::vector<Report::Warning> &w) : warnings(&w) {}
    void setIdString(std::string id) { idStr = std::move(id); }
    void add(Report::Warning::Message message, std::string id) {
        warnings->push_back(Report::Warning{message, std::move(id)});
    }
    void add(Report::Warning::Message message) {
        add(message, idStr);
    }

   protected:
    std::vector<Report::Warning> *warnings = nullptr;
    std::string idStr;
};

////////////////////////////////////////////////////////////////////////////////

// Base class to provide means of setting various data in structures while
// checking whether these data are already set
class DataAdapter {
   public:
    DataAdapter() = delete;
    DataAdapter(WarningLogger *l) : logger(l) { assert(logger); }
    void log(Report::Warning::Message msg) { logger->add(msg); }
    WarningLogger *getLogger() { return logger; }

    template <typename T>
    bool setData(T &data, T value) {
        if (this->hasData(data)) {
            log(Report::Warning::Message::DUPLICATED_DATA);
            return false;
        }
        data = std::move(value);
        return true;
    }

    bool setData(DistanceRange &data, Distance value) {
        if (this->hasData(data.prevailing)) {
            log(Report::Warning::Message::DUPLICATED_DATA);
            return false;
        }
        data.prevailing = std::move(value);
        return true;
    }

    bool setData(DistanceRange &data,
                 Distance minValue,
                 Distance maxValue) {
        if (this->hasData(data.minimum) || this->hasData(data.maximum)) {
            log(Report::Warning::Message::DUPLICATED_DATA);
            return false;
        }
        data.minimum = std::move(minValue);
        data.maximum = std::move(maxValue);
        return true;
    }

    bool setData(Ceiling &data, Height value) {
        if (this->hasData(data.exact)) {
            log(Report::Warning::Message::DUPLICATED_DATA);
            return false;
        }
        data.exact = std::move(value);
        return true;
    }

    bool setData(Ceiling &data,
                 Height minValue,
                 Height maxValue) {
        if (this->hasData(data.minimum) || this->hasData(data.maximum)) {
            log(Report::Warning::Message::DUPLICATED_DATA);
            return false;
        }
        data.minimum = std::move(minValue);
        data.maximum = std::move(maxValue);
        return true;
    }

   private:
    WarningLogger *logger;

    static bool hasData(const bool &data) {
        return data;
    }
    static bool hasData(const std::optional<int> &data) {
        return data.has_value();
    }
    static bool hasData(const Time &data) {
        return (data.day.has_value() ||
                data.hour.has_value() ||
                data.minute.has_value());
    }
    static bool hasData(const Temperature &data) {
        return data.temperature.has_value();
    }
    static bool hasData(const Speed &data) {
        return data.speed.has_value();
    }
    static bool hasData(const Distance &data) {
        return data.distance.has_value();
    }
    static bool hasData(const Height &data) {
        return data.height.has_value();
    }
    static bool hasData(const Pressure &data) {
        return data.pressure.has_value();
    }
    static bool hasData(const Precipitation &data) {
        return data.amount.has_value();
    }
    static bool hasData(const WaveHeight &data) {
        return data.waveHeight.has_value();
    }
};

////////////////////////////////////////////////////////////////////////////////

// Converts Metaf's data types into metafsimple's structures
class BasicDataAdapter : DataAdapter {
   public:
    BasicDataAdapter(WarningLogger *l) : DataAdapter(l) {}

    // Conversion from the following metaf:: values to metafsimple:: value are
    // guaranteed to succeed

    inline static Runway runway(const metaf::Runway &rw);
    inline static Time time(const std::optional<::metaf::MetafTime> &t);
    inline static Temperature temperature(const metaf::Temperature &t);
    inline static Speed speed(const metaf::Speed &s);
    inline static Pressure pressure(const metaf::Pressure &p);
    inline static Precipitation precipitation(const metaf::Precipitation &p);
    inline static Height height(const metaf::Distance &d);
    inline static WaveHeight waveHeight(const metaf::WaveHeight &wh);

    inline static CloudLayer::Details
    cloudLayerDetails(metaf::CloudType::Type t);

    inline static CloudLayer::Amount
    cloudLayerAmount(metaf::CloudGroup::Amount a);

    inline static CardinalDirection
    cardinalDirection(const metaf::Direction &d);

    // metaf::Distance may represent value coded as DSNT or VC which mean range
    // of distances rather than the fixed distance value.
    // Thus conversion from metaf::Distance to metafsimple::DistanceRange is
    // guaranteed to succeed.
    // But conversion from metaf::Distance to metafsimple::Distance may result
    // in error (empty optional is returned).

    inline static DistanceRange distanceRange(const metaf::Distance &d);
    inline static std::optional<Distance> distance(const metaf::Distance &d);
    inline static std::optional<DistanceRange>
    distanceRange(const metaf::Distance &dmin,
                  const metaf::Distance &dmax);

    // Passing invalid combinations of Qualifier, Descritor and Weather is
    // theoretically possible (e.g. FZSQ), thus conversion is not guaranteed
    // to succeed. If no equivalent return type can be found, an empty optional
    // is returned.

    inline static std::optional<Weather>
    weather(const metaf::WeatherPhenomena &wp);

    inline static std::optional<Weather::Phenomena>
    weatherPhenomena(metaf::WeatherPhenomena::Qualifier q,
                     metaf::WeatherPhenomena::Descriptor d,
                     std::vector<metaf::WeatherPhenomena::Weather> v);

    inline static std::optional<Weather::Precipitation>
    weatherPrecipitation(metaf::WeatherPhenomena::Weather w);

    inline static std::optional<Weather::Phenomena>
    precipitationPhenomena(metaf::WeatherPhenomena::Qualifier q,
                           metaf::WeatherPhenomena::Descriptor d);

    inline static const int metersPerNauticalMile = 1852;
};

Runway BasicDataAdapter::runway(const metaf::Runway &r) {
    auto designator = [](metaf::Runway::Designator d) {
        switch (d) {
            case metaf::Runway::Designator::NONE:
                return Runway::Designator::NONE;
            case metaf::Runway::Designator::LEFT:
                return Runway::Designator::LEFT;
            case metaf::Runway::Designator::CENTER:
                return Runway::Designator::CENTER;
            case metaf::Runway::Designator::RIGHT:
                return Runway::Designator::RIGHT;
        }
    };
    return Runway{static_cast<int>(r.number()), designator(r.designator())};
}

Time BasicDataAdapter::time(const std::optional<::metaf::MetafTime> &t) {
    if (!t.has_value()) return Time();
    return Time{t->day(), t->hour(), t->minute()};
}

Temperature BasicDataAdapter::temperature(const metaf::Temperature &t) {
    if (!t.temperature().has_value()) return Temperature();
    if (t.isPrecise()) {
        const auto tval = t.toUnit(metaf::Temperature::Unit::C);
        assert(tval.has_value());
        return Temperature{std::floor(*tval * 10), Temperature::Unit::TENTH_C};
    }
    const auto temp = t.temperature();
    assert(temp.has_value());
    if (!(*temp) && t.isFreezing())  // For value coded as M00 return -0.2 C
        return Temperature{-2, Temperature::Unit::TENTH_C};
    return Temperature{temp, Temperature::Unit::C};
}

Speed BasicDataAdapter::speed(const metaf::Speed &s) {
    auto convertUnit = [](metaf::Speed::Unit u) {
        switch (u) {
            case metaf::Speed::Unit::KNOTS:
                return Speed::Unit::KT;
            case metaf::Speed::Unit::METERS_PER_SECOND:
                return Speed::Unit::MPS;
            case metaf::Speed::Unit::KILOMETERS_PER_HOUR:
                return Speed::Unit::KMH;
            case metaf::Speed::Unit::MILES_PER_HOUR:
                return Speed::Unit::MPH;
        }
    };
    return Speed{s.speed(), convertUnit(s.unit())};
}

Pressure BasicDataAdapter::pressure(const metaf::Pressure &p) {
    auto convertUnit = [](metaf::Pressure::Unit u) {
        switch (u) {
            case metaf::Pressure::Unit::HECTOPASCAL:
                return Pressure::Unit::HPA;
            case metaf::Pressure::Unit::INCHES_HG:
                return Pressure::Unit::HUNDREDTHS_IN_HG;
            case metaf::Pressure::Unit::MM_HG:
                return Pressure::Unit::MM_HG;
        }
    };
    if (!p.pressure().has_value()) return Pressure();
    Pressure result{std::floor(*p.pressure()), convertUnit(p.unit())};
    if (result.unit == Pressure::Unit::HUNDREDTHS_IN_HG)
        result.pressure = std::floor(*p.pressure() * 100.0);
    return result;
}

Precipitation BasicDataAdapter::precipitation(const metaf::Precipitation &p) {
    auto convertUnit = [](metaf::Precipitation::Unit u) {
        switch (u) {
            case metaf::Precipitation::Unit::MM:
                return Precipitation::Unit::MM;
            case metaf::Precipitation::Unit::INCHES:
                return Precipitation::Unit::HUNDREDTHS_IN;
        }
    };
    if (!p.amount().has_value()) return Precipitation();
    Precipitation pr{std::floor(*p.amount()), convertUnit(p.unit())};
    if (pr.unit == Precipitation::Unit::HUNDREDTHS_IN && !(*pr.amount % 100)) {
        pr.amount = *pr.amount / 100;
        pr.unit = Precipitation::Unit::IN;
    }
    return pr;
}

CardinalDirection
BasicDataAdapter::cardinalDirection(const metaf::Direction &d) {
    switch (d.cardinal()) {
        case metaf::Direction::Cardinal::NOT_REPORTED:
        case metaf::Direction::Cardinal::VRB:
        case metaf::Direction::Cardinal::NDV:
            return CardinalDirection::NOT_SPECIFIED;
        case metaf::Direction::Cardinal::N:
        case metaf::Direction::Cardinal::TRUE_N:
            return CardinalDirection::N;
        case metaf::Direction::Cardinal::S:
        case metaf::Direction::Cardinal::TRUE_S:
            return CardinalDirection::S;
        case metaf::Direction::Cardinal::W:
        case metaf::Direction::Cardinal::TRUE_W:
            return CardinalDirection::W;
        case metaf::Direction::Cardinal::E:
        case metaf::Direction::Cardinal::TRUE_E:
            return CardinalDirection::W;
        case metaf::Direction::Cardinal::NW:
            return CardinalDirection::NW;
        case metaf::Direction::Cardinal::NE:
            return CardinalDirection::NE;
        case metaf::Direction::Cardinal::SW:
            return CardinalDirection::SW;
        case metaf::Direction::Cardinal::SE:
            return CardinalDirection::SE;
        case metaf::Direction::Cardinal::OHD:
            return CardinalDirection::OVERHEAD;
        case metaf::Direction::Cardinal::ALQDS:
            return CardinalDirection::ALL_QUADRANTS;
        case metaf::Direction::Cardinal::UNKNOWN:
            return CardinalDirection::UNKNOWN;
    };
}

Height BasicDataAdapter::height(const metaf::Distance &d) {
    const auto df = d.toUnit(metaf::Distance::Unit::FEET);
    if (!df.has_value()) return Height();
    return Height{std::floor(*df), Height::Unit::FEET};
}

WaveHeight BasicDataAdapter::waveHeight(const metaf::WaveHeight &wh) {
    const auto whm = wh.toUnit(metaf::WaveHeight::Unit::METERS);
    if (!whm.has_value()) return WaveHeight();
    return WaveHeight{std::floor(*whm / 10.0), WaveHeight::Unit::DECIMETERS};
}

CloudLayer::Amount
BasicDataAdapter::cloudLayerAmount(metaf::CloudGroup::Amount a) {
    switch (a) {
        case metaf::CloudGroup::Amount::NOT_REPORTED:
        case metaf::CloudGroup::Amount::NSC:
        case metaf::CloudGroup::Amount::NCD:
        case metaf::CloudGroup::Amount::NONE_CLR:
        case metaf::CloudGroup::Amount::NONE_SKC:
        case metaf::CloudGroup::Amount::OBSCURED:
            return CloudLayer::Amount::UNKNOWN;
        case metaf::CloudGroup::Amount::FEW:
            return CloudLayer::Amount::FEW;
        case metaf::CloudGroup::Amount::SCATTERED:
            return CloudLayer::Amount::SCATTERED;
        case metaf::CloudGroup::Amount::BROKEN:
            return CloudLayer::Amount::BROKEN;
        case metaf::CloudGroup::Amount::OVERCAST:
            return CloudLayer::Amount::OVERCAST;
        case metaf::CloudGroup::Amount::VARIABLE_FEW_SCATTERED:
            return CloudLayer::Amount::VARIABLE_FEW_SCATTERED;
        case metaf::CloudGroup::Amount::VARIABLE_SCATTERED_BROKEN:
            return CloudLayer::Amount::VARIABLE_SCATTERED_BROKEN;
        case metaf::CloudGroup::Amount::VARIABLE_BROKEN_OVERCAST:
            return CloudLayer::Amount::VARIABLE_BROKEN_OVERCAST;
    }
}

CloudLayer::Details
BasicDataAdapter::cloudLayerDetails(metaf::CloudType::Type t) {
    switch (t) {
        case metaf::CloudType::Type::NOT_REPORTED:
            return CloudLayer::Details::UNKNOWN;
        case metaf::CloudType::Type::CUMULONIMBUS:
            return CloudLayer::Details::CUMULONIMBUS;
        case metaf::CloudType::Type::TOWERING_CUMULUS:
            return CloudLayer::Details::TOWERING_CUMULUS;
        case metaf::CloudType::Type::CUMULUS:
            return CloudLayer::Details::CUMULUS;
        case metaf::CloudType::Type::CUMULUS_FRACTUS:
            return CloudLayer::Details::CUMULUS_FRACTUS;
        case metaf::CloudType::Type::STRATOCUMULUS:
            return CloudLayer::Details::STRATOCUMULUS;
        case metaf::CloudType::Type::NIMBOSTRATUS:
            return CloudLayer::Details::NIMBOSTRATUS;
        case metaf::CloudType::Type::STRATUS:
            return CloudLayer::Details::STRATUS;
        case metaf::CloudType::Type::STRATUS_FRACTUS:
            return CloudLayer::Details::STRATUS_FRACTUS;
        case metaf::CloudType::Type::ALTOSTRATUS:
            return CloudLayer::Details::ALTOSTRATUS;
        case metaf::CloudType::Type::ALTOCUMULUS:
            return CloudLayer::Details::ALTOCUMULUS;
        case metaf::CloudType::Type::ALTOCUMULUS_CASTELLANUS:
            return CloudLayer::Details::ALTOCUMULUS_CASTELLANUS;
        case metaf::CloudType::Type::CIRRUS:
            return CloudLayer::Details::CIRRUS;
        case metaf::CloudType::Type::CIRROSTRATUS:
            return CloudLayer::Details::CIRROSTRATUS;
        case metaf::CloudType::Type::CIRROCUMULUS:
            return CloudLayer::Details::CIRROCUMULUS;
        case metaf::CloudType::Type::BLOWING_SNOW:
            return CloudLayer::Details::BLOWING_SNOW;
        case metaf::CloudType::Type::BLOWING_DUST:
            return CloudLayer::Details::BLOWING_DUST;
        case metaf::CloudType::Type::BLOWING_SAND:
            return CloudLayer::Details::BLOWING_SAND;
        case metaf::CloudType::Type::ICE_CRYSTALS:
            return CloudLayer::Details::ICE_CRYSTALS;
        case metaf::CloudType::Type::RAIN:
            return CloudLayer::Details::RAIN;
        case metaf::CloudType::Type::DRIZZLE:
            return CloudLayer::Details::DRIZZLE;
        case metaf::CloudType::Type::SNOW:
            return CloudLayer::Details::SNOW;
        case metaf::CloudType::Type::ICE_PELLETS:
            return CloudLayer::Details::ICE_PELLETS;
        case metaf::CloudType::Type::SMOKE:
            return CloudLayer::Details::SMOKE;
        case metaf::CloudType::Type::FOG:
            return CloudLayer::Details::FOG;
        case metaf::CloudType::Type::MIST:
            return CloudLayer::Details::MIST;
        case metaf::CloudType::Type::HAZE:
            return CloudLayer::Details::HAZE;
        case metaf::CloudType::Type::VOLCANIC_ASH:
            return CloudLayer::Details::VOLCANIC_ASH;
    }
}

DistanceRange BasicDataAdapter::distanceRange(const metaf::Distance &d) {
    Distance result;
    switch (d.modifier()) {
        case metaf::Distance::Modifier::VICINITY:
            return DistanceRange{Distance(),
                                 Distance{Distance::Details::EXACTLY,
                                          5 * metersPerNauticalMile,
                                          Distance::Unit::METERS},
                                 Distance{Distance::Details::EXACTLY,
                                          10 * metersPerNauticalMile,
                                          Distance::Unit::METERS}};
        case metaf::Distance::Modifier::DISTANT:
            return DistanceRange{Distance(),
                                 Distance{Distance::Details::EXACTLY,
                                          10 * metersPerNauticalMile,
                                          Distance::Unit::METERS},
                                 Distance{Distance::Details::EXACTLY,
                                          30 * metersPerNauticalMile,
                                          Distance::Unit::METERS}};
        case metaf::Distance::Modifier::NONE:
            result.details = Distance::Details::EXACTLY;
            break;
        case metaf::Distance::Modifier::LESS_THAN:
            result.details = Distance::Details::LESS_THAN;
            break;
        case metaf::Distance::Modifier::MORE_THAN:
            result.details = Distance::Details::MORE_THAN;
            break;
    };
    if (!d.distance().has_value()) return DistanceRange();
    result.distance = std::floor(*d.distance());
    switch (d.unit()) {
        case metaf::Distance::Unit::METERS:
            result.unit = Distance::Unit::METERS;
            break;
        case metaf::Distance::Unit::FEET:
            result.unit = Distance::Unit::FEET;
            break;
        case metaf::Distance::Unit::STATUTE_MILES:
            result.unit = Distance::Unit::STATUTE_MILES;
            const auto integer = *result.distance;
            const auto fraction = std::floor((*d.distance() - integer) * 16);
            if (fraction) {
                result.unit = Distance::Unit::STATUTE_MILE_1_16S;
                result.distance = integer * 16 + fraction;
            }
            break;
    }
    return DistanceRange{result, Distance(), Distance()};
}

std::optional<DistanceRange>
BasicDataAdapter::distanceRange(const metaf::Distance &min,
                                const metaf::Distance &max) {
    const auto dmin = distance(min);
    const auto dmax = distance(max);
    if (!dmin.has_value() || !dmax.has_value())
        return std::optional<DistanceRange>();
    return DistanceRange{Distance(), *dmin, *dmax};
}

std::optional<Distance> BasicDataAdapter::distance(const metaf::Distance &d) {
    return distanceRange(d).prevailing;
}

std::optional<Weather::Phenomena>
BasicDataAdapter::weatherPhenomena(metaf::WeatherPhenomena::Qualifier q,
                                   metaf::WeatherPhenomena::Descriptor d,
                                   std::vector<metaf::WeatherPhenomena::
                                                   Weather>
                                       v) {
    // VCSH is special case: SH cannot be used alone without VC
    // The rest of phenomena used with VC qualifier may be used without VC too
    if (q == metaf::WeatherPhenomena::Qualifier::VICINITY &&
        d == metaf::WeatherPhenomena::Descriptor::SHOWERS &&
        v.empty())
        return Weather::Phenomena::PRECIPITATION;
    if (q == metaf::WeatherPhenomena::Qualifier::RECENT ||
        q == metaf::WeatherPhenomena::Qualifier::VICINITY)
        q = metaf::WeatherPhenomena::Qualifier::NONE;
    struct KnownPhenomena {
        metaf::WeatherPhenomena::Qualifier qualifier;
        metaf::WeatherPhenomena::Descriptor descriptor;
        std::vector<metaf::WeatherPhenomena::Weather> weather;
        Weather::Phenomena phenomena;
    };
    static const std::vector<KnownPhenomena> knownPhenomena = {
        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::SHALLOW,
         {metaf::WeatherPhenomena::Weather::FOG},
         Weather::Phenomena::SHALLOW_FOG},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::PARTIAL,
         {metaf::WeatherPhenomena::Weather::FOG},
         Weather::Phenomena::PARTIAL_FOG},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::PATCHES,
         {metaf::WeatherPhenomena::Weather::FOG},
         Weather::Phenomena::PATCHES_FOG},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::FREEZING,
         {metaf::WeatherPhenomena::Weather::FOG},
         Weather::Phenomena::FREEZING_FOG},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::FOG},
         Weather::Phenomena::FOG},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::LOW_DRIFTING,
         {metaf::WeatherPhenomena::Weather::DUST},
         Weather::Phenomena::DRIFTING_DUST},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::BLOWING,
         {metaf::WeatherPhenomena::Weather::DUST},
         Weather::Phenomena::BLOWING_DUST},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::DUST},
         Weather::Phenomena::DUST},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::LOW_DRIFTING,
         {metaf::WeatherPhenomena::Weather::SAND},
         Weather::Phenomena::DRIFTING_SAND},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::BLOWING,
         {metaf::WeatherPhenomena::Weather::SAND},
         Weather::Phenomena::BLOWING_SAND},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::SAND},
         Weather::Phenomena::SAND},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::LOW_DRIFTING,
         {metaf::WeatherPhenomena::Weather::SNOW},
         Weather::Phenomena::DRIFTING_SNOW},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::BLOWING,
         {metaf::WeatherPhenomena::Weather::SNOW},
         Weather::Phenomena::BLOWING_SNOW},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::BLOWING,
         {metaf::WeatherPhenomena::Weather::SPRAY},
         Weather::Phenomena::BLOWING_SPRAY},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::THUNDERSTORM,
         {},
         Weather::Phenomena::THUNDERSTORM},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::ICE_CRYSTALS},
         Weather::Phenomena::ICE_CRYSTALS},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::MIST},
         Weather::Phenomena::MIST},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::HAZE},
         Weather::Phenomena::HAZE},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::SMOKE},
         Weather::Phenomena::SMOKE},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::VOLCANIC_ASH},
         Weather::Phenomena::VOLCANIC_ASH},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::DUST_WHIRLS},
         Weather::Phenomena::DUST_WHIRLS},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::SQUALLS},
         Weather::Phenomena::SQUALLS},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::FUNNEL_CLOUD},
         Weather::Phenomena::FUNNEL_CLOUD},

        {metaf::WeatherPhenomena::Qualifier::HEAVY,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::FUNNEL_CLOUD},
         Weather::Phenomena::TORNADO},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::DUSTSTORM},
         Weather::Phenomena::DUST_STORM},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::SANDSTORM},
         Weather::Phenomena::SAND_STORM},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::DUSTSTORM,
          metaf::WeatherPhenomena::Weather::SANDSTORM},
         Weather::Phenomena::DUST_SAND_STORM},

        {metaf::WeatherPhenomena::Qualifier::NONE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::SANDSTORM,
          metaf::WeatherPhenomena::Weather::DUSTSTORM},
         Weather::Phenomena::DUST_SAND_STORM},

        {metaf::WeatherPhenomena::Qualifier::HEAVY,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::DUSTSTORM},
         Weather::Phenomena::HEAVY_DUST_STORM},

        {metaf::WeatherPhenomena::Qualifier::HEAVY,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::SANDSTORM},
         Weather::Phenomena::HEAVY_SAND_STORM},

        {metaf::WeatherPhenomena::Qualifier::HEAVY,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::DUSTSTORM,
          metaf::WeatherPhenomena::Weather::SANDSTORM},
         Weather::Phenomena::HEAVY_DUST_SAND_STORM},

        {metaf::WeatherPhenomena::Qualifier::HEAVY,
         metaf::WeatherPhenomena::Descriptor::NONE,
         {metaf::WeatherPhenomena::Weather::SANDSTORM,
          metaf::WeatherPhenomena::Weather::DUSTSTORM},
         Weather::Phenomena::HEAVY_DUST_SAND_STORM}};
    for (const auto &ph : knownPhenomena) {
        if (ph.qualifier == q && ph.descriptor == d && ph.weather == v)
            return ph.phenomena;
    }
    return std::optional<Weather::Phenomena>();
}

std::optional<Weather::Precipitation>
BasicDataAdapter::weatherPrecipitation(metaf::WeatherPhenomena::Weather w) {
    switch (w) {
        case metaf::WeatherPhenomena::Weather::DRIZZLE:
            return Weather::Precipitation::DRIZZLE;
        case metaf::WeatherPhenomena::Weather::RAIN:
            return Weather::Precipitation::RAIN;
        case metaf::WeatherPhenomena::Weather::SNOW:
            return Weather::Precipitation::SNOW;
        case metaf::WeatherPhenomena::Weather::ICE_PELLETS:
            return Weather::Precipitation::ICE_PELLETS;
        case metaf::WeatherPhenomena::Weather::SNOW_GRAINS:
            return Weather::Precipitation::SNOW_GRAINS;
        case metaf::WeatherPhenomena::Weather::HAIL:
            return Weather::Precipitation::HAIL;
        case metaf::WeatherPhenomena::Weather::SMALL_HAIL:
            return Weather::Precipitation::SMALL_HAIL;
        case metaf::WeatherPhenomena::Weather::UNDETERMINED:
            return Weather::Precipitation::UNDETERMINED;
        default:
            return std::optional<Weather::Precipitation>();
    }
}

std::optional<Weather::Phenomena>
BasicDataAdapter::precipitationPhenomena(
    metaf::WeatherPhenomena::Qualifier q,
    metaf::WeatherPhenomena::Descriptor d) {
    struct KnownPhenomena {
        metaf::WeatherPhenomena::Qualifier qualifier;
        metaf::WeatherPhenomena::Descriptor descriptor;
        Weather::Phenomena phenomena;
    };
    std::vector<KnownPhenomena> knownPhenomena{
        {metaf::WeatherPhenomena::Qualifier::LIGHT,
         metaf::WeatherPhenomena::Descriptor::NONE,
         Weather::Phenomena::PRECIPITATION_LIGHT},

        {metaf::WeatherPhenomena::Qualifier::LIGHT,
         metaf::WeatherPhenomena::Descriptor::FREEZING,
         Weather::Phenomena::FREEZING_PRECIPITATION_LIGHT},

        {metaf::WeatherPhenomena::Qualifier::LIGHT,
         metaf::WeatherPhenomena::Descriptor::THUNDERSTORM,
         Weather::Phenomena::THUNDERSTORM_PRECIPITATION_LIGHT},

        {metaf::WeatherPhenomena::Qualifier::LIGHT,
         metaf::WeatherPhenomena::Descriptor::SHOWERS,
         Weather::Phenomena::SHOWERY_PRECIPITATION_LIGHT},

        {metaf::WeatherPhenomena::Qualifier::MODERATE,
         metaf::WeatherPhenomena::Descriptor::NONE,
         Weather::Phenomena::PRECIPITATION_MODERATE},

        {metaf::WeatherPhenomena::Qualifier::MODERATE,
         metaf::WeatherPhenomena::Descriptor::FREEZING,
         Weather::Phenomena::FREEZING_PRECIPITATION_MODERATE},

        {metaf::WeatherPhenomena::Qualifier::MODERATE,
         metaf::WeatherPhenomena::Descriptor::THUNDERSTORM,
         Weather::Phenomena::THUNDERSTORM_PRECIPITATION_MODERATE},

        {metaf::WeatherPhenomena::Qualifier::MODERATE,
         metaf::WeatherPhenomena::Descriptor::SHOWERS,
         Weather::Phenomena::SHOWERY_PRECIPITATION_MODERATE},

        {metaf::WeatherPhenomena::Qualifier::HEAVY,
         metaf::WeatherPhenomena::Descriptor::NONE,
         Weather::Phenomena::PRECIPITATION_HEAVY},

        {metaf::WeatherPhenomena::Qualifier::HEAVY,
         metaf::WeatherPhenomena::Descriptor::FREEZING,
         Weather::Phenomena::FREEZING_PRECIPITATION_HEAVY},

        {metaf::WeatherPhenomena::Qualifier::HEAVY,
         metaf::WeatherPhenomena::Descriptor::THUNDERSTORM,
         Weather::Phenomena::THUNDERSTORM_PRECIPITATION_HEAVY},

        {metaf::WeatherPhenomena::Qualifier::HEAVY,
         metaf::WeatherPhenomena::Descriptor::SHOWERS,
         Weather::Phenomena::SHOWERY_PRECIPITATION_HEAVY},
    };
    for (const auto &ph : knownPhenomena) {
        if (ph.qualifier == q && ph.descriptor == d) return ph.phenomena;
    }
    return std::optional<Weather::Phenomena>();
}

std::optional<Weather>
BasicDataAdapter::weather(const metaf::WeatherPhenomena &wp) {
    if (const auto w = weatherPhenomena(wp.qualifier(),
                                        wp.descriptor(),
                                        wp.weather());
        w.has_value()) return Weather{*w, {}};
    const auto w = precipitationPhenomena(wp.qualifier(), wp.descriptor());
    if (!w.has_value()) return std::optional<Weather>();
    Weather result{*w, {}};
    for (const auto wpw : wp.weather()) {
        const auto pr = weatherPrecipitation(wpw);
        if (!pr.has_value()) return std::optional<Weather>();
        result.precipitation.insert(*pr);
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////

// Set report metadata in metafsimple::Report and metafsimple::Station
class MetadataAdapter : DataAdapter {
   public:
    MetadataAdapter(Report &r, Station &s, WarningLogger *l) : DataAdapter(l),
                                                               report(&r),
                                                               station(&s) {}
    inline void setReportType(metaf::ReportType t, bool speci);
    inline void setReportError(metaf::ReportError e);
    inline void setLocation(const std::string &location);
    inline void setAttributes(bool nil,
                              bool cnl,
                              bool cor,
                              bool amd,
                              bool automated,
                              bool nospeci,
                              bool maintenance,
                              std::optional<unsigned int> corNum);
    inline void setAutoType(bool ao1, bool ao2, bool ao1a, bool ao2a);
    inline void setReportTime(std::optional<metaf::MetafTime> t);
    inline void setApplicableTime(std::optional<metaf::MetafTime> from,
                                  std::optional<metaf::MetafTime> until);

   private:
    Report *report;
    Station *station;
};

void MetadataAdapter::setReportType(metaf::ReportType t, bool speci) {
    switch (t) {
        case metaf::ReportType::UNKNOWN:
            report->type = Report::Type::ERROR;
            report->error = Report::Error::UNKNOWN_REPORT_TYPE;
            break;
        case metaf::ReportType::METAR:
            report->type = Report::Type::METAR;
            if (speci) report->type = Report::Type::SPECI;
            break;
        case metaf::ReportType::TAF:
            report->type = Report::Type::TAF;
            if (speci) log(Report::Warning::Message::SPECI_IN_TAF);
            break;
    }
}

void MetadataAdapter::setReportError(metaf::ReportError e) {
    auto convertError = [](metaf::ReportError e) {
        switch (e) {
            case metaf::ReportError::NONE:
                return Report::Error::NO_ERROR;
            case metaf::ReportError::EMPTY_REPORT:
                return Report::Error::EMPTY_REPORT;
            case metaf::ReportError::EXPECTED_REPORT_TYPE_OR_LOCATION:
            case metaf::ReportError::EXPECTED_LOCATION:
            case metaf::ReportError::EXPECTED_REPORT_TIME:
            case metaf::ReportError::EXPECTED_TIME_SPAN:
                return Report::Error::REPORT_HEADER_FORMAT;
            case metaf::ReportError::UNEXPECTED_REPORT_END:
                return Report::Error::UNEXPECTED_REPORT_END;
            case metaf::ReportError::UNEXPECTED_GROUP_AFTER_NIL:
            case metaf::ReportError::UNEXPECTED_GROUP_AFTER_CNL:
            case metaf::ReportError::UNEXPECTED_NIL_OR_CNL_IN_REPORT_BODY:
            case metaf::ReportError::CNL_ALLOWED_IN_TAF_ONLY:
                return Report::Error::NIL_OR_CNL_FORMAT;
            case metaf::ReportError::AMD_ALLOWED_IN_TAF_ONLY:
            case metaf::ReportError::
                MAINTENANCE_INDICATOR_ALLOWED_IN_METAR_ONLY:
                return Report::Error::GROUP_NOT_ALLOWED;
            case metaf::ReportError::REPORT_TOO_LARGE:
                return Report::Error::REPORT_TOO_LARGE;
        }
    };
    report->error = convertError(e);
}

void MetadataAdapter::setLocation(const std::string &location) {
    if (!station->icaoCode.empty() && station->icaoCode != location) {
        log(Report::Warning::Message::INCONSISTENT_DATA);
        return;
    }
    station->icaoCode = location;
}

void MetadataAdapter::setAttributes(bool nil,
                                    bool cnl,
                                    bool cor,
                                    bool amd,
                                    bool automated,
                                    bool nospeci,
                                    bool maintenance,
                                    std::optional<unsigned int> corNum) {
    if (nil && cnl) {
        log(Report::Warning::Message::BOTH_NIL_AND_CNL);
        cnl = false;
    }
    if (amd && cor) {
        log(Report::Warning::Message::BOTH_AMD_AND_COR);
        amd = false;
    }
    if (!cor && corNum.has_value() && *corNum) {
        log(Report::Warning::Message::INCONSISTENT_CORRECTION_NUMBER);
        corNum = std::optional<unsigned int>();
    }
    switch (report->type) {
        case Report::Type::METAR:
        case Report::Type::SPECI:
            if (amd) {
                log(Report::Warning::Message::AMD_IN_NON_TAF);
                amd = false;
            }
            if (cnl) {
                log(Report::Warning::Message::CNL_IN_NON_TAF);
                cnl = false;
            }
            break;
        case Report::Type::TAF:
            break;
        case Report::Type::ERROR:
            return;
    }
    report->missing = nil;
    report->cancelled = cnl;
    report->correctional = cor;
    report->amended = amd;
    station->noSpeciReports = nospeci;
    report->automated = automated;
    station->requiresMaintenance = maintenance;
    if (corNum.has_value()) report->correctionNumber = *corNum;
}

void MetadataAdapter::setAutoType(bool ao1, bool ao2, bool ao1a, bool ao2a) {
    auto autoTypeValid = [=](bool ao1, bool ao2, bool ao1a, bool ao2a) {
        if (ao1 && (ao2 || ao1a || ao2a)) return false;
        if (ao2 && (ao1a || ao2a)) return false;
        if (ao1a && ao2a) return false;
        return true;
    };
    if (!autoTypeValid(ao1, ao2, ao1a, ao2a)) {
        log(Report::Warning::Message::INVALID_AUTOTYPE);
        station->autoType = Station::AutoType::NONE;
        return;
    }
    // At this point it is guaranteed that maximum one autotype flag is set
    station->autoType = Station::AutoType::NONE;
    if (ao1) station->autoType = Station::AutoType::AO1;
    if (ao2) station->autoType = Station::AutoType::AO2;
    if (ao1a) station->autoType = Station::AutoType::AO1A;
    if (ao2a) station->autoType = Station::AutoType::AO2A;
}

void MetadataAdapter::setReportTime(std::optional<metaf::MetafTime> t) {
    const bool isMetar = report->type == Report::Type::SPECI ||
                         report->type == Report::Type::METAR;
    if (isMetar && !t.has_value())
        log(Report::Warning::Message::NO_REPORT_TIME_IN_METAR);
    report->reportTime = BasicDataAdapter::time(t);
}

void MetadataAdapter::setApplicableTime(std::optional<metaf::MetafTime> from,
                                        std::optional<metaf::MetafTime> until) {
    if (report->type != Report::Type::TAF) {
        if (from.has_value() || until.has_value())
            log(Report::Warning::Message::APPLICABLE_TIME_IN_METAR);
        return;
    }
    if (!from.has_value() || !until.has_value()) {
        log(Report::Warning::Message::NO_APPLICABLE_TIME_IN_TAF);
        return;
    }
    report->applicableFrom = BasicDataAdapter::time(from);
    report->applicableUntil = BasicDataAdapter::time(until);
}

// Set data of Station struct : missing data (e.g. RVRNO or WX MISG), and
// NDV flag which is specified in visibility groups (e.g. 9999NDV)
class StationDataAdapter : DataAdapter {
   public:
    StationDataAdapter(Station &s, WarningLogger *l) : DataAdapter(l),
                                                       station(&s) {}
    inline void addMissingData(Station::MissingData md);
    inline void addChino(std::optional<metaf::Runway> rw,
                         std::optional<metaf::Direction> d);
    inline void addVisno(std::optional<metaf::Runway> rw,
                         std::optional<metaf::Direction> d);
    inline void setNdv();

   private:
    inline void setChinoVisno(std::set<Runway> &runways,
                              std::optional<metaf::Runway> rw,
                              std::set<CardinalDirection> &direction,
                              std::optional<metaf::Direction> d);
    Station *station = nullptr;
};

void StationDataAdapter::addMissingData(Station::MissingData md) {
    assert(station);
    if (station->missingData.count(md) &&
        md != Station::MissingData::CHINO_RUNWAY &&
        md != Station::MissingData::VISNO_RUNWAY &&
        md != Station::MissingData::CHINO_DIRECTION &&
        md != Station::MissingData::CHINO_RUNWAY) {
        log(Report::Warning::Message::DUPLICATED_DATA);
    }
    station->missingData.insert(md);
}

void StationDataAdapter::addChino(std::optional<metaf::Runway> rw,
                                  std::optional<metaf::Direction> d) {
    assert(station);
    if (!rw.has_value() && !d.has_value())
        addMissingData(Station::MissingData::CHINO);
    if (rw.has_value()) addMissingData(Station::MissingData::CHINO_RUNWAY);
    if (d.has_value()) addMissingData(Station::MissingData::CHINO_DIRECTION);
    setChinoVisno(station->runwaysNoCeilingData, rw,
                  station->directionsNoCeilingData, d);
}

void StationDataAdapter::addVisno(std::optional<metaf::Runway> rw,
                                  std::optional<metaf::Direction> d) {
    assert(station);
    if (!rw.has_value() && !d.has_value())
        addMissingData(Station::MissingData::VISNO);
    if (rw.has_value()) addMissingData(Station::MissingData::VISNO_RUNWAY);
    if (d.has_value()) addMissingData(Station::MissingData::VISNO_DIRECTION);
    setChinoVisno(station->runwaysNoVisData, rw,
                  station->directionsNoVisData, d);
}

void StationDataAdapter::setChinoVisno(std::set<Runway> &runways,
                                       std::optional<metaf::Runway> rw,
                                       std::set<CardinalDirection> &directions,
                                       std::optional<metaf::Direction> d) {
    if (rw.has_value()) {
        const auto r = BasicDataAdapter::runway(*rw);
        if (!runways.count(r)) {
            log(Report::Warning::Message::DUPLICATED_DATA);
        } else {
            runways.insert(r);
        }
    }
    if (d.has_value()) {
        const auto dir = BasicDataAdapter::cardinalDirection(*d);
        if (!directions.count(dir)) {
            log(Report::Warning::Message::DUPLICATED_DATA);
        } else {
            directions.insert(dir);
        }
    }
}

void StationDataAdapter::setNdv() {
    assert(station);
    setData<bool>(station->noVisDirectionalVariation, true);
}

////////////////////////////////////////////////////////////////////////////////

// Set data of essential block repeated in METAR report body and in trends:
// surface wind, prevailing visibility, cloud layers, weather phenomena
class EssentialsAdapter : DataAdapter {
   public:
    EssentialsAdapter(Essentials &e, WarningLogger *l) : DataAdapter(l),
                                                         essentials(&e) {}
    static inline bool isEmpty(const Essentials &e);
    inline void setCavok();
    inline void setSurfaceWind(metaf::Direction dir,
                               metaf::Speed windSpeed,
                               metaf::Speed gustSpeed,
                               metaf::Direction varSecBegin,
                               metaf::Direction verSecEnd);
    inline void setSurfaceWindCalm();
    inline bool hasSurfaceWind() const;
    inline void setVisibility(metaf::Distance vis);
    inline void
    setSkyCondition(metaf::CloudGroup::Amount a,
                    metaf::Distance height = metaf::Distance(),
                    metaf::CloudGroup::ConvectiveType convType =
                        metaf::CloudGroup::ConvectiveType::NOT_REPORTED);
    inline void setVerticalVisibility(metaf::Distance vv);
    inline void addWeatherPhenomena(const metaf::WeatherPhenomena &wp);
    inline void setNsw();
    inline bool hasNsw() const;
    inline static Essentials::SkyCondition
    skyCondition(metaf::CloudGroup::Amount a);
    inline static CloudLayer::Details
    cloudLayerDetail(metaf::CloudGroup::ConvectiveType ct);

   private:
    Essentials *essentials;
};

bool EssentialsAdapter::isEmpty(const Essentials &e) {
    return !e.windDirectionDegrees.has_value() &&
           !e.windDirectionVariable &&
           !e.windDirectionVarFromDegrees.has_value() &&
           !e.windDirectionVarToDegrees.has_value() &&
           !e.windSpeed.speed.has_value() &&
           !e.gustSpeed.speed.has_value() &&
           !e.windCalm &&
           !e.visibility.distance.has_value() &&
           !e.cavok &&
           e.skyCondition == Essentials::SkyCondition::UNKNOWN &&
           e.cloudLayers.empty() &&
           !e.verticalVisibility.height.has_value() &&
           e.weather.empty();
}

void EssentialsAdapter::setCavok() {
    assert(essentials);
    if (essentials->visibility.distance.has_value() ||
        essentials->skyCondition != Essentials::SkyCondition::UNKNOWN ||
        essentials->cavok) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    const auto vis =
        BasicDataAdapter::distance(metaf::Distance::cavokVisibility());
    assert(vis.has_value());
    essentials->cavok = true;
    essentials->visibility = *vis;
    essentials->skyCondition = Essentials::SkyCondition::CAVOK;
}

void EssentialsAdapter::setSurfaceWind(metaf::Direction dir,
                                       metaf::Speed windSpeed,
                                       metaf::Speed gustSpeed,
                                       metaf::Direction varSecBegin,
                                       metaf::Direction varSecEnd) {
    assert(essentials);
    if (hasSurfaceWind()) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    essentials->windDirectionDegrees = dir.degrees();
    if (dir.type() == metaf::Direction::Type::VARIABLE)
        essentials->windDirectionVariable = true;
    if (varSecBegin.degrees().has_value() ^ varSecEnd.degrees().has_value()) {
        log(Report::Warning::Message::INVALID_DIRECTION_SECTOR);
    } else {
        essentials->windDirectionVarFromDegrees = varSecBegin.degrees();
        essentials->windDirectionVarToDegrees = varSecEnd.degrees();
    }
    essentials->windSpeed = BasicDataAdapter::speed(windSpeed);
    essentials->gustSpeed = BasicDataAdapter::speed(gustSpeed);
}

void EssentialsAdapter::setSurfaceWindCalm() {
    assert(essentials);
    if (hasSurfaceWind()) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    essentials->windCalm = true;
}

bool EssentialsAdapter::hasSurfaceWind() const {
    assert(essentials);
    return (essentials->windDirectionDegrees.has_value() ||
            essentials->windDirectionVarFromDegrees.has_value() ||
            essentials->windDirectionVarToDegrees.has_value() ||
            essentials->windSpeed.speed.has_value() ||
            essentials->gustSpeed.speed.has_value() ||
            essentials->windCalm);
}

void EssentialsAdapter::setVisibility(metaf::Distance vis) {
    const auto v = BasicDataAdapter::distance(vis);
    if (!v.has_value()) {
        log(Report::Warning::Message::INVALID_DISTANCE_RANGE);
        return;
    }
    assert(essentials);
    setData<Distance>(essentials->visibility, *v);
}

void EssentialsAdapter::setSkyCondition(metaf::CloudGroup::Amount a,
                                        metaf::Distance height,
                                        metaf::CloudGroup::ConvectiveType
                                            convType) {
    switch (essentials->skyCondition) {
        case Essentials::SkyCondition::UNKNOWN:
            essentials->skyCondition = skyCondition(a);
            break;
        case Essentials::SkyCondition::CLOUDS:
            if (skyCondition(a) == essentials->skyCondition) {
                // TODO: check for duplicate cloud layer height?
                essentials->cloudLayers.push_back(CloudLayer{
                    BasicDataAdapter::cloudLayerAmount(a),
                    BasicDataAdapter::height(height),
                    cloudLayerDetail(convType),
                    std::optional<int>()});
                break;
            }
            [[fallthrough]];
        default:
            log(Report::Warning::Message::DUPLICATED_DATA);
            return;
    }
}

void EssentialsAdapter::setVerticalVisibility(metaf::Distance vv) {
    assert(essentials);
    if (essentials->skyCondition != Essentials::SkyCondition::UNKNOWN) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    if (!setData<Height>(essentials->verticalVisibility,
                         BasicDataAdapter::height(vv))) return;
    essentials->skyCondition = Essentials::SkyCondition::OBSCURED;
}

void EssentialsAdapter::addWeatherPhenomena(const metaf::WeatherPhenomena &wp) {
    const auto w = BasicDataAdapter::weather(wp);
    if (!w.has_value()) return;
    assert(essentials);
    if (hasNsw()) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    // TODO: check for duplicate weather phenomena?
    essentials->weather.push_back(*w);
}

void EssentialsAdapter::setNsw() {
    assert(essentials);
    if (!essentials->weather.empty()) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    essentials->weather.push_back(Weather{
        Weather::Phenomena::NO_SIGNIFICANT_WEATHER,
        {}});
}

bool EssentialsAdapter::hasNsw() const {
    assert(essentials);
    for (const auto &w : essentials->weather) {
        if (w.phenomena == Weather::Phenomena::NO_SIGNIFICANT_WEATHER)
            return false;
    }
    return true;
}

Essentials::SkyCondition
EssentialsAdapter::skyCondition(metaf::CloudGroup::Amount a) {
    switch (a) {
        case metaf::CloudGroup::Amount::NOT_REPORTED:
            return Essentials::SkyCondition::UNKNOWN;
        case metaf::CloudGroup::Amount::NSC:
            return Essentials::SkyCondition::NO_SIGNIFICANT_CLOUD;
        case metaf::CloudGroup::Amount::NCD:
            return Essentials::SkyCondition::CLEAR_NCD;
        case metaf::CloudGroup::Amount::NONE_CLR:
            return Essentials::SkyCondition::CLEAR_CLR;
        case metaf::CloudGroup::Amount::NONE_SKC:
            return Essentials::SkyCondition::CLEAR_SKC;
        case metaf::CloudGroup::Amount::FEW:
        case metaf::CloudGroup::Amount::SCATTERED:
        case metaf::CloudGroup::Amount::BROKEN:
        case metaf::CloudGroup::Amount::OVERCAST:
        case metaf::CloudGroup::Amount::VARIABLE_FEW_SCATTERED:
        case metaf::CloudGroup::Amount::VARIABLE_SCATTERED_BROKEN:
        case metaf::CloudGroup::Amount::VARIABLE_BROKEN_OVERCAST:
            return Essentials::SkyCondition::CLOUDS;
        case metaf::CloudGroup::Amount::OBSCURED:
            return Essentials::SkyCondition::OBSCURED;
    }
}

CloudLayer::Details
EssentialsAdapter::cloudLayerDetail(metaf::CloudGroup::ConvectiveType ct) {
    switch (ct) {
        case metaf::CloudGroup::ConvectiveType::NONE:
            return CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS;
        case metaf::CloudGroup::ConvectiveType::TOWERING_CUMULUS:
            return CloudLayer::Details::TOWERING_CUMULUS;
        case metaf::CloudGroup::ConvectiveType::CUMULONIMBUS:
            return CloudLayer::Details::CUMULONIMBUS;
        case metaf::CloudGroup::ConvectiveType::NOT_REPORTED:
            return CloudLayer::Details::UNKNOWN;
    }
}

////////////////////////////////////////////////////////////////////////////////

class AerodromeDataAdapter : DataAdapter {
   public:
    AerodromeDataAdapter(Aerodrome &a, WarningLogger *l) : DataAdapter(l),
                                                           aerodrome(&a) {}
    inline void setColourCode(Aerodrome::ColourCode code, bool codeBlack);
    inline void setSurfaceVisibility(metaf::Distance sfcVis);
    inline void setTowerVisibility(metaf::Distance sfcVis);
    inline void setVisibility(std::optional<metaf::Runway> rw,
                              metaf::Distance vis);
    inline void setVisibility(std::optional<metaf::Direction> d,
                              metaf::Distance vis);
    inline void setVisibility(std::optional<metaf::Runway> rw,
                              metaf::Distance minVis,
                              metaf::Distance maxVis);
    inline void setVisibility(std::optional<metaf::Direction> dir,
                              metaf::Distance minVis,
                              metaf::Distance maxVis);
    inline void setRvr(std::optional<metaf::Runway> rw,
                       metaf::Distance rvr,
                       metaf::VisibilityGroup::Trend trend);
    inline void setRvr(std::optional<metaf::Runway> rw,
                       metaf::Distance minRvr,
                       metaf::Distance maxRvr,
                       metaf::VisibilityGroup::Trend trend);
    inline void setCeiling(std::optional<metaf::Runway> rw,
                           std::optional<metaf::Direction> dir,
                           metaf::Distance ceiling);
    inline void setCeiling(std::optional<metaf::Runway> rw,
                           std::optional<metaf::Direction> dir,
                           metaf::Distance minCeiling,
                           metaf::Distance maxCeiling);
    inline void setRunwayState(metaf::Runway rw,
                               metaf::RunwayStateGroup::Deposits d,
                               metaf::RunwayStateGroup::Extent x,
                               metaf::Precipitation depth,
                               metaf::SurfaceFriction sf);
    inline void setRunwayClrd(metaf::Runway rw,
                              metaf::SurfaceFriction sf);
    inline void setRunwaySnoclo(metaf::Runway rw);
    inline void setRunwayNonOp(metaf::Runway rw);
    inline void setRunwayWindShearLowerLayers(std::optional<metaf::Runway> rw);
    inline void setAerodromeSnoclo();

   private:
    Aerodrome *aerodrome;
    inline Aerodrome::RunwayData &getOrCreateRunway(const Runway &r);
    inline Aerodrome::DirectionData &
    getOrCreateDirection(const CardinalDirection &d);
    inline Ceiling *getCeiling(std::optional<metaf::Runway> rw,
                               std::optional<metaf::Direction> dir);
    inline void setVisibility(Distance &d, const metaf::Distance &md);
    inline void setVisibility(DistanceRange &d, const metaf::Distance &md);
    inline void setVisibility(DistanceRange &d,
                              const metaf::Distance &min,
                              const metaf::Distance &max);
    inline static void setSurfaceFriction(Aerodrome::RunwayData &rd,
                                          const metaf::SurfaceFriction &s);
    inline static bool hasRunwayState(const Aerodrome::RunwayData &rd);
    inline static Aerodrome::RvrTrend
    rvrTrend(metaf::VisibilityGroup::Trend t);
};

void AerodromeDataAdapter::setColourCode(Aerodrome::ColourCode code,
                                         bool codeBlack) {
    if (code == Aerodrome::ColourCode::NOT_SPECIFIED) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(aerodrome);
    if (aerodrome->colourCode != Aerodrome::ColourCode::NOT_SPECIFIED ||
        aerodrome->colourCodeBlack) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    aerodrome->colourCode = code;
    aerodrome->colourCodeBlack = codeBlack;
}

void AerodromeDataAdapter::setSurfaceVisibility(metaf::Distance sfcVis) {
    assert(aerodrome);
    setVisibility(aerodrome->surfaceVisibility, sfcVis);
}

void AerodromeDataAdapter::setTowerVisibility(metaf::Distance twrVis) {
    assert(aerodrome);
    setVisibility(aerodrome->towerVisibility, twrVis);
}

void AerodromeDataAdapter::setVisibility(std::optional<metaf::Runway> rw,
                                         metaf::Distance vis) {
    if (!rw.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(aerodrome);
    auto rd = getOrCreateRunway(BasicDataAdapter::runway(*rw));
    setVisibility(rd.visibility, vis);
}

void AerodromeDataAdapter::setVisibility(std::optional<metaf::Direction> d,
                                         metaf::Distance vis) {
    if (!d.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(aerodrome);
    auto dd = getOrCreateDirection(BasicDataAdapter::cardinalDirection(*d));
    setVisibility(dd.visibility, vis);
}

void AerodromeDataAdapter::setVisibility(std::optional<metaf::Runway> rw,
                                         metaf::Distance minVis,
                                         metaf::Distance maxVis) {
    if (!rw.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(aerodrome);
    auto rd = getOrCreateRunway(BasicDataAdapter::runway(*rw));
    setVisibility(rd.visibility, minVis, maxVis);
}

void AerodromeDataAdapter::setVisibility(std::optional<metaf::Direction> dir,
                                         metaf::Distance minVis,
                                         metaf::Distance maxVis) {
    if (!dir.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(aerodrome);
    auto dd = getOrCreateDirection(BasicDataAdapter::cardinalDirection(*dir));
    setVisibility(dd.visibility, minVis, maxVis);
}

void AerodromeDataAdapter::setRvr(std::optional<metaf::Runway> rw,
                                  metaf::Distance rvr,
                                  metaf::VisibilityGroup::Trend trend) {
    if (!rw.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(aerodrome);
    auto rd = getOrCreateRunway(BasicDataAdapter::runway(*rw));
    if (rd.visualRangeTrend != Aerodrome::RvrTrend::UNKNOWN) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    setVisibility(rd.visualRange, rvr);
    rd.visualRangeTrend = rvrTrend(trend);
}

void AerodromeDataAdapter::setRvr(std::optional<metaf::Runway> rw,
                                  metaf::Distance minRvr,
                                  metaf::Distance maxRvr,
                                  metaf::VisibilityGroup::Trend trend) {
    if (!rw.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(aerodrome);
    auto rd = getOrCreateRunway(BasicDataAdapter::runway(*rw));
    if (rd.visualRangeTrend != Aerodrome::RvrTrend::UNKNOWN) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    setVisibility(rd.visibility, minRvr, maxRvr);
    rd.visualRangeTrend = rvrTrend(trend);
}

void AerodromeDataAdapter::setCeiling(std::optional<metaf::Runway> rw,
                                      std::optional<metaf::Direction> dir,
                                      metaf::Distance ceiling) {
    assert(aerodrome);
    auto c = getCeiling(rw, dir);
    if (!c) return;
    setData<Height>(c->exact, BasicDataAdapter::height(ceiling));
}

void AerodromeDataAdapter::setCeiling(std::optional<metaf::Runway> rw,
                                      std::optional<metaf::Direction> dir,
                                      metaf::Distance minCeiling,
                                      metaf::Distance maxCeiling) {
    assert(aerodrome);
    auto c = getCeiling(rw, dir);
    if (!c) return;
    if (c->minimum.height.has_value() || c->maximum.height.has_value()) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    c->minimum = BasicDataAdapter::height(minCeiling);
    c->maximum = BasicDataAdapter::height(maxCeiling);
}

void AerodromeDataAdapter::setRunwayState(metaf::Runway rw,
                                          metaf::RunwayStateGroup::Deposits d,
                                          metaf::RunwayStateGroup::Extent x,
                                          metaf::Precipitation depth,
                                          metaf::SurfaceFriction sf) {
    auto convertDeposits = [](metaf::RunwayStateGroup::Deposits d) {
        switch (d) {
            case metaf::RunwayStateGroup::Deposits::CLEAR_AND_DRY:
                return Aerodrome::RunwayDeposits::CLEAR_AND_DRY;
            case metaf::RunwayStateGroup::Deposits::DAMP:
                return Aerodrome::RunwayDeposits::DAMP;
            case metaf::RunwayStateGroup::Deposits::WET_AND_WATER_PATCHES:
                return Aerodrome::RunwayDeposits::WET_AND_WATER_PATCHES;
            case metaf::RunwayStateGroup::Deposits::RIME_AND_FROST_COVERED:
                return Aerodrome::RunwayDeposits::RIME_AND_FROST_COVERED;
            case metaf::RunwayStateGroup::Deposits::DRY_SNOW:
                return Aerodrome::RunwayDeposits::DRY_SNOW;
            case metaf::RunwayStateGroup::Deposits::WET_SNOW:
                return Aerodrome::RunwayDeposits::WET_SNOW;
            case metaf::RunwayStateGroup::Deposits::SLUSH:
                return Aerodrome::RunwayDeposits::SLUSH;
            case metaf::RunwayStateGroup::Deposits::ICE:
                return Aerodrome::RunwayDeposits::ICE;
            case metaf::RunwayStateGroup::Deposits::COMPACTED_OR_ROLLED_SNOW:
                return Aerodrome::RunwayDeposits::COMPACTED_OR_ROLLED_SNOW;
            case metaf::RunwayStateGroup::Deposits::FROZEN_RUTS_OR_RIDGES:
                return Aerodrome::RunwayDeposits::FROZEN_RUTS_OR_RIDGES;
            case metaf::RunwayStateGroup::Deposits::NOT_REPORTED:
                return Aerodrome::RunwayDeposits::UNKNOWN;
        }
    };
    auto convertExtent = [](metaf::RunwayStateGroup::Extent e) {
        switch (e) {
            case metaf::RunwayStateGroup::Extent::NONE:
                return Aerodrome::RunwayContamExtent::NO_DEPOSITS;
            case metaf::RunwayStateGroup::Extent::RESERVED_3:
            case metaf::RunwayStateGroup::Extent::RESERVED_4:
            case metaf::RunwayStateGroup::Extent::RESERVED_6:
            case metaf::RunwayStateGroup::Extent::RESERVED_7:
            case metaf::RunwayStateGroup::Extent::RESERVED_8:
            case metaf::RunwayStateGroup::Extent::NOT_REPORTED:
                return Aerodrome::RunwayContamExtent::UNKNOWN;
            case metaf::RunwayStateGroup::Extent::LESS_THAN_10_PERCENT:
                return Aerodrome::RunwayContamExtent::LESS_THAN_11_PERCENT;
            case metaf::RunwayStateGroup::Extent::FROM_11_TO_25_PERCENT:
                return Aerodrome::RunwayContamExtent::FROM_11_TO_25_PERCENT;
            case metaf::RunwayStateGroup::Extent::FROM_26_TO_50_PERCENT:
                return Aerodrome::RunwayContamExtent::FROM_26_TO_50_PERCENT;
            case metaf::RunwayStateGroup::Extent::MORE_THAN_51_PERCENT:
                return Aerodrome::RunwayContamExtent::MORE_THAN_50_PERCENT;
        }
    };
    assert(aerodrome);
    auto rd = getOrCreateRunway(BasicDataAdapter::runway(rw));
    if (hasRunwayState(rd)) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    rd.deposits = convertDeposits(d);
    rd.contaminationExtent = convertExtent(x);
    rd.depositDepth = BasicDataAdapter::precipitation(depth);
    setSurfaceFriction(rd, sf);
}

void AerodromeDataAdapter::setRunwayClrd(metaf::Runway rw,
                                         metaf::SurfaceFriction sf) {
    assert(aerodrome);
    auto rd = getOrCreateRunway(BasicDataAdapter::runway(rw));
    if (hasRunwayState(rd)) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    rd.clrd = true;
    setSurfaceFriction(rd, sf);
}

void AerodromeDataAdapter::setRunwaySnoclo(metaf::Runway rw) {
    assert(aerodrome);
    auto rd = getOrCreateRunway(BasicDataAdapter::runway(rw));
    if (hasRunwayState(rd)) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    rd.snoclo = true;
}

void AerodromeDataAdapter::setRunwayNonOp(metaf::Runway rw) {
    assert(aerodrome);
    auto rd = getOrCreateRunway(BasicDataAdapter::runway(rw));
    if (hasRunwayState(rd)) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    rd.notOperational = true;
}

void AerodromeDataAdapter::setRunwayWindShearLowerLayers(
    std::optional<metaf::Runway> rw) {
    assert(aerodrome);
    if (!rw.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    auto rd = getOrCreateRunway(BasicDataAdapter::runway(*rw));
    setData<bool>(rd.windShearLowerLayers, true);
}

void AerodromeDataAdapter::setAerodromeSnoclo() {
    assert(aerodrome);
    setData<bool>(aerodrome->snoclo, true);
}

Aerodrome::RunwayData &
AerodromeDataAdapter::getOrCreateRunway(const Runway &r) {
    for (auto i = 0u; i < aerodrome->runways.size(); i++) {
        if (aerodrome->runways[i].runway.number == r.number &&
            aerodrome->runways[i].runway.designator == r.designator) {
            return aerodrome->runways[i];
        }
    }
    Aerodrome::RunwayData rd;
    rd.runway = r;
    aerodrome->runways.push_back(rd);
    return aerodrome->runways.back();
}

Aerodrome::DirectionData &
AerodromeDataAdapter::getOrCreateDirection(const CardinalDirection &d) {
    for (auto i = 0u; i < aerodrome->directions.size(); i++) {
        if (aerodrome->directions[i].cardinalDirection == d)
            return aerodrome->directions[i];
    }
    Aerodrome::DirectionData dd;
    dd.cardinalDirection = d;
    aerodrome->directions.push_back(dd);
    return aerodrome->directions.back();
}

void AerodromeDataAdapter::setVisibility(Distance &d,
                                         const metaf::Distance &md) {
    const auto vis = BasicDataAdapter::distance(md);
    if (!vis.has_value()) {
        log(Report::Warning::Message::INVALID_DISTANCE_RANGE);
        return;
    }
    setData<Distance>(d, *vis);
}

void AerodromeDataAdapter::setVisibility(DistanceRange &d,
                                         const metaf::Distance &md) {
    setVisibility(d.prevailing, md);
}

void AerodromeDataAdapter::setVisibility(DistanceRange &d,
                                         const metaf::Distance &min,
                                         const metaf::Distance &max) {
    if (d.minimum.distance.has_value() || d.maximum.distance.has_value()) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    const auto visMin = BasicDataAdapter::distance(min);
    const auto visMax = BasicDataAdapter::distance(max);
    if (!visMax.has_value() || visMin.has_value()) {
        log(Report::Warning::Message::INVALID_DISTANCE_RANGE);
        return;
    }
    d.minimum = *visMin;
    d.maximum = *visMax;
}

Ceiling *AerodromeDataAdapter::getCeiling(std::optional<metaf::Runway> rw,
                                          std::optional<metaf::Direction> dir) {
    if (!rw.has_value() && !dir.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return nullptr;
    }
    if (rw.has_value() && dir.has_value()) {
        log(Report::Warning::Message::INCONSISTENT_DATA);
        return nullptr;
    }
    assert(aerodrome);
    if (rw.has_value())
        return &getOrCreateRunway(BasicDataAdapter::runway(*rw)).ceiling;
    if (dir.has_value())
        return &getOrCreateDirection(BasicDataAdapter::cardinalDirection(*dir))
                    .ceiling;
    return nullptr;
}

void AerodromeDataAdapter::setSurfaceFriction(Aerodrome::RunwayData &rd,
                                              const metaf::SurfaceFriction &s) {
    if (s.isUnreliable()) {
        rd.surfaceFrictionUnreliable = true;
    }
    if (const auto c = s.coefficient(); c.has_value()) {
        rd.coefficient = std::floor(*c * 100.0);
    }
}

bool AerodromeDataAdapter::hasRunwayState(const Aerodrome::RunwayData &rd) {
    return rd.snoclo ||
           rd.notOperational ||
           rd.surfaceFrictionUnreliable ||
           rd.deposits != Aerodrome::RunwayDeposits::UNKNOWN ||
           rd.contaminationExtent != Aerodrome::RunwayContamExtent::UNKNOWN ||
           rd.depositDepth.amount.has_value();
}

Aerodrome::RvrTrend
AerodromeDataAdapter::rvrTrend(metaf::VisibilityGroup::Trend t) {
    switch (t) {
        case metaf::VisibilityGroup::Trend::NONE:
        case metaf::VisibilityGroup::Trend::NOT_REPORTED:
            return Aerodrome::RvrTrend::UNKNOWN;
        case metaf::VisibilityGroup::Trend::DOWNWARD:
            return Aerodrome::RvrTrend::DOWNWARD;
        case metaf::VisibilityGroup::Trend::NEUTRAL:
            return Aerodrome::RvrTrend::NEUTRAL;
        case metaf::VisibilityGroup::Trend::UPWARD:
            return Aerodrome::RvrTrend::UPWARD;
    }
}

////////////////////////////////////////////////////////////////////////////////

class HistoricalDataAdapter : DataAdapter {
   public:
    HistoricalDataAdapter(Historical &h, WarningLogger *l) : DataAdapter(l),
                                                             historical(&h) {}
    inline void setPeakWind(metaf::Direction d,
                            metaf::Speed s,
                            std::optional<metaf::MetafTime> t);
    inline void setWindShift(bool fropa, std::optional<metaf::MetafTime> t);
    inline void addRecentWeather(const metaf::WeatherPhenomena &wp);
    inline void addWeatherEvent(const metaf::WeatherPhenomena &wp);
    inline void setMinMaxTemperature(bool last24h,
                                     metaf::Temperature min,
                                     metaf::Temperature max);
    inline void setPrecipitationTotal1h(metaf::Precipitation p);
    inline void setFrozenPrecipitation3h6h(metaf::Precipitation p);
    inline void setFrozenPrecipitation3h(metaf::Precipitation p);
    inline void setFrozenPrecipitation6h(metaf::Precipitation p);
    inline void setFrozenPrecipitation24h(metaf::Precipitation p);
    inline void setSnow6h(metaf::Precipitation p);
    inline void setWaterEquivalentOfSnow(metaf::Precipitation p);
    inline void setIceAccretion1h(metaf::Precipitation p);
    inline void setIceAccretion3h(metaf::Precipitation p);
    inline void setIceAccretion6h(metaf::Precipitation p);
    inline void setTotalSnowfall(metaf::Precipitation p);
    inline void setSnowfallIncrease1h(metaf::Precipitation p);
    inline void setPrecipitationSinceLastReport(metaf::Precipitation p);
    inline void setRainfall(metaf::Precipitation since9am,
                            metaf::Precipitation last10m);
    inline void setPressureTendency(metaf::PressureTendencyGroup::Type t,
                                    metaf::Pressure difference);
    inline void setSunshineDuration(std::optional<float> m);
    inline static std::optional<Historical::WeatherEvent>
    weatherEvent(const metaf::WeatherPhenomena &we);

   private:
    Historical *historical;
};

void HistoricalDataAdapter::setPeakWind(metaf::Direction d,
                                        metaf::Speed s,
                                        std::optional<metaf::MetafTime> t) {
    const auto hasPeakWind = [](const Historical &h) {
        return (h.peakWindDirectionDegrees.has_value() ||
                h.peakWindSpeed.speed.has_value() ||
                h.peakWindObserved.day.has_value() ||
                h.peakWindObserved.hour.has_value() ||
                h.peakWindObserved.minute.has_value());
    };
    assert(historical);
    if (hasPeakWind(*historical)) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    historical->peakWindDirectionDegrees = d.degrees();
    historical->peakWindSpeed = BasicDataAdapter::speed(s);
    historical->peakWindObserved = BasicDataAdapter::time(t);
}

void HistoricalDataAdapter::setWindShift(bool fropa,
                                         std::optional<metaf::MetafTime> t) {
    const auto hasWindShift = [](const Historical &h) {
        return (h.windShift ||
                h.windShiftFrontPassage ||
                h.windShiftBegan.day.has_value() ||
                h.windShiftBegan.hour.has_value() ||
                h.windShiftBegan.minute.has_value());
    };
    assert(historical);
    if (hasWindShift(*historical)) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    historical->windShift = !fropa;
    historical->windShiftFrontPassage = fropa;
    historical->windShiftBegan = BasicDataAdapter::time(t);
}

void HistoricalDataAdapter::addRecentWeather(
    const metaf::WeatherPhenomena &wp) {
    const auto w = weatherEvent(wp);
    if (!w.has_value()) {
        log(Report::Warning::Message::INVALID_WEATHER_PHENOMENA);
        return;
    }
    historical->recentWeather.push_back(*w);
}

void HistoricalDataAdapter::setMinMaxTemperature(bool last24h,
                                                 metaf::Temperature min,
                                                 metaf::Temperature max) {
    const auto tmin = BasicDataAdapter::temperature(min);
    const auto tmax = BasicDataAdapter::temperature(max);
    if (!tmin.temperature.has_value() || !tmax.temperature.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(historical);
    Temperature *dstmin = &historical->temperatureMin6h;
    Temperature *dstmax = &historical->temperatureMax6h;
    if (last24h) {
        dstmin = &historical->temperatureMin24h;
        dstmax = &historical->temperatureMax24h;
    }
    if (dstmin->temperature.has_value() && dstmax->temperature.has_value()) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    *dstmin = tmin;
    *dstmax = tmax;
}

void HistoricalDataAdapter::setPrecipitationTotal1h(metaf::Precipitation p) {
    setData<Precipitation>(historical->precipitationTotal1h,
                           BasicDataAdapter::precipitation(p));
}

void HistoricalDataAdapter::setFrozenPrecipitation3h6h(metaf::Precipitation p) {
    log(Report::Warning::Message::INVALID_3H_6H_REPORT_TIME);
    setData<Precipitation>(historical->precipitationFrozen3or6h,
                           BasicDataAdapter::precipitation(p));
}

void HistoricalDataAdapter::setFrozenPrecipitation3h(metaf::Precipitation p) {
    setData<Precipitation>(historical->precipitationFrozen3h,
                           BasicDataAdapter::precipitation(p));
}

void HistoricalDataAdapter::setFrozenPrecipitation6h(metaf::Precipitation p) {
    setData<Precipitation>(historical->precipitationFrozen6h,
                           BasicDataAdapter::precipitation(p));
}

void HistoricalDataAdapter::setFrozenPrecipitation24h(metaf::Precipitation p) {
    setData<Precipitation>(historical->precipitationFrozen24h,
                           BasicDataAdapter::precipitation(p));
}

void HistoricalDataAdapter::setSnow6h(metaf::Precipitation p) {
    setData<Precipitation>(historical->snow6h,
                           BasicDataAdapter::precipitation(p));
}

void HistoricalDataAdapter::setIceAccretion1h(metaf::Precipitation p) {
    setData<Precipitation>(historical->icing1h,
                           BasicDataAdapter::precipitation(p));
}

void HistoricalDataAdapter::setIceAccretion3h(metaf::Precipitation p) {
    setData<Precipitation>(historical->icing3h,
                           BasicDataAdapter::precipitation(p));
}

void HistoricalDataAdapter::setIceAccretion6h(metaf::Precipitation p) {
    setData<Precipitation>(historical->icing6h,
                           BasicDataAdapter::precipitation(p));
}

void HistoricalDataAdapter::setTotalSnowfall(metaf::Precipitation p) {
    setData<Precipitation>(historical->snowfallTotal,
                           BasicDataAdapter::precipitation(p));
}

void HistoricalDataAdapter::setSnowfallIncrease1h(metaf::Precipitation p) {
    setData<Precipitation>(historical->snowfallIncrease1h,
                           BasicDataAdapter::precipitation(p));
}

void HistoricalDataAdapter::setPrecipitationSinceLastReport(
    metaf::Precipitation p) {
    setData<Precipitation>(historical->precipitationSinceLastReport,
                           BasicDataAdapter::precipitation(p));
}

void HistoricalDataAdapter::setRainfall(metaf::Precipitation since9am,
                                        metaf::Precipitation last10m) {
    historical->rainfallSince0900LocalTime =
        BasicDataAdapter::precipitation(since9am);
    historical->rainfall10m = BasicDataAdapter::precipitation(last10m);
}

void HistoricalDataAdapter::setPressureTendency(
    metaf::PressureTendencyGroup::Type t,
    metaf::Pressure difference) {
    auto convertMetafTendency = [](metaf::PressureTendencyGroup::Type t) {
        switch (t) {
            case metaf::PressureTendencyGroup::Type::NOT_REPORTED:
                return Historical::PressureTendency::UNKNOWN;
            case metaf::PressureTendencyGroup::Type::INCREASING_THEN_DECREASING:
                return Historical::PressureTendency::INCREASING_THEN_DECREASING;
            case metaf::PressureTendencyGroup::Type::INCREASING_MORE_SLOWLY:
                return Historical::PressureTendency::INCREASING_MORE_SLOWLY;
            case metaf::PressureTendencyGroup::Type::INCREASING:
                return Historical::PressureTendency::INCREASING;
            case metaf::PressureTendencyGroup::Type::INCREASING_MORE_RAPIDLY:
                return Historical::PressureTendency::INCREASING_MORE_RAPIDLY;
            case metaf::PressureTendencyGroup::Type::STEADY:
                return Historical::PressureTendency::STEADY;
            case metaf::PressureTendencyGroup::Type::DECREASING_THEN_INCREASING:
                return Historical::PressureTendency::DECREASING_THEN_INCREASING;
            case metaf::PressureTendencyGroup::Type::DECREASING_MORE_SLOWLY:
                return Historical::PressureTendency::DECREASING_MORE_SLOWLY;
            case metaf::PressureTendencyGroup::Type::DECREASING:
                return Historical::PressureTendency::DECREASING;
            case metaf::PressureTendencyGroup::Type::DECREASING_MORE_RAPIDLY:
                return Historical::PressureTendency::DECREASING_MORE_RAPIDLY;
            case metaf::PressureTendencyGroup::Type::RISING_RAPIDLY:
                return Historical::PressureTendency::RISING_RAPIDLY;
            case metaf::PressureTendencyGroup::Type::FALLING_RAPIDLY:
                return Historical::PressureTendency::FALLING_RAPIDLY;
        }
    };
    auto convertMetafTrend = [](metaf::PressureTendencyGroup::Type t) {
        switch (metaf::PressureTendencyGroup::trend(t)) {
            case metaf::PressureTendencyGroup::Trend::NOT_REPORTED:
                return Historical::PressureTrend::UNKNOWN;
            case metaf::PressureTendencyGroup::Trend::HIGHER:
                return Historical::PressureTrend::HIGHER;
            case metaf::PressureTendencyGroup::Trend::HIGHER_OR_SAME:
                return Historical::PressureTrend::HIGHER_OR_SAME;
            case metaf::PressureTendencyGroup::Trend::SAME:
                return Historical::PressureTrend::SAME;
            case metaf::PressureTendencyGroup::Trend::LOWER_OR_SAME:
                return Historical::PressureTrend::LOWER_OR_SAME;
            case metaf::PressureTendencyGroup::Trend::LOWER:
                return Historical::PressureTrend::LOWER;
        }
    };
    assert(historical);
    if (historical->pressureTendency != Historical::PressureTendency::UNKNOWN ||
        historical->pressureTrend != Historical::PressureTrend::UNKNOWN ||
        historical->pressureChange3h.pressure.has_value()) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    historical->pressureChange3h = BasicDataAdapter::pressure(difference);
    historical->pressureTendency = convertMetafTendency(t);
    historical->pressureTrend = convertMetafTrend(t);
}

void HistoricalDataAdapter::setSunshineDuration(std::optional<float> m) {
    if (!m.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    const auto dur = std::floor(*m);
    assert(historical);
    setData<std::optional<int>>(historical->sunshineDurationMinutes24h, dur);
}

std::optional<Historical::WeatherEvent>
HistoricalDataAdapter::weatherEvent(const metaf::WeatherPhenomena &we) {
    auto convertEvent = [](metaf::WeatherPhenomena::Event e) {
        switch (e) {
            case metaf::WeatherPhenomena::Event::BEGINNING:
                return Historical::Event::BEGAN;
                break;
            case metaf::WeatherPhenomena::Event::NONE:
            case metaf::WeatherPhenomena::Event::ENDING:
                return Historical::Event::ENDED;
                break;
        }
    };
    const auto w = BasicDataAdapter::weather(we);
    if (!w.has_value()) return std::optional<Historical::WeatherEvent>();
    return Historical::WeatherEvent{convertEvent(we.event()),
                                    *w,
                                    BasicDataAdapter::time(we.time())};
}

////////////////////////////////////////////////////////////////////////////////

class CurrentDataAdapter : DataAdapter {
   public:
    CurrentDataAdapter(Current &c, WarningLogger *l) : DataAdapter(l),
                                                       current(&c) {}
    inline void addWindShear(metaf::Distance height,
                             metaf::Direction direction,
                             metaf::Speed windSpeed);
    inline void setObscuration(metaf::CloudGroup::Amount amount,
                               const metaf::Distance height,
                               std::optional<metaf::CloudType> cloudType);
    inline void setTemperatureDewPoint(metaf::Temperature t,
                                       metaf::Temperature dp);
    inline void setRelativeHumidity(metaf::Temperature t,
                                    metaf::Temperature dp);
    inline void setVisibility(const metaf::Distance &min,
                              const metaf::Distance &max);
    inline void setPressureQnh(metaf::Pressure p);
    inline void setPressureQfe(metaf::Pressure p);
    inline void setSeaSurface(metaf::Temperature t, metaf::WaveHeight wh);
    inline void setSnowDepth(metaf::Precipitation p);
    inline void setWaterEquivalentOfSnow(metaf::Precipitation p);
    inline void setSnowIncreasingRapidly();
    inline void addTypesToCloudLayers(std::vector<metaf::CloudType> ct);
    inline void setClouds(metaf::LowMidHighCloudGroup::LowLayer l,
                          metaf::LowMidHighCloudGroup::MidLayer m,
                          metaf::LowMidHighCloudGroup::HighLayer h);
    inline void setLightning(metaf::LightningGroup::Frequency f,
                             metaf::Distance d,
                             bool inCloud,
                             bool cloudCloud,
                             bool cloudGround,
                             bool cloudAir,
                             bool unknownType,
                             std::vector<metaf::Direction> dir);
    inline void setPhenomenaInVicinity(metaf::VicinityGroup::Type t,
                                       metaf::Distance d,
                                       std::vector<metaf::Direction> dir,
                                       metaf::Direction movDir);
    inline void setPhenomenaInVicinity(const metaf::WeatherPhenomena &w);
    inline void setHailstoneSize(std::optional<float> s);
    inline void setDensityAltitude(std::optional<float> da);
    inline void setFrostOnInstrument();

   private:
    Current *current;
};

void CurrentDataAdapter::addWindShear(metaf::Distance height,
                                      metaf::Direction direction,
                                      metaf::Speed windSpeed) {
    const auto dir = direction.degrees();
    const auto h = BasicDataAdapter::height(height);
    const auto s = BasicDataAdapter::speed(windSpeed);
    if (!dir.has_value() || !h.height.has_value() || !s.speed.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    const auto d = static_cast<int>(*dir);
    assert(current);
    //TODO: check for duplicate groups?
    current->windShear.push_back(Current::WindShear{h, d, s});
}

void CurrentDataAdapter::setObscuration(metaf::CloudGroup::Amount amount,
                                        const metaf::Distance height,
                                        std::optional<metaf::CloudType> ct) {
    if (!ct.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(current);
    current->obscurations.push_back(
        CloudLayer{BasicDataAdapter::cloudLayerAmount(amount),
                   BasicDataAdapter::height(height),
                   BasicDataAdapter::cloudLayerDetails(ct->type()),
                   std::optional<int>()});
}

void CurrentDataAdapter::setTemperatureDewPoint(metaf::Temperature t,
                                                metaf::Temperature dp) {
    assert(current);
    setData<Temperature>(current->airTemperature,
                         BasicDataAdapter::temperature(t));
    setData<Temperature>(current->dewPoint,
                         BasicDataAdapter::temperature(dp));
}

void CurrentDataAdapter::setRelativeHumidity(metaf::Temperature t,
                                             metaf::Temperature dp) {
    assert(current);
    const auto rh = metaf::Temperature::relativeHumidity(t, dp);
    if (!rh.has_value()) return;
    setData<std::optional<int>>(current->relativeHumidity, std::floor(*rh));
}

void CurrentDataAdapter::setVisibility(const metaf::Distance &min,
                                       const metaf::Distance &max) {
    assert(current);
    if (current->variableVisibility.minimum.distance.has_value() ||
        current->variableVisibility.maximum.distance.has_value()) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    const auto dmin = BasicDataAdapter::distance(min);
    const auto dmax = BasicDataAdapter::distance(max);
    if (!dmin.has_value() || !dmax.has_value()) {
        log(Report::Warning::Message::INVALID_DISTANCE_RANGE);
        return;
    }
    current->variableVisibility.minimum = *dmin;
    current->variableVisibility.maximum = *dmax;
}

void CurrentDataAdapter::setPressureQnh(metaf::Pressure p) {
    assert(current);
    setData<Pressure>(current->pressureSeaLevel, BasicDataAdapter::pressure(p));
}

void CurrentDataAdapter::setPressureQfe(metaf::Pressure p) {
    assert(current);
    setData<Pressure>(current->pressureGroundLevel,
                      BasicDataAdapter::pressure(p));
}

void CurrentDataAdapter::setSeaSurface(metaf::Temperature t,
                                       metaf::WaveHeight wh) {
    assert(current);
    setData<Temperature>(current->seaSurfaceTemperature,
                         BasicDataAdapter::temperature(t));
    setData<WaveHeight>(current->waveHeight, BasicDataAdapter::waveHeight(wh));
}

void CurrentDataAdapter::setSnowDepth(metaf::Precipitation p) {
    assert(current);
    setData<Precipitation>(current->snowDepthOnGround,
                           BasicDataAdapter::precipitation(p));
}

void CurrentDataAdapter::setSnowIncreasingRapidly() {
    assert(current);
    setData<bool>(current->snowIncreasingRapidly, true);
}

void CurrentDataAdapter::setWaterEquivalentOfSnow(metaf::Precipitation p) {
    assert(current);
    setData<Precipitation>(current->snowWaterEquivalent,
                           BasicDataAdapter::precipitation(p));
}

void CurrentDataAdapter::addTypesToCloudLayers(
    std::vector<metaf::CloudType> ct) {
    // TODO
}

void CurrentDataAdapter::setClouds(metaf::LowMidHighCloudGroup::LowLayer l,
                                   metaf::LowMidHighCloudGroup::MidLayer m,
                                   metaf::LowMidHighCloudGroup::HighLayer h) {
    auto convertLowLayer = [](metaf::LowMidHighCloudGroup::LowLayer c) {
        switch (c) {
            case metaf::LowMidHighCloudGroup::LowLayer::NONE:
                return Current::LowCloudLayer::NO_CLOUDS;
            case metaf::LowMidHighCloudGroup::LowLayer::CU_HU_CU_FR:
                return Current::LowCloudLayer::CU_HU_CU_FR;
            case metaf::LowMidHighCloudGroup::LowLayer::CU_MED_CU_CON:
                return Current::LowCloudLayer::CU_MED_CU_CON;
            case metaf::LowMidHighCloudGroup::LowLayer::CB_CAL:
                return Current::LowCloudLayer::CB_CAL;
            case metaf::LowMidHighCloudGroup::LowLayer::SC_CUGEN:
                return Current::LowCloudLayer::SC_CUGEN;
            case metaf::LowMidHighCloudGroup::LowLayer::SC_NON_CUGEN:
                return Current::LowCloudLayer::SC_NON_CUGEN;
            case metaf::LowMidHighCloudGroup::LowLayer::ST_NEB_ST_FR:
                return Current::LowCloudLayer::ST_NEB_ST_FR;
            case metaf::LowMidHighCloudGroup::LowLayer::ST_FR_CU_FR_PANNUS:
                return Current::LowCloudLayer::ST_FR_CU_FR_PANNUS;
            case metaf::LowMidHighCloudGroup::LowLayer::
                CU_SC_NON_CUGEN_DIFFERENT_LEVELS:
                return Current::LowCloudLayer::CU_SC_NON_CUGEN_DIFFERENT_LEVELS;
            case metaf::LowMidHighCloudGroup::LowLayer::CB_CAP:
                return Current::LowCloudLayer::CB_CAP;
            case metaf::LowMidHighCloudGroup::LowLayer::NOT_OBSERVABLE:
                return Current::LowCloudLayer::UNKNOWN;
        }
    };
    auto convertMidLayer = [](metaf::LowMidHighCloudGroup::MidLayer c) {
        switch (c) {
            case metaf::LowMidHighCloudGroup::MidLayer::NONE:
                return Current::MidCloudLayer::NO_CLOUDS;
            case metaf::LowMidHighCloudGroup::MidLayer::AS_TR:
                return Current::MidCloudLayer::AS_TR;
            case metaf::LowMidHighCloudGroup::MidLayer::AS_OP_NS:
                return Current::MidCloudLayer::AS_OP_NS;
            case metaf::LowMidHighCloudGroup::MidLayer::AC_TR:
                return Current::MidCloudLayer::AC_TR;
            case metaf::LowMidHighCloudGroup::MidLayer::AC_TR_LEN_PATCHES:
                return Current::MidCloudLayer::AC_TR_LEN_PATCHES;
            case metaf::LowMidHighCloudGroup::MidLayer::AC_TR_AC_OP_SPREADING:
                return Current::MidCloudLayer::AC_TR_AC_OP_SPREADING;
            case metaf::LowMidHighCloudGroup::MidLayer::AC_CUGEN_AC_CBGEN:
                return Current::MidCloudLayer::AC_CUGEN_AC_CBGEN;
            case metaf::LowMidHighCloudGroup::MidLayer::
                AC_DU_AC_OP_AC_WITH_AS_OR_NS:
                return Current::MidCloudLayer::AC_DU_AC_OP_AC_WITH_AS_OR_NS;
            case metaf::LowMidHighCloudGroup::MidLayer::AC_CAS_AC_FLO:
                return Current::MidCloudLayer::AC_CAS_AC_FLO;
            case metaf::LowMidHighCloudGroup::MidLayer::AC_OF_CHAOTIC_SKY:
                return Current::MidCloudLayer::AC_OF_CHAOTIC_SKY;
            case metaf::LowMidHighCloudGroup::MidLayer::NOT_OBSERVABLE:
                return Current::MidCloudLayer::UNKNOWN;
        }
    };
    auto convertHighLayer = [](metaf::LowMidHighCloudGroup::HighLayer c) {
        switch (c) {
            case metaf::LowMidHighCloudGroup::HighLayer::NONE:
                return Current::HighCloudLayer::NO_CLOUDS;
            case metaf::LowMidHighCloudGroup::HighLayer::CI_FIB_CI_UNC:
                return Current::HighCloudLayer::CI_FIB_CI_UNC;
            case metaf::LowMidHighCloudGroup::HighLayer::CI_SPI_CI_CAS_CI_FLO:
                return Current::HighCloudLayer::CI_SPI_CI_CAS_CI_FLO;
            case metaf::LowMidHighCloudGroup::HighLayer::CI_SPI_CBGEN:
                return Current::HighCloudLayer::CI_SPI_CBGEN;
            case metaf::LowMidHighCloudGroup::HighLayer::
                CI_FIB_CI_UNC_SPREADING:
                return Current::HighCloudLayer::CI_FIB_CI_UNC_SPREADING;
            case metaf::LowMidHighCloudGroup::HighLayer::
                CI_CS_LOW_ABOVE_HORIZON:
                return Current::HighCloudLayer::CI_CS_LOW_ABOVE_HORIZON;
            case metaf::LowMidHighCloudGroup::HighLayer::
                CI_CS_HIGH_ABOVE_HORIZON:
                return Current::HighCloudLayer::CI_CS_HIGH_ABOVE_HORIZON;
            case metaf::LowMidHighCloudGroup::HighLayer::
                CS_NEB_CS_FIB_COVERING_ENTIRE_SKY:
                return Current::HighCloudLayer::
                    CS_NEB_CS_FIB_COVERING_ENTIRE_SKY;
            case metaf::LowMidHighCloudGroup::HighLayer::CS:
                return Current::HighCloudLayer::CS;
            case metaf::LowMidHighCloudGroup::HighLayer::CC:
                return Current::HighCloudLayer::CC;
            case metaf::LowMidHighCloudGroup::HighLayer::NOT_OBSERVABLE:
                return Current::HighCloudLayer::UNKNOWN;
        }
    };
    assert(current);
    if (current->lowCloudLayer != Current::LowCloudLayer::UNKNOWN ||
        current->midCloudLayer != Current::MidCloudLayer::UNKNOWN ||
        current->highCloudLayer != Current::HighCloudLayer::UNKNOWN) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    current->lowCloudLayer = convertLowLayer(l);
    current->midCloudLayer = convertMidLayer(m);
    current->highCloudLayer = convertHighLayer(h);
}

void CurrentDataAdapter::setLightning(metaf::LightningGroup::Frequency f,
                                      metaf::Distance d,
                                      bool inCloud,
                                      bool cloudCloud,
                                      bool cloudGround,
                                      bool cloudAir,
                                      bool unknownType,
                                      std::vector<metaf::Direction> dir) {
    auto convertFrequency = [](metaf::LightningGroup::Frequency f) {
        switch (f) {
            case metaf::LightningGroup::Frequency::NONE:
                return LightningStrikes::Frequency::UNKNOWN;
            case metaf::LightningGroup::Frequency::OCCASIONAL:
                return LightningStrikes::Frequency::OCCASIONAL;
            case metaf::LightningGroup::Frequency::FREQUENT:
                return LightningStrikes::Frequency::FREQUENT;
            case metaf::LightningGroup::Frequency::CONSTANT:
                return LightningStrikes::Frequency::CONSTANT;
        }
    };
    LightningStrikes result;
    result.frequency = convertFrequency(f);
    result.distance = BasicDataAdapter::distanceRange(d);
    if (inCloud) result.type.insert(LightningStrikes::Type::IN_CLOUD);
    if (cloudGround) result.type.insert(LightningStrikes::Type::CLOUD_GROUND);
    if (cloudCloud) result.type.insert(LightningStrikes::Type::CLOUD_CLOUD);
    if (cloudAir) result.type.insert(LightningStrikes::Type::CLOUD_AIR);
    if (unknownType) log(Report::Warning::Message::INVALID_LIGHTNING_TYPE);
    for (const auto &dd : dir) {
        result.directions.insert(BasicDataAdapter::cardinalDirection(dd));
    }
    assert(current);
    current->lightningStrikes.push_back(result);
}

void CurrentDataAdapter::setPhenomenaInVicinity(metaf::VicinityGroup::Type t,
                                                metaf::Distance d,
                                                std::vector<metaf::Direction>
                                                    dir,
                                                metaf::Direction movDir) {
    auto convert = [](metaf::VicinityGroup::Type t) {
        switch (t) {
            case metaf::VicinityGroup::Type::THUNDERSTORM:
                return Vicinity::Phenomena::THUNDERSTORM;
            case metaf::VicinityGroup::Type::CUMULONIMBUS:
                return Vicinity::Phenomena::CUMULONIMBUS;
            case metaf::VicinityGroup::Type::CUMULONIMBUS_MAMMATUS:
                return Vicinity::Phenomena::CUMULONIMBUS_MAMMATUS;
            case metaf::VicinityGroup::Type::TOWERING_CUMULUS:
                return Vicinity::Phenomena::TOWERING_CUMULUS;
            case metaf::VicinityGroup::Type::ALTOCUMULUS_CASTELLANUS:
                return Vicinity::Phenomena::ALTOCUMULUS_CASTELLANUS;
            case metaf::VicinityGroup::Type::STRATOCUMULUS_STANDING_LENTICULAR:
                return Vicinity::Phenomena::STRATOCUMULUS_STANDING_LENTICULAR;
            case metaf::VicinityGroup::Type::ALTOCUMULUS_STANDING_LENTICULAR:
                return Vicinity::Phenomena::ALTOCUMULUS_STANDING_LENTICULAR;
            case metaf::VicinityGroup::Type::CIRROCUMULUS_STANDING_LENTICULAR:
                return Vicinity::Phenomena::CIRROCUMULUS_STANDING_LENTICULAR;
            case metaf::VicinityGroup::Type::ROTOR_CLOUD:
                return Vicinity::Phenomena::ROTOR_CLOUD;
            case metaf::VicinityGroup::Type::VIRGA:
                return Vicinity::Phenomena::VIRGA;
            case metaf::VicinityGroup::Type::PRECIPITATION_IN_VICINITY:
                return Vicinity::Phenomena::PRECIPITATION;
            case metaf::VicinityGroup::Type::FOG:
                return Vicinity::Phenomena::FOG;
            case metaf::VicinityGroup::Type::FOG_SHALLOW:
                return Vicinity::Phenomena::FOG_SHALLOW;
            case metaf::VicinityGroup::Type::FOG_PATCHES:
                return Vicinity::Phenomena::FOG_PATCHES;
            case metaf::VicinityGroup::Type::HAZE:
                return Vicinity::Phenomena::HAZE;
            case metaf::VicinityGroup::Type::SMOKE:
                return Vicinity::Phenomena::SMOKE;
            case metaf::VicinityGroup::Type::BLOWING_SNOW:
                return Vicinity::Phenomena::BLOWING_SNOW;
            case metaf::VicinityGroup::Type::BLOWING_SAND:
                return Vicinity::Phenomena::BLOWING_SAND;
            case metaf::VicinityGroup::Type::BLOWING_DUST:
                return Vicinity::Phenomena::BLOWING_DUST;
        }
    };
    Vicinity v;
    v.phenomena = convert(t);
    v.distance = BasicDataAdapter::distanceRange(d);
    v.moving = BasicDataAdapter::cardinalDirection(movDir);
    for (const auto &dd : dir) {
        v.directions.insert(BasicDataAdapter::cardinalDirection(dd));
    }
    assert(current);
    current->phenomenaInVicinity.push_back(v);
}

void CurrentDataAdapter::setPhenomenaInVicinity(
    const metaf::WeatherPhenomena &w) {
    auto convertVicinity = [](Weather w) {
        switch (w.phenomena) {
            case Weather::Phenomena::THUNDERSTORM:
                return std::optional<Vicinity::Phenomena>(
                    Vicinity::Phenomena::THUNDERSTORM);
            case Weather::Phenomena::FOG:
                return std::optional<Vicinity::Phenomena>(
                    Vicinity::Phenomena::FOG);
            case Weather::Phenomena::PRECIPITATION:
                return std::optional<Vicinity::Phenomena>(
                    Vicinity::Phenomena::PRECIPITATION);
            case Weather::Phenomena::DUST_WHIRLS:
                return std::optional<Vicinity::Phenomena>(
                    Vicinity::Phenomena::DUST_WHIRLS);
            case Weather::Phenomena::FUNNEL_CLOUD:
                return std::optional<Vicinity::Phenomena>(
                    Vicinity::Phenomena::FUNNEL_CLOUD);
            case Weather::Phenomena::BLOWING_DUST:
                return std::optional<Vicinity::Phenomena>(
                    Vicinity::Phenomena::BLOWING_DUST);
            case Weather::Phenomena::BLOWING_SAND:
                return std::optional<Vicinity::Phenomena>(
                    Vicinity::Phenomena::BLOWING_SAND);
            case Weather::Phenomena::BLOWING_SNOW:
                return std::optional<Vicinity::Phenomena>(
                    Vicinity::Phenomena::BLOWING_SNOW);
            case Weather::Phenomena::DUST_STORM:
                return std::optional<Vicinity::Phenomena>(
                    Vicinity::Phenomena::DUST_STORM);
            case Weather::Phenomena::SAND_STORM:
                return std::optional<Vicinity::Phenomena>(
                    Vicinity::Phenomena::SAND_STORM);
            case Weather::Phenomena::VOLCANIC_ASH:
                return std::optional<Vicinity::Phenomena>(
                    Vicinity::Phenomena::VOLCANIC_ASH);
            default:
                return std::optional<Vicinity::Phenomena>();
        }
    };
    const auto weather = BasicDataAdapter::weather(w);
    if (!weather.has_value()) {
        log(Report::Warning::Message::INVALID_WEATHER_PHENOMENA);
        return;
    }
    const auto ph = convertVicinity(*weather);
    if (!ph.has_value()) {
        log(Report::Warning::Message::INVALID_WEATHER_PHENOMENA);
        return;
    }
    assert(current);
    current->phenomenaInVicinity.push_back(Vicinity{
        *ph,
        DistanceRange(),
        CardinalDirection::NOT_SPECIFIED,
        {}});
}

void CurrentDataAdapter::setHailstoneSize(std::optional<float> s) {
    if (!s.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(current);
    setData<std::optional<int>>(current->hailstoneSizeQuartersInch,
                                std::floor(*s * 4.0));
}

void CurrentDataAdapter::setDensityAltitude(std::optional<float> da) {
    if (!da.has_value()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(current);
    setData<Height>(current->densityAltitude,
                    Height{std::floor(*da), Height::Unit::FEET});
}

void CurrentDataAdapter::setFrostOnInstrument() {
    assert(current);
    setData<bool>(current->frostOnInstrument, true);
}

////////////////////////////////////////////////////////////////////////////////

class ForecastDataAdapter : DataAdapter {
   public:
    ForecastDataAdapter(Forecast &f, WarningLogger *l) : DataAdapter(l),
                                                         forecast(&f) {}
    inline void setWindShearConditions();
    inline void addTrend(metaf::TrendGroup::Type t,
                         metaf::TrendGroup::Probability p,
                         std::optional<metaf::MetafTime> tfrom,
                         std::optional<metaf::MetafTime> tuntil,
                         std::optional<metaf::MetafTime> tat);
    inline void setLowestPressure(metaf::Pressure p);
    inline void setMinMaxTemperature(metaf::Temperature min,
                                     std::optional<metaf::MetafTime> tmin,
                                     metaf::Temperature max,
                                     std::optional<metaf::MetafTime> tmax);
    inline void addIcing(IcingForecast::Severity s,
                         IcingForecast::Type t,
                         metaf::Distance baseHeight,
                         metaf::Distance topHeight);
    inline void addTurbulence(TurbulenceForecast::Severity s,
                              TurbulenceForecast::Frequency f,
                              TurbulenceForecast::Location l,
                              metaf::Distance baseHeight,
                              metaf::Distance topHeight);

   private:
    Forecast *forecast;
};

void ForecastDataAdapter::setWindShearConditions() {
    assert(forecast);
    setData<bool>(forecast->windShearConditions, true);
}

void ForecastDataAdapter::addTrend(metaf::TrendGroup::Type t,
                                   metaf::TrendGroup::Probability p,
                                   std::optional<metaf::MetafTime> tfrom,
                                   std::optional<metaf::MetafTime> tuntil,
                                   std::optional<metaf::MetafTime> tat) {
    auto trendType = [](metaf::TrendGroup::Type type) {
        switch (type) {
            case metaf::TrendGroup::Type::NOSIG:
                return std::optional<Trend::Type>();
            case metaf::TrendGroup::Type::BECMG:
                return std::optional<Trend::Type>(Trend::Type::BECMG);
            case metaf::TrendGroup::Type::TEMPO:
                return std::optional<Trend::Type>(Trend::Type::TEMPO);
            case metaf::TrendGroup::Type::INTER:
                return std::optional<Trend::Type>(Trend::Type::INTER);
            case metaf::TrendGroup::Type::FROM:
            case metaf::TrendGroup::Type::UNTIL:
            case metaf::TrendGroup::Type::AT:
            case metaf::TrendGroup::Type::TIME_SPAN:
                return std::optional<Trend::Type>(Trend::Type::TIMED);
            case metaf::TrendGroup::Type::PROB:
                return std::optional<Trend::Type>(Trend::Type::PROB);
        }
    };
    auto trendProb = [](metaf::TrendGroup::Probability prob) {
        switch (prob) {
            case metaf::TrendGroup::Probability::NONE:
                return std::optional<int>();
            case metaf::TrendGroup::Probability::PROB_30:
                return std::optional<int>(30);
            case metaf::TrendGroup::Probability::PROB_40:
                return std::optional<int>(40);
        }
    };
    // TODO: check for duplicate trends?
    assert(forecast);
    if (forecast->noSignificantChanges) {
        log(Report::Warning::Message::DUPLICATED_DATA);
        return;
    }
    const auto type = trendType(t);
    if (!type.has_value()) {
        // NOSIG trend
        if (forecast->trends.size()) {
            log(Report::Warning::Message::DUPLICATED_DATA);
            return;
        }
        forecast->noSignificantChanges = true;
    }
    forecast->trends.push_back(Trend{
        *type,
        trendProb(p),
        BasicDataAdapter::time(tfrom),
        BasicDataAdapter::time(tuntil),
        BasicDataAdapter::time(tat),
        Essentials()});
}

void ForecastDataAdapter::setLowestPressure(metaf::Pressure p) {
    if (!p.isReported()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(forecast);
    setData<Pressure>(forecast->lowestQnh, BasicDataAdapter::pressure(p));
}

void ForecastDataAdapter::setMinMaxTemperature(metaf::Temperature min,
                                               std::optional<metaf::MetafTime>
                                                   tmin,
                                               metaf::Temperature max,
                                               std::optional<metaf::MetafTime>
                                                   tmax) {
    if (!tmin.has_value() ||
        !tmax.has_value() ||
        !min.isReported() ||
        !max.isReported()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(forecast);
    setData<Temperature>(forecast->minTemperature,
                         BasicDataAdapter::temperature(min));
    setData<Temperature>(forecast->maxTemperature,
                         BasicDataAdapter::temperature(max));
    setData<Time>(forecast->minTemperatureTime,
                  BasicDataAdapter::time(tmin));
    setData<Time>(forecast->maxTemperatureTime,
                  BasicDataAdapter::time(tmax));
}

void ForecastDataAdapter::addIcing(IcingForecast::Severity s,
                                   IcingForecast::Type t,
                                   metaf::Distance baseHeight,
                                   metaf::Distance topHeight) {
    // TODO: check for duplicate layer information?
    if (!baseHeight.isReported() || !baseHeight.isReported()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(forecast);
    forecast->icing.push_back(IcingForecast{
        s,
        t,
        BasicDataAdapter::height(baseHeight),
        BasicDataAdapter::height(topHeight)});
}

void ForecastDataAdapter::addTurbulence(TurbulenceForecast::Severity s,
                                        TurbulenceForecast::Frequency f,
                                        TurbulenceForecast::Location l,
                                        metaf::Distance baseHeight,
                                        metaf::Distance topHeight) {
    if (!baseHeight.isReported() || !baseHeight.isReported()) {
        log(Report::Warning::Message::REQUIRED_DATA_MISSING);
        return;
    }
    assert(forecast);
    forecast->turbulence.push_back(TurbulenceForecast{
        s,
        l,
        f,
        BasicDataAdapter::height(baseHeight),
        BasicDataAdapter::height(topHeight)});
}

////////////////////////////////////////////////////////////////////////////////

class CollateVisitor : public metaf::Visitor<void> {
   public:
    inline CollateVisitor(const metaf::ParseResult &src);
    const Simple &data() const { return result; }

   private:
    CollateVisitor() = delete;
    inline void collateMetadata(const metaf::ReportMetadata &metadata);
    void setGroupString(const std::string &s) { logger.setIdString(s); }
    inline EssentialsAdapter currentOrTrendBlock();
    void startPrevailingTrend() { isPrevailingTrend = true; }
    void startOtherTrend() { isPrevailingTrend = false; }
    CurrentDataAdapter currentData() {
        return CurrentDataAdapter(result.current, &logger);
    }
    HistoricalDataAdapter historicalData() {
        return HistoricalDataAdapter(result.historical, &logger);
    }
    AerodromeDataAdapter aerodromeData() {
        return AerodromeDataAdapter(result.aerodrome, &logger);
    }
    StationDataAdapter stationData() {
        return StationDataAdapter(result.station, &logger);
    }
    ForecastDataAdapter forecastData() {
        return ForecastDataAdapter(result.forecast, &logger);
    }

    Simple result;
    WarningLogger logger;
    bool isPrevailingTrend = false;

    inline virtual void visitKeywordGroup(
        const metaf::KeywordGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitLocationGroup(
        const metaf::LocationGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitReportTimeGroup(
        const metaf::ReportTimeGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitTrendGroup(
        const metaf::TrendGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitWindGroup(
        const metaf::WindGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitVisibilityGroup(
        const metaf::VisibilityGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitCloudGroup(
        const metaf::CloudGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitWeatherGroup(
        const metaf::WeatherGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitTemperatureGroup(
        const metaf::TemperatureGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitPressureGroup(
        const metaf::PressureGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitRunwayStateGroup(
        const metaf::RunwayStateGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitSeaSurfaceGroup(
        const metaf::SeaSurfaceGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitMinMaxTemperatureGroup(
        const metaf::MinMaxTemperatureGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitPrecipitationGroup(
        const metaf::PrecipitationGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitLayerForecastGroup(
        const metaf::LayerForecastGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitPressureTendencyGroup(
        const metaf::PressureTendencyGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitCloudTypesGroup(
        const metaf::CloudTypesGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitLowMidHighCloudGroup(
        const metaf::LowMidHighCloudGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitLightningGroup(
        const metaf::LightningGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitVicinityGroup(
        const metaf::VicinityGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitMiscGroup(
        const metaf::MiscGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
    inline virtual void visitUnknownGroup(
        const metaf::UnknownGroup &group,
        metaf::ReportPart reportPart,
        const std::string &rawString);
};

///////////////////////////////////////////////////////////////////////////

CollateVisitor::CollateVisitor(
    const metaf::ParseResult &src) : logger(result.report.warnings) {
    collateMetadata(src.reportMetadata);
    if (result.report.type == Report::Type::ERROR) return;
    for (const auto &g : src.groups) {
        setGroupString(g.rawString);
        visit(g);
    }
}

///////////////////////////////////////////////////////////////////////////

void CollateVisitor::collateMetadata(const metaf::ReportMetadata &md) {
    MetadataAdapter mda(result.report, result.station, &logger);
    mda.setReportType(md.type, md.isSpeci);
    mda.setReportError(md.error);
    mda.setAttributes(md.isNil,
                      md.isCancelled,
                      md.isCorrectional,
                      md.isAmended,
                      md.isAutomated,
                      md.isNospeci,
                      md.maintenanceIndicator,
                      md.correctionNumber);
    mda.setLocation(md.icaoLocation);
    mda.setReportTime(md.reportTime);
    mda.setApplicableTime(md.timeSpanFrom, md.timeSpanUntil);
}

EssentialsAdapter CollateVisitor::currentOrTrendBlock() {
    if (result.forecast.trends.size())
        return EssentialsAdapter(result.forecast.trends.back().forecast,
                                 &logger);
    if (isPrevailingTrend) return EssentialsAdapter(result.forecast.prevailing,
                                                    &logger);
    return EssentialsAdapter(result.current.weatherData, &logger);
}

void CollateVisitor::visitKeywordGroup(const metaf::KeywordGroup &group,
                                       metaf::ReportPart reportPart,
                                       const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    switch (group.type()) {
        case metaf::KeywordGroup::Type::METAR:
        case metaf::KeywordGroup::Type::SPECI:
        case metaf::KeywordGroup::Type::TAF:
        case metaf::KeywordGroup::Type::AMD:
        case metaf::KeywordGroup::Type::NIL:
        case metaf::KeywordGroup::Type::CNL:
        case metaf::KeywordGroup::Type::COR:
        case metaf::KeywordGroup::Type::AUTO:
        case metaf::KeywordGroup::Type::RMK:
        case metaf::KeywordGroup::Type::MAINTENANCE_INDICATOR:
        case metaf::KeywordGroup::Type::AO1:
        case metaf::KeywordGroup::Type::AO2:
        case metaf::KeywordGroup::Type::AO1A:
        case metaf::KeywordGroup::Type::AO2A:
        case metaf::KeywordGroup::Type::NOSPECI:
            // These groups are redundant since metadata have this info anyway
            break;
        case metaf::KeywordGroup::Type::CAVOK: {
            currentOrTrendBlock().setCavok();
            break;
        }
    }
}

void CollateVisitor::visitLocationGroup(const metaf::LocationGroup &group,
                                        metaf::ReportPart reportPart,
                                        const std::string &rawString) {
    (void)group;
    (void)reportPart;
    (void)rawString;
    // Redundant since location info is acquired from metadata
    // TODO: check against location in metadata
}

void CollateVisitor::visitReportTimeGroup(const metaf::ReportTimeGroup &group,
                                          metaf::ReportPart reportPart,
                                          const std::string &rawString) {
    (void)group;
    (void)reportPart;
    (void)rawString;
    // Redundant since report release time is acquired from metadata
    // TODO: check against time in metadata
}

void CollateVisitor::visitTrendGroup(const metaf::TrendGroup &group,
                                     metaf::ReportPart reportPart,
                                     const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    const auto from = BasicDataAdapter::time(group.timeFrom());
    const auto until = BasicDataAdapter::time(group.timeUntil());
    if (result.report.type == Report::Type::TAF &&
        group.type() == metaf::TrendGroup::Type::TIME_SPAN &&
        group.probability() == metaf::TrendGroup::Probability::NONE &&
        !group.timeAt().has_value() &&
        from.day == result.report.applicableFrom.day &&
        from.hour == result.report.applicableFrom.hour &&
        from.minute == result.report.applicableFrom.minute &&
        until.day == result.report.applicableUntil.day &&
        until.hour == result.report.applicableUntil.hour &&
        until.minute == result.report.applicableUntil.minute &&
        EssentialsAdapter::isEmpty(result.forecast.prevailing)) {
        startPrevailingTrend();
        return;
        }
        startOtherTrend();
        forecastData().addTrend(group.type(),
                                group.probability(),
                                group.timeFrom(),
                                group.timeUntil(),
                                group.timeAt());
}

void CollateVisitor::visitWindGroup(const metaf::WindGroup &group,
                                    metaf::ReportPart reportPart,
                                    const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    switch (group.type()) {
        case metaf::WindGroup::Type::SURFACE_WIND_CALM:
            currentOrTrendBlock().setSurfaceWindCalm();
            break;
        case metaf::WindGroup::Type::SURFACE_WIND:
        case metaf::WindGroup::Type::SURFACE_WIND_WITH_VARIABLE_SECTOR:
        case metaf::WindGroup::Type::VARIABLE_WIND_SECTOR: {
            currentOrTrendBlock().setSurfaceWind(group.direction(),
                                                 group.windSpeed(),
                                                 group.gustSpeed(),
                                                 group.varSectorBegin(),
                                                 group.varSectorEnd());
        } break;
        case metaf::WindGroup::Type::WIND_SHEAR:
            currentData().addWindShear(group.height(),
                                       group.direction(),
                                       group.windSpeed());
            break;
        case metaf::WindGroup::Type::WIND_SHEAR_IN_LOWER_LAYERS: {
            aerodromeData().setRunwayWindShearLowerLayers(group.runway());
            break;
        }
        case metaf::WindGroup::Type::WIND_SHIFT: {
            historicalData().setWindShift(false, group.eventTime());
            break;
        } break;
        case metaf::WindGroup::Type::WIND_SHIFT_FROPA: {
            historicalData().setWindShift(true, group.eventTime());
            break;
        }
        case metaf::WindGroup::Type::PEAK_WIND: {
            historicalData().setPeakWind(group.direction(),
                                         group.windSpeed(),
                                         group.eventTime());
            break;
        }
        case metaf::WindGroup::Type::WSCONDS: {
            forecastData().setWindShearConditions();
            break;
        }
        case metaf::WindGroup::Type::WND_MISG: {
            stationData().addMissingData(Station::MissingData::WND_MISG);
            break;
        }
    }
}

void CollateVisitor::visitVisibilityGroup(const metaf::VisibilityGroup &group,
                                          metaf::ReportPart reportPart,
                                          const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    switch (group.type()) {
        case metaf::VisibilityGroup::Type::PREVAILING: {
            currentOrTrendBlock().setVisibility(group.visibility());
            break;
        }
        case metaf::VisibilityGroup::Type::PREVAILING_NDV: {
            stationData().setNdv();
            currentOrTrendBlock().setVisibility(group.visibility());
            break;
        }
        case metaf::VisibilityGroup::Type::VARIABLE_PREVAILING: {
            currentData().setVisibility(group.minVisibility(),
                                        group.maxVisibility());
            break;
        }
        case metaf::VisibilityGroup::Type::DIRECTIONAL:
            aerodromeData().setVisibility(group.direction(), group.visibility());
            break;
        case metaf::VisibilityGroup::Type::VARIABLE_DIRECTIONAL:
            aerodromeData().setVisibility(group.direction(),
                                          group.minVisibility(),
                                          group.maxVisibility());
            break;
        case metaf::VisibilityGroup::Type::RUNWAY:
            aerodromeData().setVisibility(group.runway(), group.visibility());
            break;
        case metaf::VisibilityGroup::Type::VARIABLE_RUNWAY:
            aerodromeData().setVisibility(group.direction(),
                                          group.minVisibility(),
                                          group.maxVisibility());
            break;
        case metaf::VisibilityGroup::Type::RVR:
            aerodromeData().setRvr(group.runway(), group.visibility(), group.trend());
            break;
        case metaf::VisibilityGroup::Type::VARIABLE_RVR:
            aerodromeData().setRvr(group.runway(),
                                   group.minVisibility(),
                                   group.maxVisibility(),
                                   group.trend());
            break;

        case metaf::VisibilityGroup::Type::SURFACE:
            aerodromeData().setSurfaceVisibility(group.visibility());
            break;

        case metaf::VisibilityGroup::Type::TOWER:
            aerodromeData().setTowerVisibility(group.visibility());
            break;

        case metaf::VisibilityGroup::Type::SECTOR:
            for (const auto &d : group.sectorDirections()) {
                aerodromeData().setVisibility(d, group.visibility());
            }
            break;

        case metaf::VisibilityGroup::Type::VARIABLE_SECTOR:
            for (const auto &d : group.sectorDirections()) {
                aerodromeData().setVisibility(d, group.minVisibility(),
                                              group.maxVisibility());
            }
            break;

        case metaf::VisibilityGroup::Type::VIS_MISG:
            stationData().addMissingData(Station::MissingData::VIS_MISG);
            break;

        case metaf::VisibilityGroup::Type::RVR_MISG:
            stationData().addMissingData(Station::MissingData::RVR_MISG);
            break;

        case metaf::VisibilityGroup::Type::RVRNO:
            stationData().addMissingData(Station::MissingData::RVRNO);
            break;

        case metaf::VisibilityGroup::Type::VISNO:
            stationData().addVisno(group.runway(), group.direction());
            break;
    }
}

void CollateVisitor::visitCloudGroup(const metaf::CloudGroup &group,
                                     metaf::ReportPart reportPart,
                                     const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    switch (group.type()) {
        case metaf::CloudGroup::Type::NO_CLOUDS:
            currentOrTrendBlock().setSkyCondition(group.amount());
            break;
        case metaf::CloudGroup::Type::CLOUD_LAYER:
            currentOrTrendBlock().setSkyCondition(group.amount(),
                                                  group.height(),
                                                  group.convectiveType());
            break;
        case metaf::CloudGroup::Type::VERTICAL_VISIBILITY:
            currentOrTrendBlock().setVerticalVisibility(
                group.verticalVisibility());
            break;
        case metaf::CloudGroup::Type::CEILING:
            aerodromeData().setCeiling(group.runway(),
                                       group.direction(),
                                       group.height());
            break;
        case metaf::CloudGroup::Type::VARIABLE_CEILING:
            aerodromeData().setCeiling(group.runway(),
                                       group.direction(),
                                       group.minHeight(),
                                       group.maxHeight());
            break;
        case metaf::CloudGroup::Type::CHINO:
            stationData().addChino(group.runway(), group.direction());
            break;
        case metaf::CloudGroup::Type::CLD_MISG:
            stationData().addMissingData(Station::MissingData::CLD_MISG);
            break;
        case metaf::CloudGroup::Type::OBSCURATION: {
            currentData().setObscuration(group.amount(),
                                         group.height(),
                                         group.cloudType());
            break;
        }
    }
}
void CollateVisitor::visitWeatherGroup(const metaf::WeatherGroup &group,
                                       metaf::ReportPart reportPart,
                                       const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    switch (group.type()) {
        case metaf::WeatherGroup::Type::CURRENT:
            for (const auto &w : group.weatherPhenomena()) {
                if (w.qualifier() ==
                    metaf::WeatherPhenomena::Qualifier::VICINITY) {
                    currentData().setPhenomenaInVicinity(w);
                } else {
                    currentOrTrendBlock().addWeatherPhenomena(w);
                }
                // TODO: check vicinity qualifier and handle differently
                // (store in Current rather than in Essentials)
            }
            break;
        case metaf::WeatherGroup::Type::NSW:
            currentOrTrendBlock().setNsw();
            break;
        case metaf::WeatherGroup::Type::RECENT:
        case metaf::WeatherGroup::Type::EVENT:
            for (const auto &w : group.weatherPhenomena()) {
                historicalData().addRecentWeather(w);
            }
            break;
        case metaf::WeatherGroup::Type::PWINO:
            stationData().addMissingData(Station::MissingData::PWINO);
            break;
        case metaf::WeatherGroup::Type::TSNO:
            stationData().addMissingData(Station::MissingData::TSNO);
            break;
        case metaf::WeatherGroup::Type::WX_MISG:
            stationData().addMissingData(Station::MissingData::WX_MISG);
            break;
        case metaf::WeatherGroup::Type::TS_LTNG_TEMPO_UNAVBL:
            stationData().addMissingData(
                Station::MissingData::TS_LTNG_TEMPO_UNAVBL);
            break;
    }
}

void CollateVisitor::visitTemperatureGroup(const metaf::TemperatureGroup &group,
                                           metaf::ReportPart reportPart,
                                           const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    switch (group.type()) {
        case metaf::TemperatureGroup::Type::TEMPERATURE_AND_DEW_POINT:
            currentData().setTemperatureDewPoint(group.airTemperature(),
                                                 group.dewPoint());
            currentData().setRelativeHumidity(group.airTemperature(),
                                              group.dewPoint());
            break;
        case metaf::TemperatureGroup::Type::T_MISG:
            stationData().addMissingData(Station::MissingData::T_MISG);
            break;
        case metaf::TemperatureGroup::Type::TD_MISG:
            stationData().addMissingData(Station::MissingData::TD_MISG);
            break;
    }
}
void CollateVisitor::visitPressureGroup(const metaf::PressureGroup &group,
                                        metaf::ReportPart reportPart,
                                        const std::string &rawString) {
    (void)rawString;
    switch (group.type()) {
        case metaf::PressureGroup::Type::OBSERVED_QNH:
            if (reportPart == metaf::ReportPart::RMK) return;
            // TODO: check this SLPxxx group agains previously set pressure
            currentData().setPressureQnh(group.atmosphericPressure());
            break;
        case metaf::PressureGroup::Type::FORECAST_LOWEST_QNH:
            forecastData().setLowestPressure(group.atmosphericPressure());
            break;
        case metaf::PressureGroup::Type::OBSERVED_QFE:
            currentData().setPressureQfe(group.atmosphericPressure());
            break;
        case metaf::PressureGroup::Type::SLPNO:
            stationData().addMissingData(Station::MissingData::SLPNO);
            break;
        case metaf::PressureGroup::Type::PRES_MISG:
            stationData().addMissingData(Station::MissingData::PRES_MISG);
            break;
    }
}
void CollateVisitor::visitRunwayStateGroup(const metaf::RunwayStateGroup &group,
                                           metaf::ReportPart reportPart,
                                           const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    switch (group.type()) {
        case metaf::RunwayStateGroup::Type::RUNWAY_STATE:
            aerodromeData().setRunwayState(group.runway(),
                                           group.deposits(),
                                           group.contaminationExtent(),
                                           group.depositDepth(),
                                           group.surfaceFriction());
            break;
        case metaf::RunwayStateGroup::Type::RUNWAY_CLRD:
            aerodromeData().setRunwayClrd(group.runway(),
                                          group.surfaceFriction());
            break;
        case metaf::RunwayStateGroup::Type::RUNWAY_NOT_OPERATIONAL:
            aerodromeData().setRunwayNonOp(group.runway());
            break;
        case metaf::RunwayStateGroup::Type::RUNWAY_SNOCLO:
            aerodromeData().setRunwaySnoclo(group.runway());
            break;
        case metaf::RunwayStateGroup::Type::AERODROME_SNOCLO:
            aerodromeData().setAerodromeSnoclo();
            break;
    }
}
void CollateVisitor::visitSeaSurfaceGroup(const metaf::SeaSurfaceGroup &group,
                                          metaf::ReportPart reportPart,
                                          const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    currentData().setSeaSurface(group.surfaceTemperature(), group.waves());
}
void CollateVisitor::visitMinMaxTemperatureGroup(
    const metaf::MinMaxTemperatureGroup &group,
    metaf::ReportPart reportPart,
    const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    switch (group.type()) {
        case metaf::MinMaxTemperatureGroup::Type::OBSERVED_24_HOURLY:
            historicalData().setMinMaxTemperature(true,
                                                  group.minimum(),
                                                  group.maximum());
            break;
        case metaf::MinMaxTemperatureGroup::Type::OBSERVED_6_HOURLY:
            historicalData().setMinMaxTemperature(false,
                                                  group.minimum(),
                                                  group.maximum());
            break;
        case metaf::MinMaxTemperatureGroup::Type::FORECAST:
            forecastData().setMinMaxTemperature(group.minimum(),
                                                group.minimumTime(),
                                                group.maximum(),
                                                group.maximumTime());
            break;
    }
}
void CollateVisitor::visitPrecipitationGroup(
    const metaf::PrecipitationGroup &group,
    metaf::ReportPart reportPart,
    const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    switch (group.type()) {
        case metaf::PrecipitationGroup::Type::TOTAL_PRECIPITATION_HOURLY:
            historicalData().setPrecipitationTotal1h(group.total());
            break;
        case metaf::PrecipitationGroup::Type::SNOW_DEPTH_ON_GROUND:
            currentData().setSnowDepth(group.total());
            break;
        case metaf::PrecipitationGroup::Type::FROZEN_PRECIP_3_OR_6_HOURLY:
            historicalData().setFrozenPrecipitation3h6h(group.total());
            break;
        case metaf::PrecipitationGroup::Type::FROZEN_PRECIP_3_HOURLY:
            historicalData().setFrozenPrecipitation3h(group.total());
            break;
        case metaf::PrecipitationGroup::Type::FROZEN_PRECIP_6_HOURLY:
            historicalData().setFrozenPrecipitation6h(group.total());
            break;
        case metaf::PrecipitationGroup::Type::FROZEN_PRECIP_24_HOURLY:
            historicalData().setFrozenPrecipitation24h(group.total());
            break;
        case metaf::PrecipitationGroup::Type::SNOW_6_HOURLY:
            historicalData().setSnow6h(group.total());
            break;
        case metaf::PrecipitationGroup::Type::WATER_EQUIV_OF_SNOW_ON_GROUND:
            currentData().setWaterEquivalentOfSnow(group.total());
            break;
        case metaf::PrecipitationGroup::Type::ICE_ACCRETION_FOR_LAST_HOUR:
            historicalData().setIceAccretion1h(group.total());
            break;
        case metaf::PrecipitationGroup::Type::ICE_ACCRETION_FOR_LAST_3_HOURS:
            historicalData().setIceAccretion3h(group.total());
            break;
        case metaf::PrecipitationGroup::Type::ICE_ACCRETION_FOR_LAST_6_HOURS:
            historicalData().setIceAccretion6h(group.total());
            break;
        case metaf::PrecipitationGroup::Type::SNOW_INCREASING_RAPIDLY:
            historicalData().setTotalSnowfall(group.total());
            historicalData().setSnowfallIncrease1h(group.recent());
            currentData().setSnowIncreasingRapidly();
            break;
        case metaf::PrecipitationGroup::Type::
            PRECIPITATION_ACCUMULATION_SINCE_LAST_REPORT:
            historicalData().setPrecipitationSinceLastReport(group.total());
            break;
        case metaf::PrecipitationGroup::Type::RAINFALL_9AM_10MIN:
            historicalData().setRainfall(group.total(), group.recent());
            break;
        case metaf::PrecipitationGroup::Type::PNO:
            stationData().addMissingData(Station::MissingData::PNO);
            break;
        case metaf::PrecipitationGroup::Type::FZRANO:
            stationData().addMissingData(Station::MissingData::FZRANO);
            break;
        case metaf::PrecipitationGroup::Type::ICG_MISG:
            stationData().addMissingData(Station::MissingData::ICG_MISG);
            break;
        case metaf::PrecipitationGroup::Type::PCPN_MISG:
            stationData().addMissingData(Station::MissingData::PCPN_MISG);
            break;
    }
}
void CollateVisitor::visitLayerForecastGroup(
    const metaf::LayerForecastGroup &group,
    metaf::ReportPart reportPart,
    const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    switch (group.type()) {
        case metaf::LayerForecastGroup::Type::ICING_TRACE_OR_NONE:
            forecastData().addIcing(IcingForecast::Severity::NONE_OR_TRACE,
                                    IcingForecast::Type::NONE,
                                    group.baseHeight(),
                                    group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::ICING_LIGHT_MIXED:
            forecastData().addIcing(IcingForecast::Severity::LIGHT,
                                    IcingForecast::Type::MIXED,
                                    group.baseHeight(),
                                    group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::ICING_LIGHT_RIME_IN_CLOUD:
            forecastData().addIcing(IcingForecast::Severity::LIGHT,
                                    IcingForecast::Type::RIME_IN_CLOUD,
                                    group.baseHeight(),
                                    group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::
            ICING_LIGHT_CLEAR_IN_PRECIPITATION:
            forecastData().addIcing(IcingForecast::Severity::LIGHT,
                                    IcingForecast::Type::CLEAR_IN_PRECIPITATION,
                                    group.baseHeight(),
                                    group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::ICING_MODERATE_MIXED:
            forecastData().addIcing(IcingForecast::Severity::MODERATE,
                                    IcingForecast::Type::MIXED,
                                    group.baseHeight(),
                                    group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::ICING_MODERATE_RIME_IN_CLOUD:
            forecastData().addIcing(IcingForecast::Severity::MODERATE,
                                    IcingForecast::Type::RIME_IN_CLOUD,
                                    group.baseHeight(),
                                    group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::
            ICING_MODERATE_CLEAR_IN_PRECIPITATION:
            forecastData().addIcing(IcingForecast::Severity::MODERATE,
                                    IcingForecast::Type::CLEAR_IN_PRECIPITATION,
                                    group.baseHeight(),
                                    group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::ICING_SEVERE_MIXED:
            forecastData().addIcing(IcingForecast::Severity::SEVERE,
                                    IcingForecast::Type::MIXED,
                                    group.baseHeight(),
                                    group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::ICING_SEVERE_RIME_IN_CLOUD:
            forecastData().addIcing(IcingForecast::Severity::SEVERE,
                                    IcingForecast::Type::RIME_IN_CLOUD,
                                    group.baseHeight(),
                                    group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::
            ICING_SEVERE_CLEAR_IN_PRECIPITATION:
            forecastData().addIcing(IcingForecast::Severity::SEVERE,
                                    IcingForecast::Type::CLEAR_IN_PRECIPITATION,
                                    group.baseHeight(),
                                    group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::TURBULENCE_NONE:
            forecastData().addTurbulence(TurbulenceForecast::Severity::NONE,
                                         TurbulenceForecast::Frequency::NONE,
                                         TurbulenceForecast::Location::NONE,
                                         group.baseHeight(),
                                         group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::TURBULENCE_LIGHT:
            forecastData().addTurbulence(TurbulenceForecast::Severity::LIGHT,
                                         TurbulenceForecast::Frequency::NONE,
                                         TurbulenceForecast::Location::NONE,
                                         group.baseHeight(),
                                         group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::
            TURBULENCE_MODERATE_IN_CLEAR_AIR_OCCASIONAL:
            forecastData().addTurbulence(
                TurbulenceForecast::Severity::MODERATE,
                TurbulenceForecast::Frequency::OCCASIONAL,
                TurbulenceForecast::Location::IN_CLEAR_AIR,
                group.baseHeight(),
                group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::
            TURBULENCE_MODERATE_IN_CLEAR_AIR_FREQUENT:
            forecastData().addTurbulence(
                TurbulenceForecast::Severity::MODERATE,
                TurbulenceForecast::Frequency::FREQUENT,
                TurbulenceForecast::Location::IN_CLEAR_AIR,
                group.baseHeight(),
                group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::
            TURBULENCE_MODERATE_IN_CLOUD_OCCASIONAL:
            forecastData().addTurbulence(
                TurbulenceForecast::Severity::MODERATE,
                TurbulenceForecast::Frequency::OCCASIONAL,
                TurbulenceForecast::Location::IN_CLOUD,
                group.baseHeight(),
                group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::
            TURBULENCE_MODERATE_IN_CLOUD_FREQUENT:
            forecastData().addTurbulence(
                TurbulenceForecast::Severity::MODERATE,
                TurbulenceForecast::Frequency::FREQUENT,
                TurbulenceForecast::Location::IN_CLOUD,
                group.baseHeight(),
                group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::
            TURBULENCE_SEVERE_IN_CLEAR_AIR_OCCASIONAL:
            forecastData().addTurbulence(
                TurbulenceForecast::Severity::SEVERE,
                TurbulenceForecast::Frequency::OCCASIONAL,
                TurbulenceForecast::Location::IN_CLEAR_AIR,
                group.baseHeight(),
                group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::
            TURBULENCE_SEVERE_IN_CLEAR_AIR_FREQUENT:
            forecastData().addTurbulence(
                TurbulenceForecast::Severity::SEVERE,
                TurbulenceForecast::Frequency::FREQUENT,
                TurbulenceForecast::Location::IN_CLEAR_AIR,
                group.baseHeight(),
                group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::
            TURBULENCE_SEVERE_IN_CLOUD_OCCASIONAL:
            forecastData().addTurbulence(
                TurbulenceForecast::Severity::SEVERE,
                TurbulenceForecast::Frequency::OCCASIONAL,
                TurbulenceForecast::Location::IN_CLOUD,
                group.baseHeight(),
                group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::
            TURBULENCE_SEVERE_IN_CLOUD_FREQUENT:
            forecastData().addTurbulence(
                TurbulenceForecast::Severity::SEVERE,
                TurbulenceForecast::Frequency::FREQUENT,
                TurbulenceForecast::Location::IN_CLOUD,
                group.baseHeight(),
                group.topHeight());
            break;
        case metaf::LayerForecastGroup::Type::TURBULENCE_EXTREME:
            forecastData().addTurbulence(TurbulenceForecast::Severity::EXTREME,
                                         TurbulenceForecast::Frequency::NONE,
                                         TurbulenceForecast::Location::NONE,
                                         group.baseHeight(),
                                         group.topHeight());
            break;
    }
}

void CollateVisitor::visitPressureTendencyGroup(
    const metaf::PressureTendencyGroup &group,
    metaf::ReportPart reportPart,
    const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    historicalData().setPressureTendency(group.type(),
                                         group.difference());
}

void CollateVisitor::visitCloudTypesGroup(const metaf::CloudTypesGroup &group,
                                          metaf::ReportPart reportPart,
                                          const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    currentData().addTypesToCloudLayers(group.cloudTypes());
}

void CollateVisitor::visitLowMidHighCloudGroup(
    const metaf::LowMidHighCloudGroup &group,
    metaf::ReportPart reportPart,
    const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    currentData().setClouds(group.lowLayer(),
                            group.midLayer(),
                            group.highLayer());
}

void CollateVisitor::visitLightningGroup(const metaf::LightningGroup &group,
                                         metaf::ReportPart reportPart,
                                         const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    currentData().setLightning(group.frequency(),
                               group.distance(),
                               group.isInCloud(),
                               group.isCloudCloud(),
                               group.isCloudGround(),
                               group.isCloudAir(),
                               group.isUnknownType(),
                               group.directions());
}
void CollateVisitor::visitVicinityGroup(const metaf::VicinityGroup &group,
                                        metaf::ReportPart reportPart,
                                        const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    currentData().setPhenomenaInVicinity(group.type(),
                                         group.distance(),
                                         group.directions(),
                                         group.movingDirection());
}

void CollateVisitor::visitMiscGroup(const metaf::MiscGroup &group,
                                    metaf::ReportPart reportPart,
                                    const std::string &rawString) {
    (void)reportPart;
    (void)rawString;
    switch (group.type()) {
        case metaf::MiscGroup::Type::SUNSHINE_DURATION_MINUTES:
            historicalData().setSunshineDuration(group.data());
            break;
        case metaf::MiscGroup::Type::CORRECTED_WEATHER_OBSERVATION:
            // Redundant; metadata already have this info
            // TODO: check against metadata
            break;
        case metaf::MiscGroup::Type::DENSITY_ALTITUDE:
            currentData().setDensityAltitude(group.data());
            break;
        case metaf::MiscGroup::Type::HAILSTONE_SIZE:
            currentData().setHailstoneSize(group.data());
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_BLUE:
            aerodromeData().setColourCode(Aerodrome::ColourCode::BLUE, false);
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_WHITE:
            aerodromeData().setColourCode(Aerodrome::ColourCode::WHITE, false);
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_GREEN:
            aerodromeData().setColourCode(Aerodrome::ColourCode::GREEN, false);
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_YELLOW1:
            aerodromeData().setColourCode(Aerodrome::ColourCode::YELLOW1,
                                          false);
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_YELLOW2:
            aerodromeData().setColourCode(Aerodrome::ColourCode::YELLOW2,
                                          false);
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_AMBER:
            aerodromeData().setColourCode(Aerodrome::ColourCode::AMBER, false);
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_RED:
            aerodromeData().setColourCode(Aerodrome::ColourCode::RED, false);
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_BLACKBLUE:
            aerodromeData().setColourCode(Aerodrome::ColourCode::BLUE, true);
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_BLACKWHITE:
            aerodromeData().setColourCode(Aerodrome::ColourCode::WHITE, true);
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_BLACKGREEN:
            aerodromeData().setColourCode(Aerodrome::ColourCode::GREEN, true);
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_BLACKYELLOW1:
            aerodromeData().setColourCode(Aerodrome::ColourCode::YELLOW1, true);
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_BLACKYELLOW2:
            aerodromeData().setColourCode(Aerodrome::ColourCode::YELLOW2, true);
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_BLACKAMBER:
            aerodromeData().setColourCode(Aerodrome::ColourCode::AMBER, true);
            break;
        case metaf::MiscGroup::Type::COLOUR_CODE_BLACKRED:
            aerodromeData().setColourCode(Aerodrome::ColourCode::RED, true);
            break;
        case metaf::MiscGroup::Type::FROIN:
            currentData().setFrostOnInstrument();
            break;
    }
}

void CollateVisitor::visitUnknownGroup(const metaf::UnknownGroup &group,
                                       metaf::ReportPart reportPart,
                                       const std::string &rawString) {
    (void)group;
    (void)reportPart;
    result.report.plainText.push_back(rawString);
}

}  // namespace metafsimple::detail

namespace metafsimple {

inline Simple simplify(const metaf::ParseResult &parseResult) {
    metafsimple::detail::CollateVisitor v(parseResult);
    return v.data();
}

inline Simple simplify(const std::string &report) {
    return simplify(metaf::Parser::parse(report));
}

}  // namespace metafsimple

#endif  // #ifndef METAFSIMPLE_HPP
