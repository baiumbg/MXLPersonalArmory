#pragma once

#include <Windows.h>
#include <string>

#define DEFAULT_PIPE_ADDRESSW L"\\\\.\\pipe\\MXLPersonalArmoryHook"
#define DEFAULT_PIPE_ADDRESS "\\\\.\\pipe\\MXLPersonalArmoryHook"

class PipeClient
{
public:
    PipeClient(const std::wstring& address);

    void connect();
    void send(const std::wstring& message);
    bool read(std::wstring& msgOut);
    void disconnect();
private:
    std::wstring m_PipeAddress;
    HANDLE m_Pipe;
};

extern PipeClient g_PipeClient;