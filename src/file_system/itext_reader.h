#ifndef ITEXT_HEADER_H 
#define ITEXT_HEADER_H

namespace meow {
	
class ITextReader {
public:
	virtual ~ITextReader() {}
	virtual std::string read() = 0;
	
};

} // namespace meow

#endif // ITEXT_HEADER_H