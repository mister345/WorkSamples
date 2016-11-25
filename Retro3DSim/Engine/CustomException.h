#pragma once
#include "DXErr.h"
#include <string>

#define CUSTOM_GFX_EXCEPTION( hr,note ) GraphicsException( hr,note,_CRT_WIDE(__FILE__),__LINE__ )

class CustomException
{
public:
	CustomException( const wchar_t* file,unsigned int line,const std::wstring& note = L"" );
	const std::wstring& GetNote() const
	{
		return note;
	}
	const std::wstring& GetFile() const
	{
		return file;
	}
	unsigned int GetLine() const
	{
		return line;
	}
	std::wstring GetLocation() const;
	virtual std::wstring GetFullMessage() const = 0;
	virtual std::wstring GetExceptionType() const = 0;
private:
	std::wstring note;
	std::wstring file;
	unsigned int line;
};

class WindowsException : public CustomException
{
public:
	using CustomException::CustomException;
	virtual std::wstring GetFullMessage() const override { return GetNote() + L"\nAt: " + GetLocation(); }
	virtual std::wstring GetExceptionType() const override { return L"Windows Exception"; }
};

class GraphicsException : public CustomException
{
public:
	GraphicsException( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
	std::wstring GetErrorName() const;
	std::wstring GetErrorDescription() const;
	virtual std::wstring GetFullMessage() const override;
	virtual std::wstring GetExceptionType() const override;
private:
	HRESULT hr;
};
