#ifndef IMAIN_LOOP_SERVICE_H 
#define IMAIN_LOOP_SERVICE_H

#include <memory>

namespace meow {

enum class EventType {
	UNKNOWN,
	QUIT
};

struct Event {
	EventType eventType;
};

class ILoopHandler {
public:
	virtual ~ILoopHandler() {}

	virtual void event(const Event &event) = 0;
	virtual void update() = 0;
	virtual bool isQuitRequested() = 0;
};

class IMainLoopService {
public:
	virtual ~IMainLoopService() {}

	virtual void run() = 0;
	virtual void setHandler(const std::shared_ptr<ILoopHandler> &handler) = 0;
	virtual void requestToQuit() = 0;
};

} // namespace meow

#endif // IMAIN_LOOP_SERVICE_H