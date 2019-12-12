#pragma once

#include <rapidjson/document.h>
#include <rapidjson/encodings.h>
#include <rapidjson/encodedstream.h>
#include <rapidjson/writer.h>

namespace rapidjson
{
    typedef GenericDocument<UTF16<> > WDocument;
    typedef GenericValue<UTF16<> > WValue;
    typedef GenericStringBuffer<UTF16<> > WStringBuffer;
    typedef Writer<WStringBuffer, UTF16<>, UTF16<> > WStringBufferWriter;
}

enum class MessageType : int
{
    Inventory = 0
};

class BaseMessage
{
protected:
    MessageType m_Type;

    virtual void serializeBody(rapidjson::WValue& body, rapidjson::WDocument::AllocatorType& allocator) = 0;

public:
    BaseMessage(MessageType type)
        : m_Type(type)
    {}

    std::wstring toJSONString()
    {
        rapidjson::WDocument document;
        document.SetObject();

        rapidjson::WValue body;
        body.SetObject();

        serializeBody(body, document.GetAllocator());

        document.AddMember(L"type", (int)m_Type, document.GetAllocator());
        document.AddMember(L"body", body, document.GetAllocator());

        rapidjson::WStringBuffer buffer;
        rapidjson::WStringBufferWriter writer(buffer);
        document.Accept(writer);

        return buffer.GetString();
    }

    virtual ~BaseMessage() {};

};