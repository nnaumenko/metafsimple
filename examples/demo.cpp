/*
* Copyright (C) 2020 Nick Naumenko (https://gitlab.com/nnaumenko,
* https:://github.com/nnaumenko)
* All rights reserved.
* This software may be modified and distributed under the terms
* of the MIT license. See the LICENSE file for details.
*/

#include <algorithm>
#include <iostream>
#include <sstream>

#include "metafsimple.hpp"

using namespace std::literals;
using namespace metafsimple;

static const auto newLine = '\n';
static const auto newPart =
    "----------------------------------------"
    "---------------------------------------\n";
static const auto newReport =
    "========================================"
    "=======================================\n";
static const auto newItem = " - ";

std::string ordinalNumber(int i) {
    auto suffix = [](int n) {
        switch (n % 10) {
            case 1:
                return "st";
            case 2:
                return "nd";
            case 3:
                return "rd";
            default:
                return "th";
        }
    };
    return (std::to_string(i) + suffix(i));
}

std::string formatReport(const std::string& s) {
    std::string r = s;
    r.erase(std::remove(r.begin(), r.end(), '\n'), r.end());
    r.erase(std::remove(r.begin(), r.end(), '\r'), r.end());
    r.erase(std::remove(r.begin(), r.end(), '\t'), r.end());
    return r;
};

std::string toStr(std::optional<int> i, size_t minDigits = 0) {
    if (!i.has_value()) return "";
    std::string result = std::to_string(*i);
    if (const auto l = result.length(); l < minDigits) {
        result.insert(result[0] != '-', minDigits - l, '0');
    }
    return result;
}

std::string_view toStr(CardinalDirection cd) {
    switch (cd) {
        case CardinalDirection::NOT_SPECIFIED:
            return ""sv;
        case CardinalDirection::N:
            return "north"sv;
        case CardinalDirection::S:
            return "south"sv;
        case CardinalDirection::W:
            return "west"sv;
        case CardinalDirection::E:
            return "east"sv;
        case CardinalDirection::NW:
            return "northwest"sv;
        case CardinalDirection::SW:
            return "southwest"sv;
        case CardinalDirection::NE:
            return "northeast"sv;
        case CardinalDirection::SE:
            return "southeast"sv;
        case CardinalDirection::OVERHEAD:
            return "overhead"sv;
        case CardinalDirection::ALL_QUADRANTS:
            return "all directions"sv;
        case CardinalDirection::UNKNOWN:
            return "unknown direction"sv;
    }
}

std::string toStr(const Runway& rw) {
    auto designator = [](Runway::Designator d) {
        switch (d) {
            case Runway::Designator::NONE:
                return ""sv;
            case Runway::Designator::LEFT:
                return "LEFT"sv;
            case Runway::Designator::RIGHT:
                return "RIGHT"sv;
            case Runway::Designator::CENTER:
                return "CENTER"sv;
        }
    };
    std::string result = std::to_string(rw.number);
    if (const auto s = designator(rw.designator); !s.empty()) {
        result += ' ';
        result += s;
    }
    return result;
}

std::string toStr(const Time& t) {
    std::string result;
    if (!t.day.has_value() && !t.hour.has_value() && !t.minute.has_value())
        return "";
    if (const auto s = toStr(t.day); !s.empty()) result += "day " + s;
    if (t.hour.has_value() || t.minute.has_value()) {
        if (!result.empty()) result += ", ";
        result += toStr(t.hour, 2) + ":" + toStr(t.minute, 2) + " GMT";
    }
    return result;
}

std::string toStr(const Temperature& t) {
    const auto c = t.toUnit(Temperature::Unit::C);
    const auto f = t.toUnit(Temperature::Unit::F);
    if (!c.has_value() || !f.has_value()) return "";
    switch (t.unit) {
        case Temperature::Unit::C:
        case Temperature::Unit::TENTH_C:
            return std::to_string(*c) + " C (" + std::to_string(*f) + " F)";
        case Temperature::Unit::F:
            return std::to_string(*f) + " F (" + std::to_string(*c) + " C)";
    }
}

std::string toStr(const Speed& s) {
    const auto kt = s.toUnit(Speed::Unit::KT);
    const auto mps = s.toUnit(Speed::Unit::MPS);
    const auto kmh = s.toUnit(Speed::Unit::KMH);
    const auto mph = s.toUnit(Speed::Unit::MPH);
    if (!kt.has_value() ||
        !mps.has_value() ||
        !kmh.has_value() ||
        !mph.has_value()) return "";
    switch (s.unit) {
        case Speed::Unit::KT:
            return std::to_string(*kt) + " knots (" +
                   std::to_string(*mps) + " m/s, " +
                   std::to_string(*kmh) + " km/h, " +
                   std::to_string(*mph) + " mph)";
        case Speed::Unit::MPS:
            return std::to_string(*mps) + " m/s (" +
                   std::to_string(*kt) + " kt, " +
                   std::to_string(*kmh) + " km/h, " +
                   std::to_string(*mph) + " mph)";
        case Speed::Unit::KMH:
            return std::to_string(*kmh) + " km/h (" +
                   std::to_string(*kt) + " kt, " +
                   std::to_string(*mps) + " m/s, " +
                   std::to_string(*mph) + " mph)";
        case Speed::Unit::MPH:
            return std::to_string(*mph) + " mph (" +
                   std::to_string(*kt) + " kt, " +
                   std::to_string(*mps) + " m/s, " +
                   std::to_string(*kmh) + " km/h)";
    }
}

std::string toStr(const Distance& d) {
    auto mileFraction = [](Distance::Fraction f) {
        switch (f) {
            case Distance::Fraction::F_0:
                return ""s;
            case Distance::Fraction::F_1_16:
                return "1/16"s;
            case Distance::Fraction::F_1_8:
                return "1/8"s;
            case Distance::Fraction::F_3_16:
                return "3/16"s;
            case Distance::Fraction::F_1_4:
                return "1/4"s;
            case Distance::Fraction::F_5_16:
                return "5/16"s;
            case Distance::Fraction::F_3_8:
                return "3/8"s;
            case Distance::Fraction::F_7_16:
                return "7/16"s;
            case Distance::Fraction::F_1_2:
                return "1/2"s;
            case Distance::Fraction::F_9_16:
                return "9/16"s;
            case Distance::Fraction::F_5_8:
                return "5/8"s;
            case Distance::Fraction::F_11_16:
                return "11/16"s;
            case Distance::Fraction::F_3_4:
                return "3/4"s;
            case Distance::Fraction::F_13_16:
                return "13/16"s;
            case Distance::Fraction::F_7_8:
                return "7/8"s;
            case Distance::Fraction::F_15_16:
                return "15/16"s;
        }
    };
    auto details = [](Distance::Details d) {
        switch (d) {
            case Distance::Details::EXACTLY:
                return ""s;
            case Distance::Details::LESS_THAN:
                return "<"s;
            case Distance::Details::MORE_THAN:
                return ">"s;
        }
    };
    auto statuteMiles = [=](int i, Distance::Fraction f) {
        if (!i && f == Distance::Fraction::F_0) return std::to_string(i);
        if (!i) return mileFraction(f);
        return std::to_string(i) + " " + mileFraction(f);
    };
    const auto dt = details(d.details);
    const auto m = d.toUnit(Distance::Unit::METERS);
    const auto ft = d.toUnit(Distance::Unit::FEET);
    const auto sm = d.milesInt();
    if (!m.has_value() || !ft.has_value() || !sm.has_value()) return "";
    const auto smStr = statuteMiles(*sm, d.milesFraction());
    switch (d.unit) {
        case Distance::Unit::METERS:
            if (*ft < 10000) {  // 10000 is an arbitrary value here
                return dt + std::to_string(*m) + " m (" +
                       dt + std::to_string(*ft) + " ft, " +
                       dt + smStr + " statute miles)";
            }
            return dt + std::to_string(*m / 1000.0) + " km (" +
                   dt + smStr + " statute miles)";
        case Distance::Unit::STATUTE_MILES:
        case Distance::Unit::STATUTE_MILE_1_16S:
            if (*ft < 10000) {  // 10000 is an arbitrary value here
                return dt + smStr + " statute miles (" +
                       dt + std::to_string(*ft) + " ft, " +
                       dt + std::to_string(*m) + " m)";
            }
            return dt + smStr + " statute miles (" +
                   dt + std::to_string(*m / 1000.0) + " km)";
        case Distance::Unit::FEET:
            return dt + std::to_string(*ft) + " ft (" +
                   dt + smStr + " statute miles, " +
                   dt + std::to_string(*m) + " m)";
    }
}

std::string toStr(const DistanceRange& d) {
    std::string result = toStr(d.prevailing);
    const auto min = toStr(d.minimum);
    const auto max = toStr(d.maximum);
    if (min.empty() && max.empty()) return result;
    if (!result.empty()) result += ", variable";
    if (!min.empty()) {
        result += " from ";
        result += min;
    }
    if (!max.empty()) {
        result += " up to ";
        result += max;
    }
    return result;
}

