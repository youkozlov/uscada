#include "gtest/gtest.h"

#include "OpcUaBinaryCodec.hpp"

using namespace app::ua;

class OpcUaBinaryCodecTest : public ::testing::Test
{
public:

    template <typename T>
    void check(T const& ref)
    {
        s << ref;
        T val;
        s >> val;
        EXPECT_EQ(ref, val);
    }

private:
    OpcUaBinaryCodec s;
};

TEST_F(OpcUaBinaryCodecTest, Boolean)
{
    Boolean boolean1{true};
    check(boolean1);
    Boolean boolean2 = boolean1;
    check(boolean2);
    Boolean boolean3{boolean1};
    check(boolean3);
    Boolean boolean4{false};
    check(boolean4);
    Boolean boolean5;
    boolean5 = boolean4;
    check(boolean5);
    Boolean boolean6;
    boolean6 = false;
    check(boolean6);
}

TEST_F(OpcUaBinaryCodecTest, SByte)
{
    check(SByte{127});
    check(SByte{-128});
}

TEST_F(OpcUaBinaryCodecTest, Byte)
{
    check(Byte{1});
    check(Byte{255});
}

TEST_F(OpcUaBinaryCodecTest, Int16)
{
    check(Int16{1});
    check(Int16{-32767});
}

TEST_F(OpcUaBinaryCodecTest, UInt16)
{
    check(UInt16{1});
    check(UInt16{65534});
}

TEST_F(OpcUaBinaryCodecTest, Int32)
{
    check(Int32{-1});
    check(Int32{655340});
}

TEST_F(OpcUaBinaryCodecTest, UInt32)
{
    check(UInt32{0});
    check(UInt32{655340});
}

TEST_F(OpcUaBinaryCodecTest, Int64)
{
    check(Int64{-1});
    check(Int64{6553400});
}

TEST_F(OpcUaBinaryCodecTest, UInt64)
{
    check(UInt64{1});
    check(UInt64{6553400});
}

TEST_F(OpcUaBinaryCodecTest, Float)
{
    check(Float{1.0f});
    check(Float{-1.0f});
}

TEST_F(OpcUaBinaryCodecTest, Double)
{
    check(Double{1.0f});
    check(Double{-1.0f});
}

TEST_F(OpcUaBinaryCodecTest, String)
{
    check(String{"AAAA"});
    check(String{""});
    check(String{});
}

TEST_F(OpcUaBinaryCodecTest, DateTime)
{
    check(DateTime{0});
    check(DateTime{15666});
}

TEST_F(OpcUaBinaryCodecTest, Guid)
{
    Guid guid;
    guid.data1 = 1;
    guid.data2 = 2;
    guid.data3 = 3;
    guid.data4[0] = 0;
    guid.data4[1] = 1;
    guid.data4[2] = 2;
    guid.data4[3] = 3;
    guid.data4[4] = 4;
    guid.data4[5] = 5;
    guid.data4[6] = 6;
    guid.data4[7] = 7;
    check(guid);
}

TEST_F(OpcUaBinaryCodecTest, ByteString)
{
    ByteString byteString = "AAAAAAA";
    check(byteString);
}

TEST_F(OpcUaBinaryCodecTest, NodeId)
{
    NodeId nodeId1;
    check(nodeId1);

    NodeId nodeId2;
    nodeId2.namespaceIndex = 0;
    nodeId2.value.emplace<UInt32>(0xFF);
    check(nodeId2);

    NodeId nodeId3;
    nodeId3.namespaceIndex = 1;
    nodeId3.value.emplace<UInt32>(0xAABB);
    check(nodeId3);

    NodeId nodeId4;
    nodeId4.namespaceIndex = 1;
    nodeId4.value.emplace<UInt32>(0xFFFFFF);
    check(nodeId4);

    NodeId nodeId5;
    nodeId5.namespaceIndex = 1;
    nodeId5.value.emplace<String>("AAAAAAAAAAAA");
    check(nodeId5);

    NodeId nodeId6;
    nodeId6.namespaceIndex = 1;
    nodeId6.value.emplace<Guid>();
    check(nodeId6);
}

TEST_F(OpcUaBinaryCodecTest, StatusCode)
{
    check(StatusCode{3333});
}

TEST_F(OpcUaBinaryCodecTest, QualifiedName)
{
    QualifiedName qn;
    qn.namespaceIndex = 33;
    qn.name = "AAAAAAAAA";
    check(qn);
}

TEST_F(OpcUaBinaryCodecTest, LocalizedText)
{
    LocalizedText lz1;
    check(lz1);

    LocalizedText lz2;
    lz2.locale.emplace("111");
    check(lz2);

    LocalizedText lz3;
    lz3.text.emplace("222");
    check(lz3);

    LocalizedText lz4;
    lz4.locale.emplace("111");
    lz4.text.emplace("222");
    check(lz4);

    LocalizedText lz5;
    lz5.text.emplace();
    check(lz5);
}

TEST_F(OpcUaBinaryCodecTest, DataValue)
{
    DataValue data1;
    check(data1);

    DataValue data2;
    data2.value.emplace<UInt16>(0xFFAA);
    check(data2);

    DataValue data3;
    data3.status.emplace(0xFFAA);
    check(data3);

    DataValue data4;
    data4.sourceTimestampt.emplace(0xFFAA);
    check(data4);

    DataValue data5;
    data5.sourcePicoSeconds.emplace(0xFFAA);
    check(data5);

    DataValue data6;
    data6.serverTimeStampt.emplace(0xFFAA);
    check(data6);

    DataValue data7;
    data7.serverPicoSeconds.emplace(0xFFAA);
    check(data7);
}

TEST_F(OpcUaBinaryCodecTest, Variant)
{
    Variant var1;
    check(var1);

    Variant var2;
    var2.emplace<UInt32>(0xFFFF);
    check(var2);

    Variant var3;
    var3.emplace<Guid>();
    check(var3);

    Variant var4;
    var4.emplace<String>("String");
    check(var4);

    Variant var5;
    auto& arr = var5.emplace<DynamicArray<UInt32>>(10);
    for (auto &&i : arr) { i = 0xAA; }
    check(var5);
}

TEST_F(OpcUaBinaryCodecTest, DiagnosticInfo)
{
    DiagnosticInfo diag1;
    check(diag1);

    DiagnosticInfo diag2;
    diag2.symbolicId.emplace(0x12345);
    check(diag2);

    DiagnosticInfo diag3;
    diag3.namespaceUri.emplace(0x12345);
    check(diag3);

    DiagnosticInfo diag4;
    diag4.locale.emplace(0x12345);
    check(diag4);

    DiagnosticInfo diag5;
    diag5.localizedText.emplace(0x12345);
    check(diag5);

    DiagnosticInfo diag6;
    diag6.additionalInfo.emplace("0x12345");
    check(diag6);

    DiagnosticInfo diag7;
    diag7.innerStatusCode.emplace(0x12345);
    check(diag7);

    DiagnosticInfo diag8;
    diag8.innerDiagnosticInfo = std::make_unique<DiagnosticInfo>();
    check(diag8);

    DiagnosticInfo diag9;
    diag9.innerDiagnosticInfo = std::make_unique<DiagnosticInfo>();
    diag9.innerDiagnosticInfo->symbolicId.emplace(0xAAAA);
    diag9.innerDiagnosticInfo->additionalInfo.emplace("0xAAAA");
    check(diag9);
}