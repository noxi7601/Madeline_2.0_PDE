#include <string.h>

#include <string>
#include <algorithm>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>

#include <windows.h>

#include "main2.h"

#define MM_PING (WM_USER + 1000)
#define MM_OPEN (WM_USER + 1001)
#define MM_CLOSE (WM_USER + 1002)

LPCWSTR className = L"e9ec3947-4209-4eb4-9f91-36ef7ffbe183";

HWND handle = 0;
std::list<HWND> handles;

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
	this->body = *((Integer*) data);

	return sizeof(this->body);
}

Integer ArgumentInteger::getBody() {
	return this->body;
}

// ArgumentFloat

ArgumentFloat::ArgumentFloat() : Argument(ArgumentKind::Float) {
	this->body = body;
}

int ArgumentFloat::doParse(const char* data) {
	this->body = *((Float*) data);

	return sizeof(this->body);
}

Float ArgumentFloat::getBody() {
	return this->body;
}

// ArgumentString

ArgumentString::ArgumentString() : Argument(ArgumentKind::String) {
	this->body = NULL;
}

int ArgumentString::doParse(const char* data) {
	int bodySize = *((int*) data);
	this->body = bodySize > 0 ? data + sizeof(int) : NULL;

	return sizeof(bodySize) + bodySize;
}

String_ ArgumentString::getBody() {
	return this->body;
}

// ArgumentData

ArgumentData::ArgumentData() : Argument(ArgumentKind::Data) {
	this->bodySize = 0;
	this->body = NULL;
}

int ArgumentData::doParse(const char* data) {
	this->bodySize = *((int*) data);
	this->body = bodySize > 0 ? data + sizeof(int) : NULL;

	return sizeof(this->bodySize) + this->bodySize;
}

// Arguments

Arguments::Arguments() {
}

Arguments::~Arguments() {
	doClear();
}

void Arguments::doClear() {
	for (auto i : this->items) {
		delete i.second;
	}

	this->items.clear();
}

void Arguments::clear() {
	doClear();
}

void Arguments::parse(const char* data, int dataSize) {
	doClear();

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

Integer Arguments::getInteger(const std::string name, Integer default_) {
	ArgumentInteger* argument = dynamic_cast<ArgumentInteger*>(get(name));
	return argument != NULL ? argument->getBody() : default_;
}

Float Arguments::getFloat(const std::string name, Float default_) {
	ArgumentFloat* argument = dynamic_cast<ArgumentFloat*>(get(name));
	return argument != NULL ? argument->getBody() : default_;
}

String_ Arguments::getString(const std::string name, String_ default_) {
	ArgumentString* argument = dynamic_cast<ArgumentString*>(get(name));
	return argument != NULL ? argument->getBody() : default_;
}

// Unit

void check() {
	if (handles.size() > 0) {
		for (auto i = handles.begin(); i != handles.end(); ) {
			HWND handle = *i;
			DWORD_PTR o = 0;
			i++;

#ifdef __DEBUG__
			o = SendMessage(handle, MM_PING, 2023, 0);
#else
			SendMessageTimeoutW(handle, MM_PING, 2023, 0, SMTO_NORMAL, 3000, &o);
#endif
			if (o != 2023) {
				handles.remove(handle);

				std::cout << "remove: " << handle << std::endl;
			}
		}

		if (handles.size() == 0) {
			PostQuitMessage(0);
		}
	}
}

void open(HWND handle) {
	handles.push_back(handle);

	std::cout << "open: " << handle << std::endl;
}

void close(HWND handle) {
	std::cout << "close: " << handle << std::endl;

	auto i = std::find(handles.begin(), handles.end(), handle);
	if (i != handles.end()) {
		handles.remove(handle);
	}

	if (handles.size() == 0) {
		PostQuitMessage(0);
	}
}

LRESULT APIENTRY handler(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_USER) {
        return wParam;
    } else if (msg == WM_TIMER) {
    	if (wParam == 1000) {
    		check();
    	}
    } else if (msg == WM_COPYDATA) {
    	PCOPYDATASTRUCT in = (PCOPYDATASTRUCT) lParam;
    	if (build != NULL) {
    		Arguments arguments;
    		arguments.parse(static_cast<char*>(in->lpData), in->cbData);
    		std::string result = build(arguments);

    		COPYDATASTRUCT out;
    		out.dwData = in->dwData;
    		out.cbData = result.length() + 1;
    		out.lpData = (void*)(result.c_str());
    		SendMessage((HWND) wParam, WM_COPYDATA, (WPARAM) handle, (LPARAM) &out);

    		return in->dwData;
    	}
    } else if (msg == MM_PING) {
    	return wParam;
    } else if (msg == MM_OPEN) {
    	open(reinterpret_cast<HWND>(wParam));
    } else if (msg == MM_CLOSE) {
    	close(reinterpret_cast<HWND>(wParam));
    }

    return DefWindowProc(handle, msg, wParam, lParam);
}

void printWarning(std::string message) {
}

int start() {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASSW wc;
    wc.style = 0;
    wc.lpfnWndProc = &handler;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = 0;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = className;

    if (!RegisterClassW(&wc)) {
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

    SetTimer(handle, 1000, 100, NULL);

    MSG msg;
    while (GetMessageW(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return 0;
}
