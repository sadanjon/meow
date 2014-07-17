#ifndef IDRIVER_RUNNER_H 
#define IDRIVER_RUNNER_H

namespace meow {
	
class IDriver {
public:
	virtual ~IDriver() {}

	virtual int run(int argc, char **argv) = 0;
};

class IDriverRunner {
public:
	virtual ~IDriverRunner() {};

	virtual int run(IDriver &driver, int argc, char **argv) = 0;
};

} // namespace meow

#endif // IDRIVER_RUNNER_H