std::string toStr(const Height& h) {
    const auto ft = h.toUnit(Height::Unit::FEET);
    const auto m = h.toUnit(Height::Unit::METERS);
    if (!ft.has_value() || !m.has_value()) return "";
    switch (h.unit) {
        case Height::Unit::FEET:
            return std::to_string(*ft) + " ft (" + std::to_string(*m) + " m)";
        case Height::Unit::METERS:
            return std::to_string(*m) + " m (" + std::to_string(*ft) + " ft)";
    }
}

std::string toStr(const Ceiling& c) {
    std::string result = toStr(c.exact);
    const auto min = toStr(c.minimum);
    const auto max = toStr(c.maximum);
    if (min.empty() && max.empty()) return result;
    if (!result.empty()) result += ", variable";
    if (!min.empty()) {
        result += " from ";
        result += min;
    }
    if (!max.empty()) {
        result += " up to ";
        result += max;
    }
    return result;
}

std::string toStr(const Pressure& p) {
    const auto hpa = p.toUnit(Pressure::Unit::HPA);
    const auto inhg = p.toUnit(Pressure::Unit::IN_HG);
    const auto mmhg = p.toUnit(Pressure::Unit::MM_HG);
    if (!hpa.has_value() || !inhg.has_value() || !mmhg.has_value())
        return "";
    switch (p.unit) {
        case Pressure::Unit::HPA:
            return std::to_string(*hpa) + " hPa (" +
                   std::to_string(*inhg) + " \"Hg, " +
                   std::to_string(*mmhg) + " mmHg)";
        case Pressure::Unit::IN_HG:
        case Pressure::Unit::HUNDREDTHS_IN_HG:
            return std::to_string(*inhg) + " \"Hg (" +
                   std::to_string(*hpa) + " hPa, " +
                   std::to_string(*mmhg) + " mmHg)";
        case Pressure::Unit::MM_HG:
            return std::to_string(*mmhg) + " mmHg (" +
                   std::to_string(*hpa) + " hPa, " +
                   std::to_string(*inhg) + " \"Hg)";
    }
}

std::string toStr(const Precipitation& p) {
    const auto in = p.toUnit(Precipitation::Unit::IN);
    const auto mm = p.toUnit(Precipitation::Unit::MM);
    if (!in.has_value() || !mm.has_value()) return "";
    switch (p.unit) {
        case Precipitation::Unit::IN:
        case Precipitation::Unit::HUNDREDTHS_IN:
            return std::to_string(*in) + " \" (" + std::to_string(*mm) + " mm)";
        case Precipitation::Unit::MM:
            return std::to_string(*mm) + " mm (" + std::to_string(*in) + " \")";
    }
}

std::string toStr(const WaveHeight& wh) {
    const auto m = wh.toUnit(WaveHeight::Unit::METERS);
    const auto ft = wh.toUnit(WaveHeight::Unit::FEET);
    const auto yd = wh.toUnit(WaveHeight::Unit::YARDS);
    if (!m.has_value() || !ft.has_value() || !yd.has_value()) return "";
    switch (wh.unit) {
        case WaveHeight::Unit::METERS:
        case WaveHeight::Unit::DECIMETERS:
            return std::to_string(*m) + " m (" +
                   std::to_string(*ft) + " ft" +
                   std::to_string(*yd) + "yd)";
        case WaveHeight::Unit::FEET:
            return std::to_string(*ft) + " ft (" +
                   std::to_string(*m) + " m" +
                   std::to_string(*yd) + "yd)";
        case WaveHeight::Unit::YARDS:
            return std::to_string(*yd) + " yd (" +
                   std::to_string(*m) + " m" +
                   std::to_string(*ft) + "ft)";
    }
}

std::string toStr(const Weather& w) {
    auto phenomena = [](Weather::Phenomena p) {
        switch (p) {
            case Weather::Phenomena::UNKNOWN:
                return "";
            case Weather::Phenomena::NO_SIGNIFICANT_WEATHER:
                return "no significant weather (indicates the end of previous "
                       "weather phenomena)";
            case Weather::Phenomena::SHALLOW_FOG:
                return "shallow fog (ground fog)";
            case Weather::Phenomena::PARTIAL_FOG:
                return "partial fog (fog covering part of the location)";
            case Weather::Phenomena::PATCHES_FOG:
                return "patches of fog (randomly covering the location)";
            case Weather::Phenomena::FREEZING_FOG:
                return "freezing fog or fog at freezing temperatures";
            case Weather::Phenomena::FOG:
                return "fog";
            case Weather::Phenomena::DRIFTING_DUST:
                return "low drifting dust";
            case Weather::Phenomena::BLOWING_DUST:
                return "blowing dust";
            case Weather::Phenomena::DUST:
                return "widespread dust";
            case Weather::Phenomena::DRIFTING_SAND:
                return "low drifting sand";
            case Weather::Phenomena::BLOWING_SAND:
                return "blowing sand";
            case Weather::Phenomena::SAND:
                return "sand";
            case Weather::Phenomena::DRIFTING_SNOW:
                return "low drifting snow";
            case Weather::Phenomena::BLOWING_SNOW:
                return "blowing snow";
            case Weather::Phenomena::BLOWING_SPRAY:
                return "blowing spray";
            case Weather::Phenomena::ICE_CRYSTALS:
                return "ice crystals";
            case Weather::Phenomena::MIST:
                return "mist";
            case Weather::Phenomena::SMOKE:
                return "smoke";
            case Weather::Phenomena::VOLCANIC_ASH:
                return "volcanic ash";
            case Weather::Phenomena::HAZE:
                return "haze";
            case Weather::Phenomena::DUST_WHIRLS:
                return "dust or sand whirls";
            case Weather::Phenomena::SQUALLS:
                return "squalls";
            case Weather::Phenomena::FUNNEL_CLOUD:
                return "funnel cloud";
            case Weather::Phenomena::TORNADO:
                return "tornado";
            case Weather::Phenomena::SAND_STORM:
                return "sand storm";
            case Weather::Phenomena::DUST_STORM:
                return "dust storm";
            case Weather::Phenomena::DUST_SAND_STORM:
                return "dust and sand storm";
            case Weather::Phenomena::HEAVY_SAND_STORM:
                return "heavy sand storm";
            case Weather::Phenomena::HEAVY_DUST_STORM:
                return "heavy dust storm";
            case Weather::Phenomena::HEAVY_DUST_SAND_STORM:
                return "heavy dust and sand storm";
            case Weather::Phenomena::PRECIPITATION:
                return "precipitation";
            case Weather::Phenomena::SHOWERY_PRECIPITATION:
                return "showery precipitation";
            case Weather::Phenomena::PRECIPITATION_LIGHT:
                return "precipitation of light intensity";
            case Weather::Phenomena::PRECIPITATION_MODERATE:
                return "precipitation of moderate intensity";
            case Weather::Phenomena::PRECIPITATION_HEAVY:
                return "precipitation of heavy intensity";
            case Weather::Phenomena::SHOWERY_PRECIPITATION_LIGHT:
                return "showery precipitation of light intensity";
            case Weather::Phenomena::SHOWERY_PRECIPITATION_MODERATE:
                return "showery precipitation of moderate intensity";
            case Weather::Phenomena::SHOWERY_PRECIPITATION_HEAVY:
                return "showery precipitation of heavy intensity";
            case Weather::Phenomena::FREEZING_PRECIPITATION_LIGHT:
                return "freezing precipitation of light intensity";
            case Weather::Phenomena::FREEZING_PRECIPITATION_MODERATE:
                return "freezing precipitation of moderate intensity";
            case Weather::Phenomena::FREEZING_PRECIPITATION_HEAVY:
                return "freezing precipitation of heavy intensity";
            case Weather::Phenomena::THUNDERSTORM:
                return "thunderstorm";
            case Weather::Phenomena::THUNDERSTORM_PRECIPITATION_LIGHT:
                return "thunderstorm with precipitation of light intensity";
            case Weather::Phenomena::THUNDERSTORM_PRECIPITATION_MODERATE:
                return "thunderstorm with precipitation of moderate intensity";
            case Weather::Phenomena::THUNDERSTORM_PRECIPITATION_HEAVY:
                return "thunderstorm with precipitation of heavy intensity";
        }
    };
    auto precipitation = [](Weather::Precipitation p) {
        switch (p) {
            case Weather::Precipitation::DRIZZLE:
                return "drizzle";
            case Weather::Precipitation::RAIN:
                return "rain";
            case Weather::Precipitation::SNOW:
                return "snow";
            case Weather::Precipitation::SNOW_GRAINS:
                return "snow grains";
            case Weather::Precipitation::ICE_PELLETS:
                return "ice pellets";
            case Weather::Precipitation::HAIL:
                return "hail";
            case Weather::Precipitation::SMALL_HAIL:
                return "small hail (graupel)";
            case Weather::Precipitation::UNDETERMINED:
                return "undetermined precipitation";
        }
    };
    std::string result = phenomena(w.phenomena);
    for (const auto p : w.precipitation)
        result += ", "s + precipitation(p);
    return result;
}

