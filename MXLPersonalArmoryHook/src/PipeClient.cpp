#include <PipeClient.h>

PipeClient g_PipeClient(DEFAULT_PIPE_ADDRESSW);

PipeClient::PipeClient(const std::wstring& address)
    : m_PipeAddress(address)
{}

void PipeClient::connect()
{
    DWORD dwMode = PIPE_READMODE_MESSAGE;
    m_Pipe = CreateFileW(m_PipeAddress.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    SetNamedPipeHandleState(m_Pipe, &dwMode, NULL, NULL);
}

void PipeClient::send(const std::wstring& message)
{
    DWORD len;
    WriteFile(m_Pipe, message.c_str(), message.size() * sizeof(wchar_t), &len, NULL);
}

bool PipeClient::read(std::wstring& msgOut)
{
    DWORD len;

    msgOut.resize(1024);
    bool result = ReadFile(m_Pipe, &msgOut[0], 1024, &len, NULL);
    msgOut.resize(len / 2);

    return result;
}

void PipeClient::disconnect()
{
    CloseHandle(m_Pipe);
}