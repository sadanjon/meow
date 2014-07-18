#ifndef IWINDOW_SERVICE 
#define IWINDOW_SERVICE

#include <exception>

namespace meow {
	
class IWindowService {
public:
	virtual ~IWindowService() {}
	
	virtual void initialize() = 0;
	virtual void swap() = 0;

	class FailedToInitializeWindow : public std::exception {};
};

} // namespace meow

#endif // IWINDOW_SERVICE