#include "BodyPart.h"

std::string bodyPartToString(BodyPart part)
{
	std::string result;
	switch (part)
	{
	case (BodyPart::NONE): return "NONE";
	case (BodyPart::HEAD): return "head";
	case (BodyPart::LIVER): return "liver";
	case (BodyPart::BODY): return "body";
	case (BodyPart::STOMACH): return "stomach";
	case (BodyPart::ARM): return "arm";
	}
	return result;
}

std::ostream& operator<<(std::ostream& out, BodyPart part)
{
	return out << bodyPartToString(part);
}

int bodyPartPoints(BodyPart part)
{
	int points{ 0 };
	switch (part)
	{
	case (BodyPart::NONE): points = 0; break;
	case (BodyPart::HEAD): points = 25 + (std::rand() % 21 - 10); break;
	case (BodyPart::LIVER): points = 33 + (std::rand() % 21 - 10); break;
	case (BodyPart::BODY): points = 15 + (std::rand() % 7 - 3); break;
	case (BodyPart::STOMACH): points = 25 + (std::rand() % 11 - 5); break;
	case (BodyPart::ARM): points = 8 + (std::rand() % 13 - 6); break;
	}
	return points;
}

BodyPart bodyPartByNumber(int number)
{
	return static_cast<BodyPart>(number);
}