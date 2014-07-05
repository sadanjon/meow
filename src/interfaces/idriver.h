#ifndef IDRIVER_H 
#define IDRIVER_H

namespace meow {
	
class IDriver {
public:
	virtual ~IDriver() {}

	virtual void run(int argc, char **argv) = 0;
};

} // namespace meow

#endif // IDRIVER_H