//
// Created by felix on 19/12/2018.
//

#include "catch.hpp"
#include "core/util/dynamic_bitset.h"
#include "common.h"

using namespace chimeric;


TEST_CASE("Dynamic bitset") {

    using bitset = dynamic_bitset;

    SECTION("Set and test", "[BS]") {

        bitset bs;

        bs.set(6);
        bs.set(9);
        bs.set(45);
        bs.set(75);
        bs.set(80);
        bs.set(156);

        REQUIRE(bs.test(6));
        REQUIRE(bs.test(9));
        REQUIRE(bs.test(45));
        REQUIRE(bs.test(75));
        REQUIRE(bs.test(80));
        REQUIRE(bs.test(156));


        REQUIRE_FALSE(bs.test(0));
        REQUIRE_FALSE(bs.test(7));
        REQUIRE_FALSE(bs.test(46));
        REQUIRE_FALSE(bs.test(90));
        REQUIRE_FALSE(bs.test(160));
    }

    SECTION("Reference get and set", "[BS]") {

        bitset bs;

        bs[0] = true;
        REQUIRE(bs[0]);
        REQUIRE_FALSE(bs[5]);
        bs[5] = true;
        REQUIRE(bs[5]);
        bs[5] = false;
        REQUIRE_FALSE(bs[5]);
    }


    SECTION("From string", "[BS]") {
        bitset bs("01001");
        REQUIRE(bs[0] == 1);
        REQUIRE(bs[1] == 0);
        REQUIRE(bs[2] == 0);
        REQUIRE(bs[3] == 1);
        REQUIRE(bs[4] == 0);
    }

    SECTION("equal", "[BS]") {
        bitset a("0100111");
        bitset b("0100111");
        bitset c("0110111");

        REQUIRE(a == b);
        REQUIRE_FALSE(a == c);
    }

    SECTION("and", "[BS]") {
        bitset a("0100111");
        bitset b("1101010");
        bitset c("0100010");

        REQUIRE((a & b) == c);
    }

    SECTION("or", "[BS]") {
        bitset a("0100111");
        bitset b("1101010");
        bitset c("1101111");

        REQUIRE((a | b) == c);
    }

    SECTION("xor", "[BS]") {
        bitset a("0100111");
        bitset b("1101010");
        bitset c("1001101");

        REQUIRE((a ^ b) == c);
    }

    SECTION("trim", "[BS]") {

        bitset a;
        for(size_t i = 0; i < 256; i++) {
            a[i] = (i % 5);
        }

        for(size_t i = 256; i < 512; i++) {
            a[i] = false;
        }

        bitset b(a);

        REQUIRE(a == b);

        b.trim();

        REQUIRE(a == b);
    }

    SECTION("count", "[BS]") {
        bitset a("0100111010101110101");

        REQUIRE(a.count() == 11);
    }

    SECTION("Contains", "[BS]") {

        bitset a("0110101011010001010101");
        bitset b("0010101010000001010001");

        REQUIRE(a.containsAll(b));

        bitset c("1110101011011001010101");

        REQUIRE_FALSE(a.containsAll(c));
        REQUIRE(c.containsAll(a));


        bitset d("0100101111000011010101");
        REQUIRE_FALSE(a.containsAll(d));
        REQUIRE_FALSE(d.containsAll(a));
    }

    SECTION("Intersects", "[BS]") {
        bitset a("00000010010101001010100101");
        bitset b("10101100010100000100011000");

        REQUIRE(a.intersects(b));
        REQUIRE_FALSE(a.notIntersects(b));

        bitset c("01111001100010010000000010");

        REQUIRE_FALSE(a.intersects(c));
        REQUIRE(a.notIntersects(c));
    }

    SECTION("Int vec", "[BS]") {
        std::vector<size_t> vec {4,5,7,8,14,67,96,145,258};
        bitset bs;
        for(size_t i : vec) {
            bs[i] = true;
        }

        REQUIRE(bs.toIntVector() == vec);
    }

    SECTION("flip", "[BS]") {
        bitset a("0100101010");
        bitset b("0100011010");

        a.flip(4);
        a.flip(5);

        REQUIRE(a == b);
    }

    SECTION("foreachset", "[BS]") {
        std::vector<size_t> vec {4,5,7,8,14,67,96,145,258};
        bitset bs;
        for(size_t i : vec) {
            bs[i] = true;
        }

        int i = 0;
        bs.foreachset([&](auto e) {
           REQUIRE(e == vec[i++]);
        });
    }

}