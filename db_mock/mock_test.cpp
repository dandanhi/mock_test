#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


using ::testing::_;
using ::testing::AtLeast;                     // #1
using ::testing::Ge;
using ::testing::NotNull;
using ::testing::StrictMock;
using ::testing::StartsWith;


// The fixture for testing class Project1. From google test primer.
class AsyncIOTests : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

    AsyncIOService *aioService;

	AsyncIOTests()

    {
		// You can do set-up work for each test here.
        aioService = AsyncIOService::getInstance();        
	}

	virtual ~AsyncIOTests() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case for Project1.

};


class AsyncIOHttpCallback {
public:
    virtual void onData(char *data, size_t datalen) {};

    virtual void onFinish(double content_length, long header_size, long httpcode, char *redirect_url) {};

    virtual void onError(CURLcode curlErrorNo) {};

    virtual void onTimeout() {};

    virtual ~AsyncIOHttpCallback() {}
};

class MockCallback : public AsyncIOHttpCallback {
public:
    MOCK_METHOD1(onError, void(CURLcode errCode));
    MOCK_METHOD0(onTimeout, void());
    MOCK_METHOD2(onData, void(char *data, size_t datalen));
    MOCK_METHOD4(onFinish, void(double content_length, long header_size, long httpcode, char *redirect_url));
};

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
TEST_F(AsyncIOTests, DoSampleHTTPFetch) {
    shared_ptr<AsyncIOHttpContext>  url1(new AsyncIOHttpContext);
    shared_ptr<MockCallback>    mcallback(new StrictMock<MockCallback>);

    shared_ptr<AsyncIORequestPolicy> policy(new AsyncIORequestPolicy);

    policy->finishHandler = [&mcallback](double  content_length, long header_size, long httpcode, char *redirect_url) {
        EXPECT_EQ(httpcode, 200);
        mcallback->onFinish(content_length, header_size, httpcode, redirect_url);
    };
    std::string url = "http://www.baidu.com";
    url1->url = url;

    policy->errorHandler = [&mcallback] (CURLcode curlError) {
        mcallback->onError(curlError);
    };
    policy->timeoutHandler = [&mcallback]() {
        mcallback->onTimeout();
    };

    aioService->queueHttpRequest(policy);

    EXPECT_CALL((*mcallback.get()), onFinish(_,_, _, NULL)).Times(1);

    aioService->waitRequestEmpty(5);
}


int main(int argc, char** argv) {
	// The following line must be executed to initialize Google Mock
	// (and Google Test) before running the tests.

  ::testing::InitGoogleTest(&argc, argv);
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
