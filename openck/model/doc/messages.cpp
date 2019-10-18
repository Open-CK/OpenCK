#include "messages.hpp"

Message::Message()
	: level(Default)
{
}

Message::Message(const QString& message, const QString& hint, Level level) : 
	message(message),
	hint(hint),
	level(level)
{
}

QString Message::toString(Level level)
{
	switch (level)
	{
	case Message::Info:		return QString("Information");
	case Message::Warning:	return QString("Warning");
	case Message::Error:	return QString("Error");
	case Message::Critical: return QString("Critical Error");
	case Message::Default:	break;
	}

	return "";
}

Messages::Messages(Message::Level default_) :
	defaultLevel(default_)
{
}

void Messages::append(const QString& message, const QString& hint, Message::Level level)
{
	if (level == Message::Default)
	{
		level = defaultLevel;
	}

	messages.push_back(Message(message, hint, level));
}

Messages::Iterator Messages::begin() const
{
	return messages.constBegin();
}

Messages::Iterator Messages::end() const
{
	return messages.constEnd();
}
