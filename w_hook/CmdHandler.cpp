#include "CmdHandler.h"
using namespace std;

#define EXCEPTIION_STATE_CHECK \
    if (!m_bInit) return E_NOTIMPL

CCmdHandler::CCmdHandler()
	: m_bInit(FALSE)
	, m_dwErrorCode(0)
	, m_hPipeRead(NULL)
	, m_hPipeWrite(NULL)
{
	ZeroMemory(m_szReadBuffer, sizeof(m_szReadBuffer));
	ZeroMemory(m_szWriteBuffer, sizeof(m_szWriteBuffer));
	ZeroMemory(&m_CommandParam, sizeof(m_CommandParam));
}
CCmdHandler::~CCmdHandler()
{
}

HRESULT CCmdHandler::Initalize()
{
	// 初始化，创建匿名管道
	if (m_bInit) return S_OK;
	m_bInit = TRUE;
	ZeroMemory(m_szReadBuffer, sizeof(m_szReadBuffer));
	ZeroMemory(&m_saOutPipe, sizeof(m_saOutPipe));
	m_saOutPipe.nLength = sizeof(SECURITY_ATTRIBUTES);
	m_saOutPipe.lpSecurityDescriptor = NULL;
	m_saOutPipe.bInheritHandle = TRUE;
	ZeroMemory(&m_startupInfo, sizeof(STARTUPINFO));
	ZeroMemory(&m_processInfo, sizeof(PROCESS_INFORMATION));
	if (!CreatePipe(&m_hPipeRead, &m_hPipeWrite, &m_saOutPipe, PIPE_BUFFER_SIZE))
	{
		m_dwErrorCode = GetLastError();
		return E_FAIL;
	}
	return S_OK;
}
HRESULT CCmdHandler::Finish()
{
	EXCEPTIION_STATE_CHECK;
	if (m_hPipeRead)
	{
		CloseHandle(m_hPipeRead);
		m_hPipeRead = NULL;
	}
	if (m_hPipeWrite)
	{
		CloseHandle(m_hPipeWrite);
		m_hPipeWrite = NULL;
	}
	return S_OK;
}
HRESULT CCmdHandler::HandleCommand(CHCmdParam* pCommmandParam)
{
	EXCEPTIION_STATE_CHECK;
	if (!pCommmandParam || pCommmandParam->iSize != sizeof(CHCmdParam))
		return E_INVALIDARG;
	if (_tcslen(pCommmandParam->szCommand) <= 0)
		return E_UNEXPECTED;
	memset(&m_CommandParam, 0, sizeof(m_CommandParam));
	m_CommandParam = *pCommmandParam;
	return ExecuteCmdWait();
}
HRESULT CCmdHandler::ExecuteCmdWait()
{
	EXCEPTIION_STATE_CHECK;
	HRESULT hResult = E_FAIL;
	DWORD dwReadLen = 0;
	DWORD dwStdLen = 0;
	m_startupInfo.cb = sizeof(STARTUPINFO);
	m_startupInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	m_startupInfo.hStdOutput = m_hPipeWrite;
	m_startupInfo.hStdError = m_hPipeWrite;
	m_startupInfo.wShowWindow = SW_HIDE;
	DWORD dTimeOut = m_CommandParam.iTimeOut >= 3000 ? m_CommandParam.iTimeOut : 5000;
	do
	{
		if (!CreateProcess(NULL, m_CommandParam.szCommand,
			NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL,
			&m_startupInfo, &m_processInfo))
		{
			m_dwErrorCode = GetLastError();
			hResult = E_FAIL;
			break;
		}
		if (WAIT_TIMEOUT == WaitForSingleObject(m_processInfo.hProcess, dTimeOut))
		{
			m_dwErrorCode = GetLastError();
			hResult = CO_E_SERVER_START_TIMEOUT;
			break;
		}
		// 预览管道中数据的内容
		if (!PeekNamedPipe(m_hPipeRead, NULL, 0, NULL, &dwReadLen, NULL)
			|| dwReadLen <= 0)
		{
			m_dwErrorCode = GetLastError();
			hResult = E_FAIL;
			break;
		}
		else
		{
			ZeroMemory(m_szPipeOut, sizeof(m_szPipeOut));
			// 读取管道中的数据
			if (ReadFile(m_hPipeRead, m_szPipeOut, dwReadLen, &dwStdLen, NULL))
			{

				hResult = S_OK;
				break;
			}
			else
			{
				m_dwErrorCode = GetLastError();
				break;
			}
		}
	} while (FALSE);
	if (m_processInfo.hThread)
	{
		CloseHandle(m_processInfo.hThread);
		m_processInfo.hThread = NULL;
	}
	if (m_processInfo.hProcess)
	{
		CloseHandle(m_processInfo.hProcess);
		m_processInfo.hProcess = NULL;
	}
	return hResult;
}
