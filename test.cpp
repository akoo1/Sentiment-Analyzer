//
// Created by Alfred on 2/11/20.
//

#include "catch.h"

#include <cstring>
#include "DSString.h"


// After each SECTION, the variables in the scope will be reset to the variables in the TEST_CASE

TEST_CASE("DSString class", "[DSString]"){
    DSString s[10];
    s[0] = DSString("testDSString");
    s[1] = DSString("a test string");
    s[2] = DSString("");
    s[3] = DSString("THIS IS AN UPPERCASE STRING");
    s[4] = DSString("this is an uppercase string");
    s[5] = DSString("\n");
    s[6] = DSString("");
    s[7] = DSString("  split  split  split  ");
    s[8] = DSString("                          ");
    s[9] = DSString("testDSString");



    SECTION("Equality operators"){
        REQUIRE(s[0] == DSString("testDSString"));
        REQUIRE(s[0] == s[9]);
        REQUIRE(s[2] == "");
        REQUIRE(s[1] == "a test string");
        REQUIRE(!(s[3] == s[4]));
    }

    SECTION("Greater than operators"){
        REQUIRE(s[0] > DSString("test"));
        REQUIRE(s[0] > s[1]);
        REQUIRE(s[4] > s[3]);
        REQUIRE(s[9] > s[6]);
        REQUIRE(s[7] > s[6]);
    }


    SECTION("Less than operators"){
        REQUIRE(s[0] < DSString("testDSStringgg"));
        REQUIRE(s[0] < s[4]);
        REQUIRE((s[7] < s[4]));
    }

    SECTION("Assignment operators"){
        DSString str;
        str = "a test string";
        REQUIRE(str == s[1]);
        str = DSString("testDSString");
        REQUIRE(str == s[0]);
        str = "";
        REQUIRE(str == s[6]);
        str = DSString("\n");
        REQUIRE(str == s[5]);
    }

//    SECTION("Addition operator"){
//        REQUIRE(DSString("testDSStringtestDSString") == s[0]+s[9]);
//        REQUIRE(s[6] + s[6] == "");
//        REQUIRE(s[5] + s[6] == DSString("\n"));
//        REQUIRE(s[0] + s[1] + s[2] == "testDSStringa test string");
//    }



//    SECTION("[] Operator"){
//        REQUIRE(s[0][1] == 'e');
//        REQUIRE(s[4][4] == ' ');
//        REQUIRE(s[6][0] == 0);
//    }


    SECTION("getLength function"){
        REQUIRE(s[9].getLength() == 12);
        REQUIRE(s[2].getLength() == 0);
        REQUIRE(s[8].getLength() == 26);
        REQUIRE(s[3].getLength() == 27);
    }

    SECTION("isEmpty function") {
        REQUIRE(s[2].isEmpty() == false);
        REQUIRE(s[0].isEmpty() == false);
    }

    SECTION("Substring function"){
        REQUIRE(s[0].substring(0, 5) == "testD");
        REQUIRE(s[4].substring(0, 4) == "this");
        REQUIRE(s[4].substring(1, 3) == "his");
    }



}