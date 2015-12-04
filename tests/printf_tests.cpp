#include <UnitTest++.h>

#include "stdio_fixture.h"

SUITE(PrintF)
{
    TEST_FIXTURE(StdIOFixture, BasicPrintFTest)
    {
        int r = fslc_fprintf(&stream, "Hello, World!\n");
        
        CHECK_EQUAL("Hello, World!\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFStringTest)
    {
        int r = fslc_fprintf(&stream, "Hello from %s!\n", "PrintF");
        
        CHECK_EQUAL("Hello from PrintF!\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintF2StringsTest)
    {
        int r = fslc_fprintf(&stream, "%s from %s!\n", "Hello", "PrintF");
        
        CHECK_EQUAL("Hello from PrintF!\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFCharTest)
    {
        int r = fslc_fprintf(&stream, "Hello, %corld!\n", 'W');
        
        CHECK_EQUAL("Hello, World!\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFPercentTest)
    {
        int r = fslc_fprintf(&stream, "Special offer: 50%% off!");
        
        CHECK_EQUAL("Special offer: 50% off!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFPrePostMultiTest)
    {
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        
        int r = fslc_fprintf(&stream, "Testing %s%% of all possibilities%c", "a few ", '!');
        
        const char *expected_str = "Testing a few % of all possibilities!";
        
        std::vector<FuncCallItem> expected_calls;
        expected_calls.push_back({ CalledFunc::PreOp, 0 });
        for (const char *c = expected_str; *c; ++c)
            expected_calls.push_back({ CalledFunc::PutC, *c });
        expected_calls.push_back({ CalledFunc::PostOp, 0 });

        CHECK(r >= 0);
        CHECK_EQUAL(expected_calls.size(), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected_calls, FuncCallLog, FuncCallLog.size());
        
        CHECK_EQUAL(expected_str, ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFPrePostMultiEofTest)
    {
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        
        eof_counter = 20;
        
        int r = fslc_fprintf(&stream, "Testing %s%% of all possibilities%c", "a few ", '!');
        
        const char *expected_str = "Testing a few % of a";
        //                          12345678901234567890
        
        std::vector<FuncCallItem> expected_calls;
        expected_calls.push_back({ CalledFunc::PreOp, 0 });
        for (const char *c = expected_str; *c; ++c)
            expected_calls.push_back({ CalledFunc::PutC, *c });
        expected_calls.push_back({ CalledFunc::PutC, 'l' }); // EOF
        expected_calls.push_back({ CalledFunc::PostOp, 0 });

        CHECK(r < 0);
        CHECK_EQUAL(expected_calls.size(), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected_calls, FuncCallLog, FuncCallLog.size());
        
        CHECK_EQUAL(expected_str, ostring.str());
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFBasicIntTest)
    {
        int r = fslc_fprintf(&stream, "The answer is %d!", 42);
        
        CHECK(r >= 0);
        CHECK_EQUAL("The answer is 42!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFZeroIntTest)
    {
        int r = fslc_fprintf(&stream, "Zero is %d!", 0);
        
        CHECK(r >= 0);
        CHECK_EQUAL("Zero is 0!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUIntMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max uint is %u\n", -1);
        
        CHECK(r >= 0);
        CHECK_EQUAL("Max uint is 4294967295\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
}