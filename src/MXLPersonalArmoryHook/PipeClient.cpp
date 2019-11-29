#include <PipeClient.h>

PipeClient g_PipeClient(DEFAULT_PIPE_ADDRESSW);

PipeClient::PipeClient(const std::wstring& address)
    : m_PipeAddress(address)
{}

void PipeClient::connect()
{
    m_Pipe = CreateFileW(m_PipeAddress.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
}

void PipeClient::send(const std::wstring& message)
{
    DWORD len;
    BOOL success = WriteFile(m_Pipe, message.c_str(), message.size() * sizeof(wchar_t), &len, NULL);
}

void PipeClient::disconnect()
{
    CloseHandle(m_Pipe);
}