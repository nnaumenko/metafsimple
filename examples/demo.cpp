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
            result << " - " << warning(w) << newLine;
        }
    }
    if (!report.plainText.empty()) {
        result << "plainText: unable to decode the following group(s) in this ";
        result << "report (possibly they are plain text remarks)" << newLine;
        for (const auto& pt : report.plainText) {
            result << " - " << pt << newLine;
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
        result << "missingData: station reports that the following data ";
        result << "are missing" << newLine;
        for (const auto md : station.missingData) {
            result << " - " << missingData(md) << newLine;
        }
    }
    if (!station.runwaysNoCeilingData.empty()) {
        result << "runwaysNoCeilingData: station reports that the ceiling ";
        result << "data is missing for the following runways" << newLine;
        for (const auto rw : station.runwaysNoCeilingData) {
            result << " - runway " << toStr(rw) << newLine;
        }
    }
    if (!station.runwaysNoVisData.empty()) {
        result << "runwaysNoVisData: station reports that the visibility ";
        result << "data is missing for the following runways" << newLine;
        for (const auto rw : station.runwaysNoVisData) {
            result << " - runway " << toStr(rw) << newLine;
        }
    }
    return result.str();
}

std::string toStr(const Aerodrome& aerodrome) {
    auto colourCode = [](Aerodrome::ColourCode c) {
        switch(c) {
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
        switch(r) {
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
        switch(d) {
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
        switch(r) {
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
        switch(ba) {
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
    std::ostringstream result;
    // TODO
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
/*
    result << "aerodrome (aerodrome, runway, and directional data)\n";
    result << toStr(simple.aerodrome) << newPart;

    result << "current (current weather conditions)\n";
    result << toStr(simple.current) << newPart;

    result << "historical (recent weather, cumulative and historical data)\n";
    result << toStr(simple.historical) << newPart;;

    result << "forecast (forecast and weather trends)\n";
    result << toStr(simple.forecast);
*/
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