std::string toStr(const CloudLayer& cl) {
    auto amount = [](CloudLayer::Amount a) {
        switch (a) {
            case CloudLayer::Amount::UNKNOWN:
                return "amount unknown";
            case CloudLayer::Amount::FEW:
                return "few clouds";
            case CloudLayer::Amount::SCATTERED:
                return "scattered clouds";
            case CloudLayer::Amount::BROKEN:
                return "broken clouds";
            case CloudLayer::Amount::OVERCAST:
                return "overcast";
            case CloudLayer::Amount::VARIABLE_FEW_SCATTERED:
                return "variable between few and scattered clouds";
            case CloudLayer::Amount::VARIABLE_SCATTERED_BROKEN:
                return "variable between scattered and broken clouds";
            case CloudLayer::Amount::VARIABLE_BROKEN_OVERCAST:
                return "variable between broken clouds and overcast";
        }
    };
    auto details = [](CloudLayer::Details d) {
        switch (d) {
            case CloudLayer::Details::UNKNOWN:
                return "unknown";
            case CloudLayer::Details::NOT_TOWERING_CUMULUS_NOT_CUMULONIMBUS:
                return "non-convective";
            case CloudLayer::Details::CUMULONIMBUS:
                return "cumulonimbus";
            case CloudLayer::Details::TOWERING_CUMULUS:
                return "towering cumulus";
            case CloudLayer::Details::CUMULUS:
                return "cumulus";
            case CloudLayer::Details::CUMULUS_FRACTUS:
                return "cumulus fractus";
            case CloudLayer::Details::STRATOCUMULUS:
                return "stratocumulus";
            case CloudLayer::Details::NIMBOSTRATUS:
                return "nimbostratus";
            case CloudLayer::Details::STRATUS:
                return "stratus";
            case CloudLayer::Details::STRATUS_FRACTUS:
                return "stratus fractus";
            case CloudLayer::Details::ALTOSTRATUS:
                return "altostratus";
            case CloudLayer::Details::ALTOCUMULUS:
                return "altocumulus";
            case CloudLayer::Details::ALTOCUMULUS_CASTELLANUS:
                return "altocumulus castellanus";
            case CloudLayer::Details::CIRRUS:
                return "cirrus";
            case CloudLayer::Details::CIRROSTRATUS:
                return "cirrostratus";
            case CloudLayer::Details::CIRROCUMULUS:
                return "cirrocumulus";
            case CloudLayer::Details::BLOWING_SNOW:
                return "blowing snow";
            case CloudLayer::Details::BLOWING_DUST:
                return "blowing dust";
            case CloudLayer::Details::BLOWING_SAND:
                return "blowing sand";
            case CloudLayer::Details::ICE_CRYSTALS:
                return "ice crystals";
            case CloudLayer::Details::RAIN:
                return "rain";
            case CloudLayer::Details::DRIZZLE:
                return "drizzle";
            case CloudLayer::Details::SNOW:
                return "snow";
            case CloudLayer::Details::ICE_PELLETS:
                return "ice pellets";
            case CloudLayer::Details::SMOKE:
                return "smoke";
            case CloudLayer::Details::FOG:
                return "fog";
            case CloudLayer::Details::MIST:
                return "mist";
            case CloudLayer::Details::HAZE:
                return "haze";
            case CloudLayer::Details::VOLCANIC_ASH:
                return "volcanic ash";
        }
    };
    std::string result = amount(cl.amount) + ", "s + details(cl.details);
    if (cl.height.height.has_value())
        result += " at height "s + toStr(cl.height);
    if (const auto s = toStr(cl.okta); !s.empty())
        result += " covering "s + s + "/8 of the sky"s + newLine;
    return result;
}

std::string toStr(ObservedPhenomena p) {
    switch (p) {
        case ObservedPhenomena::THUNDERSTORM:
            return "thunderstorm";
        case ObservedPhenomena::CUMULONIMBUS:
            return "cumulonimbus clouds";
        case ObservedPhenomena::CUMULONIMBUS_MAMMATUS:
            return "cumulonimbus mammatus clouds";
        case ObservedPhenomena::TOWERING_CUMULUS:
            return "towering cumulus clouds";
        case ObservedPhenomena::ALTOCUMULUS_CASTELLANUS:
            return "altocumulus castellanus clouds";
        case ObservedPhenomena::STRATOCUMULUS_STANDING_LENTICULAR:
            return "stratocumulus standing lenticular cloud";
        case ObservedPhenomena::ALTOCUMULUS_STANDING_LENTICULAR:
            return "stratocumulus standing lenticular cloud";
        case ObservedPhenomena::CIRROCUMULUS_STANDING_LENTICULAR:
            return "cirrocumulus standing lenticular cloud";
        case ObservedPhenomena::ROTOR_CLOUD:
            return "rotor cloud";
        case ObservedPhenomena::VIRGA:
            return "virga";
        case ObservedPhenomena::PRECIPITATION:
            return "precipitation";
        case ObservedPhenomena::FOG:
            return "fog";
        case ObservedPhenomena::FOG_SHALLOW:
            return "shallow fog";
        case ObservedPhenomena::FOG_PATCHES:
            return "patches of fog";
        case ObservedPhenomena::HAZE:
            return "haze";
        case ObservedPhenomena::SMOKE:
            return "smoke";
        case ObservedPhenomena::BLOWING_SNOW:
            return "blowing snow";
        case ObservedPhenomena::BLOWING_SAND:
            return "blowing sand";
        case ObservedPhenomena::BLOWING_DUST:
            return "blowing dust";
        case ObservedPhenomena::DUST_WHIRLS:
            return "dust or sand whirls";
        case ObservedPhenomena::SAND_STORM:
            return "sand storm";
        case ObservedPhenomena::DUST_STORM:
            return "dust storm";
        case ObservedPhenomena::VOLCANIC_ASH:
            return "volcanic ash";
        case ObservedPhenomena::FUNNEL_CLOUD:
            return "funnel cloud";
    }
}

std::string toStr(const Vicinity& v) {
    std::ostringstream result;
    result << toStr(v.phenomena);
    if (!v.directions.empty()) {
        result << "towards ";
        bool comma = false;
        for (const auto d : v.directions) {
            if (comma) result << ", ";
            comma = true;
            result << toStr(d);
        }
    }
    if (const auto s = toStr(v.distance); !s.empty())
        result << " at distance " << s;
    if (v.moving != CardinalDirection::NOT_SPECIFIED)
        result << " moving towards " << toStr(v.moving);
    return result.str();
}

std::string toStr(const LightningStrikes& ls) {
    auto freq = [](LightningStrikes::Frequency f) {
        switch (f) {
            case LightningStrikes::Frequency::UNKNOWN:
                return "";
            case LightningStrikes::Frequency::OCCASIONAL:
                return "occassional";
            case LightningStrikes::Frequency::FREQUENT:
                return "frequent";
            case LightningStrikes::Frequency::CONSTANT:
                return "constant";
        }
    };
    auto lightningType = [](LightningStrikes::Type t) {
        switch (t) {
            case LightningStrikes::Type::UNKNOWN:
                return "unknown lightning type";
            case LightningStrikes::Type::CLOUD_AIR:
                return "cloud-to-air without strike to ground";
            case LightningStrikes::Type::CLOUD_CLOUD:
                return "cloud-to-cloud";
            case LightningStrikes::Type::IN_CLOUD:
                return "in cloud";
            case LightningStrikes::Type::CLOUD_GROUND:
                return "cloud-to-ground";
        }
    };
    std::ostringstream result;
    if (ls.frequency != LightningStrikes::Frequency::UNKNOWN)
        result << freq(ls.frequency) << " ";
    result << "lightning strikes";
    if (!ls.type.empty()) {
        bool comma = false;
        for (auto t : ls.type) {
            if (comma) result << ", ";
            comma = true;
            result << lightningType(t);
        }
    }
    if (const auto s = toStr(ls.distance); !s.empty())
        result << " at distance " << s;
    if (!ls.directions.empty()) {
        result << "towards ";
        bool comma = false;
        for (const auto d : ls.directions) {
            if (comma) result << ", ";
            comma = true;
            result << toStr(d);
        }
    }
    return result.str();
}

std::string toStr(const WindShear& ws) {
    std::ostringstream result;
    if (ws.height.height.has_value())
        result << "at height " << toStr(ws.height) << ", ";
    result << "wind direction is " << std::to_string(ws.directionDegrees);
    result << " and wind speed is " << toStr(ws.windSpeed);
    return result.str();
}

