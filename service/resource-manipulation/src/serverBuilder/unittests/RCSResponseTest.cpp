//******************************************************************
//
// Copyright 2015 Samsung Electronics All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#include <gtest/gtest.h>
#include <HippoMocks/hippomocks.h>

#include <RCSResponse.h>
#include <ResourceObject.h>

#include <RequestHandler.h>
#include <ResourceAttributesConverter.h>

#include <OCPlatform.h>

using namespace std;

using namespace testing;

using namespace OIC::Service;
using namespace OC;

typedef OCStackResult (*registerResourceSig)(OCResourceHandle&,
                       string&,
                       const string&,
                       const string&,
                       EntityHandler,
                       uint8_t );

static constexpr char KEY[] = "key";


void EXPECT_RESPONSE(shared_ptr< OCResourceResponse > ocResponse,
        const OCEntityHandlerResult& result, int errorCode, const ResourceAttributes& attrs)
{
    EXPECT_EQ(ocResponse->getResponseResult(), result);
    EXPECT_EQ(ocResponse->getErrorCode(), errorCode);
    EXPECT_EQ(ResourceAttributesConverter::fromOCRepresentation(
                    ocResponse->getResourceRepresentation()), attrs);
}


class RCSResponseTest: public Test
{
public:
    MockRepository mocks;

public:
    template< typename T >
    shared_ptr< OCResourceResponse > buildResponse(const T& response)
    {
        ResourceObject::Ptr server =
                ResourceObject::Builder("a/test", "", "").build();

        return response.getHandler()->buildResponse(*server);
    }

protected:
    void SetUp()
    {
        mocks.OnCallFuncOverload(static_cast< registerResourceSig >(OCPlatform::registerResource))
                .Return(OC_STACK_OK);

        mocks.OnCallFunc(OCPlatform::unregisterResource).Return(OC_STACK_OK);
    }
};

TEST_F(RCSResponseTest, GetDefaultActionHasEmptyAttrs)
{
    EXPECT_RESPONSE(buildResponse(RCSGetResponse::defaultAction()),
            RequestHandler::DEFAULT_RESULT, RequestHandler::DEFAULT_ERROR_CODE,
            ResourceAttributes());
}

TEST_F(RCSResponseTest, GetResponseHasResultsPassedCodes)
{
    constexpr OCEntityHandlerResult result{ OC_EH_ERROR };
    constexpr int errorCode{ -10 };

    EXPECT_RESPONSE(buildResponse(RCSGetResponse::create(result, errorCode)),
            result, errorCode, ResourceAttributes());
}

TEST_F(RCSResponseTest, GetResponseHasAttrsAndResultsPassedCodes)
{
    constexpr OCEntityHandlerResult result{ OC_EH_ERROR };
    constexpr int errorCode{ -10 };

    ResourceAttributes attrs;
    attrs[KEY] = 100;

    EXPECT_RESPONSE(buildResponse(RCSGetResponse::create(attrs, result, errorCode)),
            result, errorCode, attrs);
}

TEST_F(RCSResponseTest, GetResponseCanMoveAttrs)
{
    constexpr OCEntityHandlerResult result{ OC_EH_ERROR };
    constexpr int errorCode{ -10 };

    ResourceAttributes attrs;
    attrs[KEY] = 100;

    ResourceAttributes attrsClone;
    attrsClone[KEY] = 100;

    EXPECT_RESPONSE(
            buildResponse(RCSGetResponse::create(std::move(attrs), result, errorCode)),
            result, errorCode, attrsClone);

    EXPECT_TRUE(attrs.empty());
}

TEST_F(RCSResponseTest, SetDefaultActionHasEmptyAttrs)
{
    EXPECT_RESPONSE(buildResponse(RCSSetResponse::defaultAction()),
            RequestHandler::DEFAULT_RESULT, RequestHandler::DEFAULT_ERROR_CODE,
            ResourceAttributes());
}

TEST_F(RCSResponseTest, SetResponseHasResultsPassedCodes)
{
    constexpr OCEntityHandlerResult result{ OC_EH_ERROR };
    constexpr int errorCode{ -10 };

    EXPECT_RESPONSE(buildResponse(RCSSetResponse::create(result, errorCode)),
            result, errorCode, ResourceAttributes());
}

TEST_F(RCSResponseTest, SetResponseHasAttrsAndResultsPassedCodes)
{
    constexpr OCEntityHandlerResult result{ OC_EH_ERROR };
    constexpr int errorCode{ -10 };

    ResourceAttributes attrs;
    attrs[KEY] = 100;

    EXPECT_RESPONSE(buildResponse(RCSSetResponse::create(attrs, result, errorCode)),
            result, errorCode, attrs);
}

TEST_F(RCSResponseTest, SetResponseCanMoveAttrs)
{
    constexpr OCEntityHandlerResult result{ OC_EH_ERROR };
    constexpr int errorCode{ -10 };

    ResourceAttributes attrs;
    attrs[KEY] = 100;

    ResourceAttributes attrsClone;
    attrsClone[KEY] = 100;

    EXPECT_RESPONSE(
            buildResponse(RCSSetResponse::create(std::move(attrs), result, errorCode)),
            result, errorCode, attrsClone);

    EXPECT_TRUE(attrs.empty());
}


TEST_F(RCSResponseTest, DefaultSetResponseHasDefaultMethod)
{
    EXPECT_EQ(RCSSetResponse::AcceptanceMethod::DEFAULT,
            RCSSetResponse::defaultAction().getAcceptanceMethod());
}

TEST_F(RCSResponseTest, AcceptSetResponseHasAcceptMethod)
{
    EXPECT_EQ(RCSSetResponse::AcceptanceMethod::ACCEPT,
            RCSSetResponse::accept().getAcceptanceMethod());
}

TEST_F(RCSResponseTest, IgnoreSetResponseHasIgnoreMethod)
{
    EXPECT_EQ(RCSSetResponse::AcceptanceMethod::IGNORE,
            RCSSetResponse::ignore().getAcceptanceMethod());
}

TEST_F(RCSResponseTest, SetResponseHasMethodSetBySetter)
{
    RCSSetResponse::AcceptanceMethod method = RCSSetResponse::AcceptanceMethod::ACCEPT;
    RCSSetResponse response =
            RCSSetResponse::defaultAction().setAcceptanceMethod(method);

    EXPECT_EQ(method, response.getAcceptanceMethod());
}