#ifndef MESSAGES_H
#define MESSAGES_H

#include <QString>
#include <QVector>
#include <QVectorIterator>

struct Message
{
	enum Level
	{
		Info = 0,
		Warning = 1,
		Error = 2,
		Critical = 3,
		Default = 4
	};

	QString message;
	QString hint;
	Level level;

	Message();
	Message(const QString& message, const QString& hint, Level level);
	
	static QString toString(Level level);
};

class Messages
{
public:
	typedef QVector<Message>::const_iterator Iterator;
	
	Messages(Message::Level default_);

	void append(const QString& message, const QString& hint = "", Message::Level = Message::Default);

	Iterator begin() const;
	Iterator end() const;

private:
	QVector<Message> messages;
	Message::Level defaultLevel;
};

#endif // MESSAGES_H