std::string toStr(const Essentials& e, bool list = false) {
    auto skyCondition = [](Essentials::SkyCondition sc) {
        switch (sc) {
            case Essentials::SkyCondition::UNKNOWN:
                return "";
            case Essentials::SkyCondition::CLEAR_CLR:
                return "clear sky (station is at least partly automated)";
            case Essentials::SkyCondition::CLEAR_SKC:
                return "clear sky (report produced by human observer)";
            case Essentials::SkyCondition::CLEAR_NCD:
                return "clear sky, no clouds detected by automated station";
            case Essentials::SkyCondition::NO_SIGNIFICANT_CLOUD:
                return "no significant cloud";
            case Essentials::SkyCondition::CAVOK:
                return "ceiling and visibility OK";
            case Essentials::SkyCondition::CLOUDS:
                return "one or more cloud layer in the sky";
            case Essentials::SkyCondition::OBSCURED:
                return "sky obscured";
        }
    };
    std::ostringstream result;
    if (e.windDirectionDegrees.has_value()) {
        if (list) result << newItem;
        result << "windDirectionDegrees: wind direction ";
        result << toStr(e.windDirectionDegrees) << " degrees" << newLine;
    }
    if (e.windDirectionVariable) {
        if (list) result << newItem;
        result << "windDirectionVariable: wind direction is variable, no ";
        result << "mean direction" << newLine;
    }
    if (e.windDirectionVarFromDegrees.has_value()) {
        if (list) result << newItem;
        result << "windDirectionVarFromDegrees: wind direction is variable ";
        result << "in a sector clockwise from ";
        result << toStr(e.windDirectionVarFromDegrees) << " degrees" << newLine;
    }
    if (e.windDirectionVarToDegrees.has_value()) {
        if (list) result << newItem;
        result << "windDirectionVarToDegrees: wind direction is variable ";
        result << "in a sector clockwise to ";
        result << toStr(e.windDirectionVarToDegrees) << " degrees" << newLine;
    }
    if (e.windSpeed.speed.has_value()) {
        if (list) result << newItem;
        result << "windSpeed: sustained wind speed is " << toStr(e.windSpeed);
        result << newLine;
    }
    if (e.gustSpeed.speed.has_value()) {
        if (list) result << newItem;
        result << "gustSpeed: wind gust speed is " << toStr(e.gustSpeed);
        result << newLine;
    }
    if (e.windCalm) {
        if (list) result << newItem;
        result << "windCalm: calm wind (no wind)" << newLine;
    }
    if (e.visibility.distance.has_value()) {
        if (list) result << newItem;
        result << "visibility: prevailing visibility is ";
        result << toStr(e.visibility) << newLine;
    }
    if (e.cavok) {
        if (list) result << newItem;
        result << "cavok: ceiling and visibility OK, visibility 10 km or more "
                  "in all directions, no cloud below 5000 feet (1500 meters), "
                  "no cumulonimbus, no towering cumulus, no significant "
                  "weather phenomena";
        result << newLine;
    }
    if (e.skyCondition != Essentials::SkyCondition::UNKNOWN)
        if (list) result << newItem;
        result << "skyCondition: " << skyCondition(e.skyCondition) << newLine;
    if (!e.cloudLayers.empty()) {
        if (list) result << newItem;
        result << "cloudLayers: the following cloud layers are present";
        result << newLine;
        for (const auto& c : e.cloudLayers) {
            result << newItem << toStr(c) << newLine;
        }
    }
    if (e.verticalVisibility.height.has_value()) {
        if (list) result << newItem;
        result << "verticalVisibility: vertical visibility is ";
        result << toStr(e.verticalVisibility) << newLine;
    }
    if (!e.weather.empty()) {
        if (list) result << newItem;
        result << "weather: the following weather phenomena occur" << newLine;
        for (const auto& w : e.weather) {
            result << newItem << toStr(w) << newLine;
        }
    }
    if (e.seaLevelPressure.pressure.has_value()) {
        if (list) result << newItem;
        result << "seaLevelPressure: the atmospheric pressure normalised to ";
        result << "sea level is " << toStr(e.seaLevelPressure) << newLine;
    }
    if (!e.windShear.empty()) {
        if (list) result << newItem;
        result << "windShear: the wind shear is as as follows" << newLine;
        for (const auto& ws : e.windShear) {
            result << newItem << toStr(ws) << newLine;
        }
    }
    return result.str();
}

std::string toStr(const Report& report) {
    auto type = [](Report::Type t) {
        switch (t) {
            case Report::Type::METAR:
                return "METAR (weather observation report)";
            case Report::Type::SPECI:
                return "unscheduled METAR (weather observation report)";
            case Report::Type::TAF:
                return "TAF (terminal aerodrome forecast)";
            case Report::Type::ERROR:
                return "error occurred while parsing this report";
        }
    };
    auto error = [](Report::Error e) {
        switch (e) {
            case Report::Error::NO_ERROR:
                return "no error";
            case Report::Error::NO_REPORT_PARSED:
                return "no report parsed yet";
            case Report::Error::EMPTY_REPORT:
                return "empty report supplied";
            case Report::Error::UNKNOWN_REPORT_TYPE:
                return "unknown report type";
            case Report::Error::REPORT_TOO_LARGE:
                return "report has too many groups";
            case Report::Error::UNEXPECTED_REPORT_END:
                return "report unexpected report end reached";
            case Report::Error::REPORT_HEADER_FORMAT:
                return "invalid report header format";
            case Report::Error::NIL_OR_CNL_FORMAT:
                return "invalid format of missing or cancelled report";
            case Report::Error::GROUP_NOT_ALLOWED:
                return "report has a group incompatible with this report type";
        }
    };
    auto warningMessage = [](Report::Warning::Message m) {
        switch (m) {
            case Report::Warning::Message::INCONSISTENT_DATA:
                return "inconsistent data";
            case Report::Warning::Message::DUPLICATED_DATA:
                return "duplicated or conflicting data";
            case Report::Warning::Message::INVALID_GROUP:
                return "invalid group";
            case Report::Warning::Message::INVALID_TIME:
                return "conflicting ot missing time";
        }
    };
    auto warning = [=](const Report::Warning& w) {
        return w.id + ": " + warningMessage(w.message);
    };
    std::ostringstream result;
    result << "type: " << type(report.type) << newLine;
    if (report.missing)
        result << "missing: indicates missing report" << newLine;
    if (report.cancelled)
        result << "cancelled: cancels previous forecast" << newLine;
    if (report.correctional) {
        result << "correctional: corrects previous report" << newLine;
        if (report.correctionNumber) {
            result << "correctionNumber: " << report.correctionNumber;
            result << " (this is the ";
            result << ordinalNumber(report.correctionNumber) << " correction)";
            result << newLine;
        }
    }
    if (report.amended)
        result << "ameded: amends previous report" << newLine;
    if (report.automated) {
        result << "automated: fully automated report produced with no ";
        result << "human intervention or oversight" << newLine;
    }
    if (const auto t = toStr(report.reportTime); !t.empty())
        result << "reportTime: report released on " << t << newLine;
    if (const auto t = toStr(report.applicableFrom); !t.empty())
        result << "applicableFrom: report is applicable from " << t << newLine;
    if (const auto t = toStr(report.applicableUntil); !t.empty()) {
        result << "applicableUntil: report is applicable until " << t;
        result << newLine;
    }
    if (report.error != Report::Error::NO_ERROR)
        result << "error: " << error(report.error) << newLine;
    if (!report.warnings.empty()) {
        result << "warnings: the following warnings were generated ";
        result << "while processing this report" << newLine;
        for (const auto& w : report.warnings) {
            result << newItem << warning(w) << newLine;
        }
    }
    if (!report.plainText.empty()) {
        result << "plainText: unable to decode the following group(s) in this ";
        result << "report (possibly they are plain text remarks)" << newLine;
        for (const auto& pt : report.plainText) {
            result << newItem << pt << newLine;
        }
    }

    return result.str();
}

