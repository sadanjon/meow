#ifndef ILINE_READER_H
#define ILINE_READER_H

namespace meow {
	
class ILineReader {
public:
	virtual ~ILineReader() {}
	virtual Optional<std::string> nextLine() = 0;
};

} // namespace meow

#endif // ILINE_READER_H