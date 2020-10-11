/*
* Copyright (C) 2020 Nick Naumenko (https://gitlab.com/nnaumenko,
* https:://github.com/nnaumenko)
* All rights reserved.
* This software may be modified and distributed under the terms
* of the MIT license. See the LICENSE file for details.
*/

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

std::string toStr(Report report) {
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
    result << "Report type: " << type(report.type) << newLine;
    if (report.missing)
        result << "This report is missing" << newLine;
    if (report.cancelled)
        result << "This report cancels previous forecast" << newLine;
    if (report.correctional) {
        result << "This report corrects previous report";
        if (report.correctionNumber) {
            result << " (corection " << report.correctionNumber << ")";
        }
        result << newLine;
    }
    if (report.amended)
        result << "This report amends previous report" << newLine;
    if (report.automated) {
        result << "This report fully automated and produced with no ";
        result << "human intervention or oversight" << newLine;
    }
    if (const auto t = toStr(report.reportTime); !t.empty())
        result << "Report release time: " << t << newLine;
    const auto tf = toStr(report.applicableFrom);
    const auto tu = toStr(report.applicableUntil);
    if (!tf.empty() || !tu.empty()) {
        result << "Report is applicable";
        if (!tf.empty()) result << " from " << tf;
        if (!tu.empty()) result << ", until " << tu;
        result << newLine;
    }
    if (report.error != Report::Error::NO_ERROR) {
        result << "Error while parsing this report: ";
        result << error(report.error) << newLine;
    }
    if (!report.warnings.empty()) {
        result << "The following warnings were generated ";
        result << "while processing the report: " << newLine;
        for (const auto& w : report.warnings) {
            result << " - " << warning(w) << newLine;
        }
    }
    if (!report.plainText.empty()) {
        result << "The parser was unable to decode the following group";
        if (report.plainText.size() != 1) result << 's';
        result << " in this report:" << newLine;
        result << "(possibly they are plain text remarks)" << newLine;
        for (const auto& pt : report.plainText) {
            result << " - " << pt << newLine;
        }
    }

    return result.str();
}

std::string demo(const std::string& report) {
    const auto simple = simplify(report);
    std::string result = newReport;

    result += "Raw report:";
    result += newLine;
    result += report;
    result += newLine;
    result += newPart;

    result += "Report data:\n";
    result += toStr(simple.report);
    result += newPart;
    /*
    result += "Station data:\n";
    result += toStr(simple.station);
    result += newPart;

    result += "Aerodrome data:\n";
    result += toStr(simple.aerodrome);
    result += newPart;

    result += "Current weather data:\n";
    result += toStr(simple.current);
    result += newPart;

    result += "Cumulative and historical data:\n";
    result += toStr(simple.historical);
    result += newPart;

    result += "Forecast data:\n";
    result += toStr(simple.forecast);
    result += newPart;
*/
    return result;
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