std::string toStr(const Station& station) {
    auto autoType = [](Station::AutoType at) {
        switch (at) {
            case Station::AutoType::NONE:
                return "";
            case Station::AutoType::AO1:
                return "This automated station is not equipped with a "
                       "precipitation discriminator";
            case Station::AutoType::AO1A:
                return "This automated station is not equipped with a "
                       "precipitation discriminator and observation is "
                       "augmented by a human observer";
            case Station::AutoType::AO2:
                return "This automated station is equipped with a "
                       "precipitation discriminator";
            case Station::AutoType::AO2A:
                return "This automated station is equipped with a "
                       "precipitation discriminator and observation is "
                       "augmented by a human observer";
        }
    };
    auto missingData = [](Station::MissingData md) {
        switch (md) {
            case Station::MissingData::WND_MISG:
                return "wind data is missing";
            case Station::MissingData::VIS_MISG:
                return "visibility data is missing";
            case Station::MissingData::RVR_MISG:
                return "runway visual range data is missing";
            case Station::MissingData::RVRNO:
                return "runway visual range should be present"
                       " but not available";
            case Station::MissingData::VISNO:
                return "visibility data not available";
            case Station::MissingData::VISNO_RUNWAY:
                return "visibility data not available for at least one runway";
            case Station::MissingData::VISNO_DIRECTION:
                return "visibility data not available for at least one "
                       "cardinal direction";
            case Station::MissingData::CHINO:
                return "ceiling data not available";
            case Station::MissingData::CHINO_RUNWAY:
                return "ceiling data not available for at least one runway";
            case Station::MissingData::CHINO_DIRECTION:
                return "ceiling data not available for at least one "
                       "cardinal direction";
            case Station::MissingData::PWINO:
                return "this automated station is equipped with "
                       "present weather identifier "
                       "and this sensor is not operating";
            case Station::MissingData::TSNO:
                return "this automated station is equipped with lightning "
                       "detector and this sensor is not operating";
            case Station::MissingData::PNO:
                return "this automated station is equipped with tipping "
                       "bucket rain gauge and this sensor is not operating";
            case Station::MissingData::FZRANO:
                return "this automated station is equipped with freezing rain "
                       "sensor and this sensor is not operating";
            case Station::MissingData::SLPNO:
                return "mean sea-level pressure information is not available";
            case Station::MissingData::TS_LTNG_TEMPO_UNAVBL:
                return "thunderstorm and lightning data is missing";
            case Station::MissingData::CLD_MISG:
                return "sky condition data is missing";
            case Station::MissingData::WX_MISG:
                return "weather phenomena data is missing";
            case Station::MissingData::T_MISG:
                return "temperature data is missing";
            case Station::MissingData::TD_MISG:
                return "dew point data is missing";
            case Station::MissingData::PRES_MISG:
                return "atmospheric pressure data is missing";
            case Station::MissingData::ICG_MISG:
                return "icing data is missing";
            case Station::MissingData::PCPN_MISG:
                return "precipitation data is missing";
        }
    };
    std::ostringstream result;
    result << "icaoCode: station ICAO code " << station.icaoCode << newLine;
    if (station.autoType != Station::AutoType::NONE) {
        result << "autoType: ";
        result << autoType(station.autoType) << newLine;
    }
    if (station.requiresMaintenance) {
        result << "requiresMaintenance: ";
        result << "automated station requires maintenance" << newLine;
    }
    if (station.noSpeciReports) {
        result << "noSpeciReports: this station does not issue SPECI reports";
        result << newLine;
    }
    if (station.noVisDirectionalVariation) {
        result << "noVisDirectionalVariation: this station cannot ";
        result << "differentiate the directional variation of visibility";
        result << newLine;
    }
    if (!station.missingData.empty()) {
        result << "missingData: the following data are missing" << newLine;
        for (const auto md : station.missingData) {
            result << newItem << missingData(md) << newLine;
        }
    }
    if (!station.runwaysNoCeilingData.empty()) {
        result << "runwaysNoCeilingData: ceiling data is missing for the ";
        result << "following runways" << newLine;
        for (const auto rw : station.runwaysNoCeilingData) {
            result << newItem << "runway " << toStr(rw) << newLine;
        }
    }
    if (!station.runwaysNoVisData.empty()) {
        result << "runwaysNoVisData: visibility data is missing for the ";
        result << "following runways" << newLine;
        for (const auto rw : station.runwaysNoVisData) {
            result << newItem << "runway " << toStr(rw) << newLine;
        }
    }
    if (!station.directionsNoCeilingData.empty()) {
        result << "directionsNoCeilingData: ceiling data is missing for the ";
        result << "following directions" << newLine;
        for (const auto rw : station.directionsNoCeilingData) {
            result << newItem << "runway " << toStr(rw) << newLine;
        }
    }
    if (!station.directionsNoVisData.empty()) {
        result << "directionsNoVisData: visibility data is missing for the ";
        result << "following directions" << newLine;
        for (const auto rw : station.directionsNoVisData) {
            result << newItem << "runway " << toStr(rw) << newLine;
        }
    }
    return result.str();
}

std::string toStr(const Aerodrome& aerodrome) {
    auto colourCode = [](Aerodrome::ColourCode c) {
        switch (c) {
            case Aerodrome::ColourCode::NOT_SPECIFIED:
                return "";
            case Aerodrome::ColourCode::BLUE:
                return "blue";
            case Aerodrome::ColourCode::WHITE:
                return "white";
            case Aerodrome::ColourCode::GREEN:
                return "green";
            case Aerodrome::ColourCode::YELLOW1:
                return "yellow1";
            case Aerodrome::ColourCode::YELLOW2:
                return "yellow2";
            case Aerodrome::ColourCode::AMBER:
                return "amber";
            case Aerodrome::ColourCode::RED:
                return "red";
        }
    };
    auto rvrTrend = [](Aerodrome::RvrTrend r) {
        switch (r) {
            case Aerodrome::RvrTrend::UNKNOWN:
                return "";
            case Aerodrome::RvrTrend::DOWNWARD:
                return "downward";
            case Aerodrome::RvrTrend::NEUTRAL:
                return "neutral";
            case Aerodrome::RvrTrend::UPWARD:
                return "upward";
        }
    };
    auto runwayDeposits = [](Aerodrome::RunwayDeposits d) {
        switch (d) {
            case Aerodrome::RunwayDeposits::UNKNOWN:
                return "";
            case Aerodrome::RunwayDeposits::CLEAR_AND_DRY:
                return "clear and dry";
            case Aerodrome::RunwayDeposits::DAMP:
                return "damp";
            case Aerodrome::RunwayDeposits::WET_AND_WATER_PATCHES:
                return "wet and there are water patches";
            case Aerodrome::RunwayDeposits::RIME_AND_FROST_COVERED:
                return "rime and frost covered";
            case Aerodrome::RunwayDeposits::DRY_SNOW:
                return "dry snow covered";
            case Aerodrome::RunwayDeposits::WET_SNOW:
                return "wet snow covered";
            case Aerodrome::RunwayDeposits::SLUSH:
                return "slush covered";
            case Aerodrome::RunwayDeposits::ICE:
                return "ice covered";
            case Aerodrome::RunwayDeposits::COMPACTED_OR_ROLLED_SNOW:
                return "covered in compacted or rolled snow";
            case Aerodrome::RunwayDeposits::FROZEN_RUTS_OR_RIDGES:
                return "ice or snow covered with frozen ruts or ridges";
        }
    };
    auto runwayContamExtent = [](Aerodrome::RunwayContamExtent r) {
        switch (r) {
            case Aerodrome::RunwayContamExtent::UNKNOWN:
                return "";
            case Aerodrome::RunwayContamExtent::NO_DEPOSITS:
                return "none";
            case Aerodrome::RunwayContamExtent::LESS_THAN_11_PERCENT:
                return "less than 11 percent";
            case Aerodrome::RunwayContamExtent::FROM_11_TO_25_PERCENT:
                return "11 to 25 percent";
            case Aerodrome::RunwayContamExtent::FROM_26_TO_50_PERCENT:
                return "26 to 50 percent";
            case Aerodrome::RunwayContamExtent::MORE_THAN_50_PERCENT:
                return "more than 50 percent";
        }
    };
    auto brakingAction = [](Aerodrome::BrakingAction ba) {
        switch (ba) {
            case Aerodrome::BrakingAction::UNKNOWN:
                return "";
            case Aerodrome::BrakingAction::POOR:
                return "poor";
            case Aerodrome::BrakingAction::MEDIUM_POOR:
                return "medium-poor";
            case Aerodrome::BrakingAction::MEDIUM:
                return "medium";
            case Aerodrome::BrakingAction::MEDIUM_GOOD:
                return "medium-good";
            case Aerodrome::BrakingAction::GOOD:
                return "good";
            case Aerodrome::BrakingAction::UNRELIABLE:
                return "unreliable or unmeasurable";
        }
    };
    auto runwayData = [&](const Aerodrome::RunwayData& rd,
                          bool includeRunway = false) {
        std::ostringstream result;
        if (includeRunway)
            result << newItem << "runway: " << toStr(rd.runway) << newLine;
        if (rd.notOperational) {
            result << newItem << "notOperational: runway not operational";
            result << newLine;
        }
        if (rd.snoclo) {
            result << newItem << "snoclo: ";
            result << "runway closed due to snow accumulation" << newLine;
        }
        if (rd.clrd) {
            result << newItem << "clrd: deposits cleared or ceased to exist";
            result << newLine;
        }
        if (rd.windShearLowerLayers) {
            result << newItem << "windShearLowerLayers: ";
            result << "wind shear in the lower layers" << newLine;
        }
        if (rd.deposits != Aerodrome::RunwayDeposits::UNKNOWN) {
            result << newItem << "deposits: runway is ";
            result << runwayDeposits(rd.deposits) << newLine;
        }
        if (rd.contaminationExtent != Aerodrome::RunwayContamExtent::UNKNOWN) {
            result << newItem << "contaminationExtent: ";
            result << runwayContamExtent(rd.contaminationExtent);
            result << " of runway covered with deposits" << newLine;
        }
        if (rd.depositDepth.amount.has_value()) {
            result << newItem << "depositDepth: runway deposit depth ";
            result << toStr(rd.depositDepth) << newLine;
        }
        if (rd.coefficient.has_value()) {
            result << newItem << "coefficient: friction coefficient 0.";
            result << toStr(rd.coefficient) << ", braking action ";
            result << brakingAction(rd.brakingAction()) << newLine;
        }
        if (rd.surfaceFrictionUnreliable) {
            result << newItem << "surfaceFrictionUnreliable: ";
            result << "surface friction unrealiable or unmeasureable" << newLine;
        }
        if (const auto s = toStr(rd.visualRange); !s.empty()) {
            result << newItem << "visualRange: runway visual range is ";
            result << s << newLine;
        }
        if (rd.visualRangeTrend != Aerodrome::RvrTrend::UNKNOWN) {
            result << newItem << "visualRangeTrend: ";
            result << "runway visual range trend is ";
            result << rvrTrend(rd.visualRangeTrend) << newLine;
        }
        if (const auto s = toStr(rd.ceiling); !s.empty())
            result << newItem << "ceiling: ceiling is " << s << newLine;
        if (const auto s = toStr(rd.visibility); !s.empty()) {
            result << newItem << "visibility: runway visibility is ";
            result << s << newLine;
        }
        return result.str();
    };
    auto directionData = [](const Aerodrome::DirectionData& dd,
                            bool includeDirection = false) {
        std::ostringstream result;
        if (includeDirection)
            result << newItem << toStr(dd.cardinalDirection) << newLine;
        if (const auto s = toStr(dd.visibility); !s.empty()) {
            result << newItem << "visibility: directional visibility is ";
            result << s << newLine;
        }
        if (const auto s = toStr(dd.ceiling); !s.empty())
            result << newItem << "ceiling: ceiling is " << s << newLine;
        return result.str();
    };
    std::ostringstream result;
    if (aerodrome.snoclo) {
        result << "snoclo: aerodrome closed due to snow accumulation";
        result << newLine;
    }
    if (aerodrome.colourCode != Aerodrome::ColourCode::NOT_SPECIFIED)
        result << "colourCode: " << colourCode(aerodrome.colourCode) << newLine;
    if (aerodrome.colourCodeBlack) {
        result << "colourCodeBlack: aerodrome closed due to snow accumulation ";
        result << "or non-weather reasons" << newLine;
    }
    if (!aerodrome.runways.empty()) {
        for (const auto& r : aerodrome.runways) {
            result << "runways: data for runway " << toStr(r.runway) << newLine;
            result << runwayData(r);
        }
    }
    if (!aerodrome.directions.empty()) {
        for (const auto& d : aerodrome.directions) {
            result << "directions: data for direction towards";
            result << toStr(d.cardinalDirection) << newLine;
            result << directionData(d);
        }
    }
    if (const auto s = toStr(aerodrome.ceiling); !s.empty())
        result << "ceiling: ceiling is " << s << newLine;
    if (const auto s = toStr(aerodrome.surfaceVisibility); !s.empty()) {
        result << "surfaceVisibility: visibility on surface level is ";
        result << s << newLine;
    }
    if (const auto s = toStr(aerodrome.towerVisibility); !s.empty()) {
        result << "towerVisibility: visibility from ATC tower is ";
        result << s << newLine;
    }
    return result.str();
}

