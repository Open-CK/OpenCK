#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "../../../files/esm/esmreader.hpp"
#include "../../../files/esm/esmwriter.hpp"
#include "../../../files/filepaths.hpp"
#include "../world/data.hpp"

#include <QObject>

class ESMReader;
class ESMWriter;

class Document : public QObject
{
    Q_OBJECT

public:
    Document(const QStringList& files, bool isNew, bool isBase);
    ~Document();

    void preload(const QString& fileName);
	void load();
    void save(const QString& savePath);

    void setAuthor(const QString& author);
    void setDescription(const QString& desc);

    bool isNewFile() const;
	bool isBase() const;
	const QString getSavePath() const;
	QStringList getDerivedFiles() const;
	QStringList getParentFiles() const;

private:
    void createNew();

    FilePaths paths;
    QStringList derivedFiles;
    QString savePath;
    bool newFile;
	bool base;

    Data data;
	std::unique_ptr<ESMReader> reader;
};

#endif // DOCUMENT_H
