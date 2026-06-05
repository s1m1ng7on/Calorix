#include "Helper.h"

bool Helper::isToday(const time_t& entryTimeStamp) {
	time_t currentTimeStamp = std::time(nullptr);

	tm* currentTime = std::localtime(&currentTimeStamp);
	tm* entryTime = std::localtime(&entryTimeStamp);

	if (currentTime->tm_mday == entryTime->tm_mday &&
		currentTime->tm_mon == entryTime->tm_mon &&
		currentTime->tm_year == entryTime->tm_year)
		return true;

	return false;
}