std::string toStr(const Current& current) {
    const auto lowCloudLayer = [](Current::LowCloudLayer l) {
        switch (l) {
            case Current::LowCloudLayer::UNKNOWN:
                return "";
            case Current::LowCloudLayer::NO_CLOUDS:
                return "absent";
            case Current::LowCloudLayer::CU_HU_CU_FR:
                return "Cumulus Humilis and/or Cumulus Fractus";
            case Current::LowCloudLayer::CU_MED_CU_CON:
                return "Cumulus Mediocris or Cumulus Congestus";
            case Current::LowCloudLayer::CB_CAL:
                return "Cumulonimbus Calvus";
            case Current::LowCloudLayer::SC_CUGEN:
                return "Stratocumulus Cumulogenitus";
            case Current::LowCloudLayer::SC_NON_CUGEN:
                return "Stratocumulus Non-Cumulogenitus";
            case Current::LowCloudLayer::ST_NEB_ST_FR:
                return "Stratus Nebulosus and/or Stratus Fractus of dry "
                       "weather";
            case Current::LowCloudLayer::ST_FR_CU_FR_PANNUS:
                return "Stratus Fractus and/or Cumulus Fractus of wet weather";
            case Current::LowCloudLayer::CU_SC_NON_CUGEN_DIFFERENT_LEVELS:
                return "Cumulus and Stratocumulus with bases at different "
                       "levels";
            case Current::LowCloudLayer::CB_CAP:
                return "Cumulonimbus Capillatus or Cumulonimbus Capillatus "
                       "Incus";
        }
    };
    const auto midCloudLayer = [](Current::MidCloudLayer m) {
        switch (m) {
            case Current::MidCloudLayer::UNKNOWN:
                return "";
            case Current::MidCloudLayer::NO_CLOUDS:
                return "absent";
            case Current::MidCloudLayer::AS_TR:
                return "Altostratus Translucidus";
            case Current::MidCloudLayer::AS_OP_NS:
                return "Altostratus Opacus or Nimbostratus";
            case Current::MidCloudLayer::AC_TR:
                return "Altocumulus Translucidus at a single level "
                       "(mackerel sky)";
            case Current::MidCloudLayer::AC_TR_LEN_PATCHES:
                return "continually changing patches of Altocumulus "
                       "Translucidus";
            case Current::MidCloudLayer::AC_TR_AC_OP_SPREADING:
                return "Altocumulus Translucidus or Altocumulus Opacus, "
                       "spreading";
            case Current::MidCloudLayer::AC_CUGEN_AC_CBGEN:
                return "Altocumulus Cumulogenitus or Altocumulus "
                       "Cumulonimbogenitus";
            case Current::MidCloudLayer::AC_DU_AC_OP_AC_WITH_AS_OR_NS:
                return "Altocumulus Duplicatus, or Altocumulus Opacus (not "
                       "spreading), or Altocumulus with Altostratus or "
                       "Nimbostratus.";
            case Current::MidCloudLayer::AC_CAS_AC_FLO:
                return "Altocumulus Castellanus or Altocumulus Floccus";
            case Current::MidCloudLayer::AC_OF_CHAOTIC_SKY:
                return "Altocumuls of chaotic sky (variety of ill-defined cloud"
                       "types)";
        }
    };
    const auto highCloudLayer = [](Current::HighCloudLayer h) {
        switch (h) {
            case Current::HighCloudLayer::UNKNOWN:
                return "";
            case Current::HighCloudLayer::NO_CLOUDS:
                return "absent";
            case Current::HighCloudLayer::CI_FIB_CI_UNC:
                return "Cirrus Fibratus and/or Cirrus Uncinus, not spreading";
            case Current::HighCloudLayer::CI_SPI_CI_CAS_CI_FLO:
                return "Cirrus Spissatus or Cirrus Castellanus or Cirrus "
                       "Floccus)";
            case Current::HighCloudLayer::CI_SPI_CBGEN:
                return "Cirrus Spissatus Cumulonimbogenitus";
            case Current::HighCloudLayer::CI_FIB_CI_UNC_SPREADING:
                return "Cirrus Uncinus and/or Cirrus Fibratus, spreading";
            case Current::HighCloudLayer::CI_CS_LOW_ABOVE_HORIZON:
                return "Cirrostratus, possibly with Cirrus, spreading but below "
                       "45 degrees above the horizon";
            case Current::HighCloudLayer::CI_CS_HIGH_ABOVE_HORIZON:
                return "Cirrostratus, possibly with Cirrus, spreading but below "
                       "45 degrees above the horizon, not covering whole sky";
            case Current::HighCloudLayer::CS_NEB_CS_FIB_COVERING_ENTIRE_SKY:
                return "Cirrostratus Nebulosus or Cirrostratus Fibratus "
                       "covering whole sky";
            case Current::HighCloudLayer::CS:
                return "Cirrostratus not spreading and not covering whole sky";
            case Current::HighCloudLayer::CC:
                return "Cirrocumulus alone, or predominant among the "
                       "high-layer clouds";
        }
    };
    std::ostringstream result;
    result << "weatherData: essential weather data are below" << newLine;
    result << toStr(current.weatherData, true);
    if (const auto s = toStr(current.variableVisibility); !s.empty())
        result << "variableVisibility: visibility is variable " << s << newLine;
    if (!current.obscurations.empty()) {
        result << "obscurations: the following obscurations are present";
        result << newLine;
        for (const auto& c : current.obscurations) {
            result << newItem << toStr(c) << newLine;
        }
    }
    if (current.lowCloudLayer != Current::LowCloudLayer::UNKNOWN) {
        result << "lowCloudLayer: low cloud layer is ";
        result << lowCloudLayer(current.lowCloudLayer) << newLine;
    }
    if (current.midCloudLayer != Current::MidCloudLayer::UNKNOWN) {
        result << "midCloudLayer: middle cloud layer is ";
        result << midCloudLayer(current.midCloudLayer) << newLine;
    }
    if (current.highCloudLayer != Current::HighCloudLayer::UNKNOWN) {
        result << "highCloudLayer: high cloud layer is ";
        result << highCloudLayer(current.highCloudLayer) << newLine;
    }
    if (current.airTemperature.temperature.has_value()) {
        result << "airTemperature: ambient air temperature ";
        result << toStr(current.airTemperature) << newLine;
    }
    if (current.dewPoint.temperature.has_value())
        result << "dewPoint: dew point " << toStr(current.dewPoint) << newLine;
    if (current.relativeHumidity.has_value()) {
        result << "relativeHumidity: relative humidity ";
        result << toStr(current.relativeHumidity) << "%" << newLine;
    }
    if (current.pressureGroundLevel.pressure.has_value()) {
        result << "pressureGroundLevel: actual pressure at ground level ";
        result << toStr(current.pressureGroundLevel) << newLine;
    }
    if (current.seaSurfaceTemperature.temperature.has_value()) {
        result << "seaSurfaceTemperature: temperature of sea surface ";
        result << toStr(current.seaSurfaceTemperature) << newLine;
    }
    if (current.waveHeight.waveHeight.has_value()) {
        result << "waveHeight: sea wave height ";
        result << toStr(current.waveHeight) << newLine;
    }
    if (current.snowWaterEquivalent.amount.has_value()) {
        result << "snowWaterEquivalent: water equivalent of snow on ground ";
        result << toStr(current.snowWaterEquivalent) << newLine;
    }
    if (current.snowDepthOnGround.amount.has_value()) {
        result << "snowDepthOnGround: snow depth on ground ";
        result << toStr(current.snowDepthOnGround) << newLine;
    }
    if (current.snowIncreasingRapidly) {
        result << "snowIncreasingRapidly: snow increasing rapidly";
        result << newLine;
    }
    if (!current.phenomenaInVicinity.empty()) {
        result << "phenomenaInVicinity: the following phenomena are observed ";
        result << "in vicinity of the station" << newLine;
        for (const auto& v : current.phenomenaInVicinity)
            result << newItem << toStr(v) << newLine;
    }
    if (!current.lightningStrikes.empty()) {
        result << "lightningStrikes: lightning strikes are observed" << newLine;
        for (const auto& l : current.lightningStrikes)
            result << newItem << toStr(l) << newLine;
    }
    if (current.densityAltitude.height.has_value()) {
        result << "densityAltitude: density altitude is ";
        result << toStr(current.densityAltitude) << newLine;
    }
    if (current.hailstoneSizeQuartersInch.has_value()) {
        result << "hailstoneSizeQuartersInch: largest hailstone size ";
        result << toStr(current.hailstoneSizeQuartersInch);
        result << " quarters of inch" << newLine;
    }
    if (current.frostOnInstrument) {
        result << "frostOnInstrument: frost observed on the instrument";
        result << newLine;
    }
    return result.str();
}

