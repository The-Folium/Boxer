#pragma once
#include <iostream>
#include <string>

enum class BodyPart
{
	NONE, HEAD, LIVER, BODY, STOMACH, ARM
};

std::string bodyPartToString(BodyPart part);

std::ostream& operator<<(std::ostream& out, BodyPart part);

int bodyPartPoints(BodyPart part);

BodyPart bodyPartByNumber(int number);
