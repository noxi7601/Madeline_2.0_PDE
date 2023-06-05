#include <string.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <windows.h>

#include "main2.h"

LPCWSTR className = L"e9ec3947-4209-4eb4-9f91-36ef7ffbe183";
HWND handle = 0;

std::string (*build)(Arguments& arguments) = NULL;

// Argument

Argument::Argument(ArgumentKind kind) {
	this->kind = kind;
}

Argument::~Argument() {
}

int Argument::parse(const char* data) {
	return doParse(data);
}

ArgumentKind Argument::getKind() {
	return this->kind;
}

// ArgumentInteger

ArgumentInteger::ArgumentInteger() : Argument(ArgumentKind::Integer) {
	this->body = 0;
}

int ArgumentInteger::doParse(const char* data) {
	this->body = *((__int64*) data);

	return sizeof(this->body);
}

__int64 ArgumentInteger::getBody() {
	return this->body;
}

// ArgumentFloat

ArgumentFloat::ArgumentFloat() : Argument(ArgumentKind::Float) {
	this->body = body;
}

int ArgumentFloat::doParse(const char* data) {
	this->body = *((double*) data);

	return sizeof(this->body);
}

double ArgumentFloat::getBody() {
	return this->body;
}

// ArgumentString

ArgumentString::ArgumentString() : Argument(ArgumentKind::String) {
	this->body = NULL;
}

int ArgumentString::doParse(const char* data) {
	int bodySize = *((int*) data);
	this->body = bodySize > 0 ? const_cast<char*>(data + sizeof(int)) : NULL;

	return sizeof(bodySize) + bodySize;
}

const char* ArgumentString::getBody() {
	return this->body;
}

// ArgumentData

ArgumentData::ArgumentData() : Argument(ArgumentKind::Data) {
	this->bodySize = 0;
	this->body = NULL;
}

int ArgumentData::doParse(const char* data) {
	this->bodySize = *((int*) data);
	this->body = bodySize > 0 ? const_cast<char*>(data + sizeof(int)) : NULL;

	return sizeof(this->bodySize) + this->bodySize;
}

// Arguments

void Arguments::parse(const char* data, int dataSize) {
	this->items.clear();

	int offset = 0;
	while (offset < dataSize) {
		int nameSize = *((int*) (data + offset));
		offset += sizeof(int);

		const char* name = (const char*) (data + offset);
		offset += nameSize;

		ArgumentKind argumentKind = (ArgumentKind) (*((int*) (data + offset)));
		offset += sizeof(int);

		Argument* argument;
		switch (argumentKind) {
		case ArgumentKind::Integer:
			argument = new ArgumentInteger();
			break;
		case ArgumentKind::Float:
			argument = new ArgumentFloat();
			break;
		case ArgumentKind::String:
			argument = new ArgumentString();
			break;
		case ArgumentKind::Data:
			argument = new ArgumentData();
			break;
		default:
			argument = NULL;
		}
		if (argument != NULL) {
			offset += argument->parse(data + offset);
			this->items.insert({
				name,
				argument
			});
		} else {
			break;
		}
	}
}

Argument* Arguments::get(const std::string name) {
	auto result = this->items.find(name);
	return result != this->items.end() ? result->second : NULL;
}

// Unit

LRESULT APIENTRY handler(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_USER) {
        return wParam;
    } else if (msg == WM_COPYDATA) {
    	PCOPYDATASTRUCT in = (PCOPYDATASTRUCT) lParam;
    	if (build != NULL) {
    		Arguments arguments;
    		arguments.parse((const char*) in->lpData, in->cbData);
    		std::string result = build(arguments);

    		COPYDATASTRUCT out;
    		out.dwData = 0;
    		out.cbData = result.length() + 1;
    		out.lpData = (void*) result.c_str();
    		SendMessage((HWND) wParam, WM_COPYDATA, (WPARAM) handle, (LPARAM) &out);
    	}
    }

    return DefWindowProc(handle, msg, wParam, lParam);
}

int start() {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASSW wndClass;
    wndClass.style = 0;
    wndClass.lpfnWndProc = &handler;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = 0;
    wndClass.hCursor = 0;
    wndClass.hbrBackground = 0;
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = className;

    if (!RegisterClassW(&wndClass)) {
        return -1;
    }

    handle = CreateWindowExW(
        0,
        className,
        L"",
        WS_POPUP,
        0, 0, 0, 0,
        0, 0,
        hInstance,
        NULL
    );
    if (handle == NULL) {
        return -2;
    }

    MSG msg;
    while (GetMessageW(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return 0;
}
