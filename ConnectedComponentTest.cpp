#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "PGMimageProcessor.h"
#include "ConnectedComponent.h"

TEST_CASE ("Big 6 Unit Tests PGMimageProcessor")
{
	SECTION ("Custom Constructor")
	{
		PGMimageProcessor proc("chess.pgm");
        REQUIRE(proc.getComponentCount()==6);
	}


}

TEST_CASE ("Connected Component Method Unit Tests ")
{
    PGMimageProcessor proc("chess.pgm");
	SECTION ("get Component Count")
	{
        REQUIRE(proc.getComponentCount()==6);
	}

    SECTION ("Default Constructor")
	{   ConnectedComponent cc;
        REQUIRE(cc.getID()==0);
        REQUIRE(cc.getPixelCount()==0);
	}

    SECTION ("Custom Constructor")
    {
        ConnectedComponent tester(3);
        REQUIRE(tester.getID()==3);
    }

    SECTION ("add Pixel Method")
	{
        ConnectedComponent tst();
        tst.addPixel(1,1);
        REQUIRE(tester.getPixelCount()==1);
        tst.addPixel(1,2);
        REQUIRE(tester.getPixelCount()==2);
	}

    SECTION ("setID Method")
	{
        ConnectedComponent tstr();
        tstr.setID(2);
        REQUIRE(tstr.getID()==2);

	}






}