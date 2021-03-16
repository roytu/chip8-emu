
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "opcode.h"


TEST_CASE( "Opcode parsing test", "[opcode]" ) {
    OpcodeParams params;

    SECTION( "Testing 0000" ) {
        bool res = opcodeParse(&params, "0000", 0x0000);
        REQUIRE( res );
    }

    SECTION( "Testing 0NNN" ) {
        bool res = opcodeParse(&params, "0NNNN", 0x0000);
        REQUIRE( res );
        REQUIRE( params.N == 0x0 );
    }

    SECTION( "Testing 00NN" ) {
        bool res = opcodeParse(&params, "00NN", 0x0000);
        REQUIRE( res );
        REQUIRE( params.N == 0x0 );
    }

    SECTION( "Testing 0XYN" ) {
        bool res = opcodeParse(&params, "0XYN", 0x03DF);
        REQUIRE( res );
        REQUIRE( params.X == 0x3 );
        REQUIRE( params.Y == 0xD );
        REQUIRE( params.N == 0xF );
    }

    SECTION( "Testing 1XYN" ) {
        bool res = opcodeParse(&params, "1XYN", 0x0000);
        REQUIRE( !res );
    }

    SECTION( "Testing 2NNN" ) {
        bool res = opcodeParse(&params, "2NNN", 0x1222);
        REQUIRE( !res );
    }

    SECTION( "Testing 1234" ) {
        bool res = opcodeParse(&params, "1234", 0x1234);
        REQUIRE( res );
    }

}