std::string toStr(const Historical& historical) {
    auto pressureTendency = [](Historical::PressureTendency p) {
        switch (p) {
            case Historical::PressureTendency::UNKNOWN:
                return "";
            case Historical::PressureTendency::INCREASING_THEN_DECREASING:
                return "increasing then decreasing";
            case Historical::PressureTendency::INCREASING_MORE_SLOWLY:
                return "increasing more slowly";
            case Historical::PressureTendency::INCREASING:
                return "increasing";
            case Historical::PressureTendency::INCREASING_MORE_RAPIDLY:
                return "increasing more rapidly";
            case Historical::PressureTendency::STEADY:
                return "steady";
            case Historical::PressureTendency::DECREASING_THEN_INCREASING:
                return "decreasing then increasing";
            case Historical::PressureTendency::DECREASING_MORE_SLOWLY:
                return "decreasing more slowly";
            case Historical::PressureTendency::DECREASING:
                return "decreasing";
            case Historical::PressureTendency::DECREASING_MORE_RAPIDLY:
                return "decreasing more rapidly";
            case Historical::PressureTendency::RISING_RAPIDLY:
                return "rising rapidly";
            case Historical::PressureTendency::FALLING_RAPIDLY:
                return "falling rapidly";
        }
    };
    auto pressureTrend = [](Historical::PressureTrend t) {
        switch (t) {
            case Historical::PressureTrend::UNKNOWN:
                return "";
            case Historical::PressureTrend::HIGHER:
                return "higher than";
            case Historical::PressureTrend::HIGHER_OR_SAME:
                return "higher or the same as";
            case Historical::PressureTrend::SAME:
                return "the same as";
            case Historical::PressureTrend::LOWER_OR_SAME:
                return "lower or the same as";
            case Historical::PressureTrend::LOWER:
                return "lower than";
        }
    };
    auto event = [](Historical::Event e) {
        switch (e) {
            case Historical::Event::BEGAN:
                return "began";
            case Historical::Event::ENDED:
                return "ended";
        }
    };
    auto weatherEvent = [&](const Historical::WeatherEvent& we) {
        std::string result = toStr(we.weather) + " "s + event(we.event);
        if (const auto t = toStr(we.time); !t.empty())
            result += " at " + t;
        return result;
    };
    std::ostringstream result;
    if (historical.peakWindDirectionDegrees.has_value()) {
        result << "peakWindDirectionDegrees: peak wind direction is ";
        result << toStr(historical.peakWindDirectionDegrees);
        result << " degrees" << newLine;
    }
    if (historical.peakWindSpeed.speed.has_value()) {
        result << "peakWindSpeed: peak wind speed ";
        result << toStr(historical.peakWindSpeed) << newLine;
    }
    if (const auto t = toStr(historical.peakWindObserved); !t.empty()) {
        result << "peakWindObserved: peak wind observed at ";
        result << toStr(historical.peakWindObserved) << newLine;
    }
    if (historical.windShift)
        result << "windShift: wind shift occurred" << newLine;
    if (historical.windShiftFrontPassage) {
        result << "windShiftFrontPassage: wind shift associated with ";
        result << "frontal passage occurred" << newLine;
    }
    if (const auto t = toStr(historical.windShiftBegan); !t.empty())
        result << "windShiftBegan: wind shift began at " << t << newLine;
    if (historical.temperatureMin6h.temperature.has_value()) {
        result << "temperatureMin6h: 6-hourly minimum temperature ";
        result << toStr(historical.temperatureMin6h) << newLine;
    }
    if (historical.temperatureMax6h.temperature.has_value()) {
        result << "temperatureMax6h: 6-hourly maximum temperature ";
        result << toStr(historical.temperatureMax6h) << newLine;
    }
    if (historical.temperatureMin24h.temperature.has_value()) {
        result << "temperatureMin24h: 24-hourly minimum temperature ";
        result << toStr(historical.temperatureMin24h) << newLine;
    }
    if (historical.temperatureMax24h.temperature.has_value()) {
        result << "temperatureMax24h: 24-hourly maximum temperature ";
        result << toStr(historical.temperatureMax24h) << newLine;
    }
    if (historical.pressureTendency != Historical::PressureTendency::UNKNOWN) {
        result << "pressureTendency: atmospheric pressure for the ";
        result << "last 3 hours was ";
        result << pressureTendency(historical.pressureTendency) << newLine;
    }
    if (historical.pressureTrend != Historical::PressureTrend::UNKNOWN) {
        result << "pressureTrend: atmospheric pressure is ";
        result << pressureTrend(historical.pressureTrend);
        result << " 3 hours ago" << newLine;
    }
    if (historical.pressureChange3h.pressure.has_value()) {
        result << "pressureChange3h: atmospheric pressure change for the last ";
        result << "3 hours is ";
        result << toStr(historical.pressureChange3h) << newLine;
    }
    if (!historical.recentWeather.empty()) {
        result << "recentWeather: the following weather events occurred";
        result << " recently";
        for (const auto& e : historical.recentWeather)
            result << newItem << weatherEvent(e) << newLine;
    }
    if (historical.rainfall10m.amount.has_value()) {
        result << "rainfall10m: rainfall for the last 10 minutes ";
        result << toStr(historical.rainfall10m) << newLine;
    }
    if (historical.rainfallSince0900LocalTime.amount.has_value()) {
        result << "rainfallSince0900LocalTime: rainfall since 09:00 (9AM) ";
        result << "local time ";
        result << toStr(historical.rainfallSince0900LocalTime) << newLine;
    }
    if (historical.precipitationSinceLastReport.amount.has_value()) {
        result << "precipitationSinceLastReport: precipitation since last ";
        result << "report ";
        result << toStr(historical.precipitationSinceLastReport) << newLine;
    }
    if (historical.precipitationTotal1h.amount.has_value()) {
        result << "precipitationTotal1h: total precipitation for the last 1 ";
        result << "hour ";
        result << toStr(historical.precipitationTotal1h) << newLine;
    }
    if (historical.precipitationFrozen3or6h.amount.has_value()) {
        result << "precipitationFrozen3or6h: frozen precipitation for the ";
        result << "last 3 or 6 hours ";
        result << toStr(historical.precipitationFrozen3or6h) << newLine;
    }
    if (historical.precipitationFrozen3h.amount.has_value()) {
        result << "precipitationFrozen3h: frozen precipitation for the ";
        result << "last 3 hours ";
        result << toStr(historical.precipitationFrozen3h) << newLine;
    }
    if (historical.precipitationFrozen6h.amount.has_value()) {
        result << "precipitationFrozen6h: frozen precipitation for the ";
        result << "last 6 hours ";
        result << toStr(historical.precipitationFrozen6h) << newLine;
    }
    if (historical.precipitationFrozen24h.amount.has_value()) {
        result << "precipitationFrozen24h: frozen precipitation for the ";
        result << "last 24 hours ";
        result << toStr(historical.precipitationFrozen24h) << newLine;
    }
    if (historical.snow6h.amount.has_value()) {
        result << "snow6h: snowfall for the last 6 hours ";
        result << toStr(historical.snow6h) << newLine;
    }
    if (historical.snowfallTotal.amount.has_value()) {
        result << "snowfallTotal: total snowfall ";
        result << toStr(historical.snowfallTotal) << newLine;
    }
    if (historical.snowfallIncrease1h.amount.has_value()) {
        result << "snowfallIncrease1h: total snowfall ";
        result << toStr(historical.snowfallIncrease1h) << newLine;
    }
    if (historical.icing1h.amount.has_value()) {
        result << "icing1h: ice accretion for the last 1 hour ";
        result << toStr(historical.icing1h) << newLine;
    }
    if (historical.icing3h.amount.has_value()) {
        result << "icing3h: ice accretion for the last 3 hours ";
        result << toStr(historical.icing3h) << newLine;
    }
    if (historical.icing6h.amount.has_value()) {
        result << "icing6h: ice accretion for the last 6 hours ";
        result << toStr(historical.icing6h) << newLine;
    }
    return result.str();
}

