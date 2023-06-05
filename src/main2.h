#ifndef main2_INCLUDED
#define main2_INCLUDED

#include <string>
#include <map>

enum class ArgumentKind {
	Integer = 1,
	Float = 2,
	String = 3,
	Data = 4
};

class Argument {
public:
	Argument(ArgumentKind kind);
	virtual ~Argument();

private:
	ArgumentKind kind;
protected:
	virtual int doParse(const char* data) = 0;
public:
	int parse(const char* data);

	ArgumentKind getKind();
};

class ArgumentInteger : public Argument {
public:
	ArgumentInteger();

protected:
	int doParse(const char* data) override;

private:
	__int64 body;
public:
	__int64 getBody();
};

class ArgumentFloat : public Argument {
public:
	ArgumentFloat();

protected:
	int doParse(const char* data) override;

private:
	double body;
public:
	double getBody();
};

class ArgumentString : public Argument {
public:
	ArgumentString();

protected:
	int doParse(const char* data) override;

private:
	char* body;
public:
	const char* getBody();
};

class ArgumentData : public Argument {
public:
	ArgumentData();

protected:
	int doParse(const char* data) override;

private:
	int bodySize;
	char* body;
};

class Arguments {
private:
	std::map<std::string, Argument*> items;
public:
	void parse(const char* data, int dataSize);
	Argument* get(const std::string name);
};

int start();

extern std::string (*build)(Arguments& arguments);

#endif
