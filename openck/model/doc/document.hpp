#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "../tools/reports.hpp"
#include "../world/data.hpp"
#include "../../../files/esm/esmreader.hpp"
#include "../../../files/esm/esmwriter.hpp"
#include "../../../files/filepaths.hpp"

#include <QObject>

class ESMReader;
class ESMWriter;

class Document : public QObject
{
    Q_OBJECT

public:
    Document(const QStringList& contentFiles, const QString& savePath, bool isNew);
    ~Document();

    void save(const QString& savePath);

    bool isNewFile() const;
	bool isBase() const;
	const QString getSavePath() const;
	QStringList getContentFiles() const;

	std::shared_ptr<ReportModel> getReport();

	const Data& getData() const;
	Data& getData();

private:
    void createNew();

    FilePaths paths;
    QStringList contentFiles;
    QString savePath;
    bool newFile;
	bool base;

	std::shared_ptr<ReportModel> reports;

    Data data;
};

#endif // DOCUMENT_H
