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

typedef __int64 Integer;
typedef double Float;
typedef const char* String_;

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
	Integer body;
public:
	Integer getBody();
};

class ArgumentFloat : public Argument {
public:
	ArgumentFloat();

protected:
	int doParse(const char* data) override;

private:
	Float body;
public:
	Float getBody();
};

class ArgumentString : public Argument {
public:
	ArgumentString();

protected:
	int doParse(const char* data) override;

private:
	String_ body;
public:
	String_ getBody();
};

class ArgumentData : public Argument {
public:
	ArgumentData();

protected:
	int doParse(const char* data) override;

private:
	int bodySize;
	const char* body;
};

class Arguments {
public:
	Arguments();
	~Arguments();

private:
	std::map<std::string, Argument*> items;
private:
	void doClear();
public:
	void clear();
	void parse(const char* data, int dataSize);
	Argument* get(const std::string name);

	Integer getInteger(const std::string name, Integer default_ = 0);
	Float getFloat(const std::string name, Float default_ = 0);
	String_ getString(const std::string name, String_ default_ = NULL);
};

extern std::string (*build)(Arguments& arguments);

extern void printWarning(std::string message);
extern int start();

#endif