std::string toStr(const IcingForecast& f) {
    auto severity = [](IcingForecast::Severity s) {
        switch (s) {
            case IcingForecast::Severity::NONE_OR_TRACE:
                return "none or trace";
            case IcingForecast::Severity::LIGHT:
                return "light";
            case IcingForecast::Severity::MODERATE:
                return "moderate";
            case IcingForecast::Severity::SEVERE:
                return "severe";
        }
    };
    auto type = [](IcingForecast::Type t) {
        switch (t) {
            case IcingForecast::Type::NONE:
                return "";
            case IcingForecast::Type::RIME_IN_CLOUD:
                return "rime-in-cloud";
            case IcingForecast::Type::CLEAR_IN_PRECIPITATION:
                return "clear-in-precipitation";
            case IcingForecast::Type::MIXED:
                return "mixed";
        }
    };
    std::ostringstream result;
    if (f.type == IcingForecast::Type::NONE) {
        result << "no";
    } else {
        result << severity(f.severity);
        result << " " << type(f.type);
    }
    result << " icing at height from " << toStr(f.minHeight) << " up to ";
    result << toStr(f.maxHeight);
    return result.str();
}

std::string toStr(const TurbulenceForecast& tf) {
    auto severity = [](TurbulenceForecast::Severity s) {
        switch (s) {
            case TurbulenceForecast::Severity::NONE:
                return "no";
            case TurbulenceForecast::Severity::LIGHT:
                return "light";
            case TurbulenceForecast::Severity::MODERATE:
                return "moderate";
            case TurbulenceForecast::Severity::SEVERE:
                return "severe";
            case TurbulenceForecast::Severity::EXTREME:
                return "extreme";
        }
    };
    auto location = [](TurbulenceForecast::Location l) {
        switch (l) {
            case TurbulenceForecast::Location::NONE:
                return ""s;
            case TurbulenceForecast::Location::IN_CLOUD:
                return "in cloud "s;
            case TurbulenceForecast::Location::IN_CLEAR_AIR:
                return "in clear air "s;
        }
    };
    std::ostringstream result;
    result << severity(tf.severity) << " turbulence ";
    result << location(tf.location) << "at height from ";
    result << toStr(tf.minHeight) << " up to " << toStr(tf.maxHeight);
    return result.str();
}

std::string toStr(const TemperatureForecast& tf) {
    std::ostringstream result;
    result << "temperature " << toStr(tf.temperature) << " expected at ";
    result << toStr(tf.time);
    return result.str();
}

std::string toStr(const Trend& t) {
    auto type = [](const Trend::Type t) {
        switch (t) {
            case Trend::Type::BECMG:
                return "becoming "
                       "(weather conditions expected to change gradually)";
            case Trend::Type::TEMPO:
                return "temporary "
                       "(weather conditions expected to arise for less than "
                       " 60 minutes)";
            case Trend::Type::INTER:
                return "intermediary "
                       "(weather conditions expected to arise for less than "
                       " 30 minutes)";
            case Trend::Type::TIMED:
                return "timed "
                       "(weather conditions expected within time frame)";
            case Trend::Type::PROB:
                return "probability "
                       "(weather conditions expected with the specified "
                       "probability and no other details are provided)";
        }
    };
    std::ostringstream result;
    result << newItem << "type: " << type(t.type) << newLine;
    if (t.probability.has_value()) {
        result << newItem << "probability: " << toStr(t.probability);
        result << " %" << newLine;
    }
    if (t.metar)
        result << "metar: this trend was reported in METAR rather than TAF";
    if (const auto tm = toStr(t.timeFrom); !tm.empty())
        result << newItem << "timeFrom: expected from " << tm << newLine;
    if (const auto tm = toStr(t.timeUntil); !tm.empty())
        result << newItem << "timeUntil: expected until " << tm << newLine;
    if (const auto tm = toStr(t.timeAt); !tm.empty())
        result << newItem << "timeAt: expected at " << tm << newLine;
    result << newItem << "forecast: the following weather conditions ";
    result << "are expected" << newLine;
    result << toStr(t.forecast, true);
    if (!t.vicinity.empty()) {
        result << newItem << "vicinity: the following phenomena are expected";
        result << "in the vicinity of the station" << newLine;
        for (const auto & v : t.vicinity) {
            result << newItem << toStr(v) << newLine;
        }
    }
    if (!t.icing.empty()) {
        result << newItem << "icing: icing conditions are expected" << newLine;
        for (const auto & f : t.icing) {
            result << newItem << toStr(f) << newLine;
        }
    }
    if (!t.turbulence.empty()) {
        result << newItem << "turbulence: turbulence conditions are expected";
        result << newLine;
        for (const auto & f : t.turbulence) {
            result << newItem << toStr(f) << newLine;
        }
    }
    if (t.windShearConditions) {
        result << "windShearConditions: potential wind shear conditions are ";
        result << "present" << newLine;
    }
    return result.str();
}

std::string toStr(const Forecast & forecast) {
    std::ostringstream result;
    result << "prevailing: the following weather conditions are expected to ";
    result << "prevail" << newLine;
    result << toStr(forecast.prevailing, true) << newLine;
    if (!forecast.prevailingIcing.empty()) {
        result << newItem << "prevailingIcing: the following icing conditions ";
        result << "are expected to prevail" << newLine;
        for (const auto & f : forecast.prevailingIcing) {
            result << newItem << toStr(f) << newLine;
        }
    }
    if (!forecast.prevailingTurbulence.empty()) {
        result << newItem << "turbulence: the following turbulence conditions ";
        result << "are expected to prevail" << newLine;
        for (const auto & f : forecast.prevailingTurbulence) {
            result << newItem << toStr(f) << newLine;
        }
    }
    if (!forecast.prevailingVicinity.empty()) {
        result << newItem << "prevailingVicinity: the following phenomena are ";
        result << "expected to prevail in vicinity" << newLine;
        for (const auto & v : forecast.prevailingVicinity) {
            result << newItem << toStr(v) << newLine;
        }
    }
    if (forecast.prevailingWsConds) {
        result << newItem << "prevailingWsConds: potential wind shear ";
        result << "are expected to prevail" << newLine;
    }
    if (forecast.noSignificantChanges) {
        result << newItem << "noSignificantChanges: no significant weather ";
        result << "changes are expected" << newLine;
    }
    if (!forecast.trends.empty()) {
        result << newItem << "trends: the weather trends are as follows";
        result << newLine;
        for (const auto & t : forecast.trends) {
            result << toStr(t);
        }
    }
    return result.str();
}

std::string demo(const std::string& report) {
    const auto simple = simplify(report);
    std::ostringstream result;
    result << newReport;

    result << "Raw report: " << formatReport(report) << newLine << newPart;

    result << "report (report type, time, attributes, parsing info, etc.)\n";
    result << toStr(simple.report) << newPart;

    result << "station (station name, capabilities, missing data, etc)\n";
    result << toStr(simple.station) << newPart;

    result << "aerodrome (aerodrome, runway, and directional data)\n";
    result << toStr(simple.aerodrome) << newPart;

    result << "current (current weather conditions)\n";
    result << toStr(simple.current) << newPart;

    result << "historical (recent weather, cumulative and historical data)\n";
    result << toStr(simple.historical) << newPart;
    
    result << "forecast (forecast and weather trends)\n";
    result << toStr(simple.forecast);

    return result.str();
}

#ifdef __EMSCRIPTEN__

#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(WasmDemo) {
    function("demo", &demo);
}

/*
int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    EM_ASM_(wasmDemo(), 0);
    return 0;
}
*/
#else

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    try {
        for (std::string report; std::getline(std::cin, report);) {
            demo(report);
        }
    } catch (...) {
        return 1;
    }
    return 0;
}

#endif  // #ifdef __EMSCRIPTEN__