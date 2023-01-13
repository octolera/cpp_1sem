#pragma once
class Process {
private:
public:
	Process();
	~Process();
	static double process_string(const char*);
	static void from_file(const char*, const char*);
};

