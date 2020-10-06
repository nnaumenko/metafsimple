/*
* Copyright (C) 2020 Nick Naumenko (https://gitlab.com/nnaumenko,
* https:://github.com/nnaumenko)
* All rights reserved.
* This software may be modified and distributed under the terms
* of the MIT license. See the LICENSE file for details.
*/

#include "gtest/gtest.h"
#include "metafsimple.hpp"

TEST(WarningLogger, warningLogger) {
    static const std::string idStr12 = "test1";
    static const std::string idStr3 = "test2";
    static const auto msg1 =
        metafsimple::Report::Warning::Message::INCONSISTENT_DATA;
    static const auto msg2 =
        metafsimple::Report::Warning::Message::DUPLICATED_DATA;
    static const auto msg3 =
        metafsimple::Report::Warning::Message::INVALID_GROUP;
    metafsimple::Report r;
    metafsimple::detail::WarningLogger wl(r.warnings);
    wl.setIdString(idStr12);
    wl.add(msg1);
    wl.add(msg2);
    wl.setIdString(idStr3);
    wl.add(msg3);
    ASSERT_EQ(r.warnings.size(), 3u);
    EXPECT_EQ(r.warnings.at(0).id, idStr12);
    EXPECT_EQ(r.warnings.at(0).message, msg1);
    EXPECT_EQ(r.warnings.at(1).id, idStr12);
    EXPECT_EQ(r.warnings.at(1).message, msg2);
    EXPECT_EQ(r.warnings.at(2).id, idStr3);
    EXPECT_EQ(r.warnings.at(2).message, msg3);
}

// To confirm that instead of two or more duplicated warnings, only first
// warning is added (i.e. sequential duplicated warnings are merged)
TEST(WarningLogger, duplicateWarnings) {
    static const std::string idStr1 = "test1";
    static const std::string idStr2 = "test2";
    static const auto msg1 =
        metafsimple::Report::Warning::Message::INCONSISTENT_DATA;
    static const auto msg2 =
        metafsimple::Report::Warning::Message::DUPLICATED_DATA;
    metafsimple::Report r;
    metafsimple::detail::WarningLogger wl(r.warnings);
    wl.setIdString(idStr1);
    wl.add(msg1);
    wl.add(msg1);

    wl.add(msg2);
    wl.add(msg2);
    wl.add(msg2);
    wl.add(msg2);

    wl.setIdString(idStr2);
    wl.add(msg2);
    wl.add(msg2);
    wl.add(msg2);

    wl.add(msg1);
    wl.add(msg1);

    wl.add(msg2);

    wl.setIdString(idStr1);
    wl.add(msg2);
    wl.add(msg2);
    wl.add(msg2);
    wl.add(msg2);
    wl.add(msg2);
    wl.add(msg2);
    wl.add(msg2);
    ASSERT_EQ(r.warnings.size(), 6u);

    EXPECT_EQ(r.warnings.at(0).id, idStr1);
    EXPECT_EQ(r.warnings.at(0).message, msg1);

    EXPECT_EQ(r.warnings.at(1).id, idStr1);
    EXPECT_EQ(r.warnings.at(1).message, msg2);

    EXPECT_EQ(r.warnings.at(2).id, idStr2);
    EXPECT_EQ(r.warnings.at(2).message, msg2);

    EXPECT_EQ(r.warnings.at(3).id, idStr2);
    EXPECT_EQ(r.warnings.at(3).message, msg1);

    EXPECT_EQ(r.warnings.at(4).id, idStr2);
    EXPECT_EQ(r.warnings.at(4).message, msg2);

    EXPECT_EQ(r.warnings.at(5).id, idStr1);
    EXPECT_EQ(r.warnings.at(5).message, msg2);
}