#include "loader.hpp"
#include "../../model/doc/document.hpp"
#include "../../../ui/ui_loaderdialog.h"

#include <sstream>

LoaderDialog::LoaderDialog(QWidget* parent) :
	QDialog(parent),
	ui(new Ui::loaderdialog)
{
	ui->setupUi(this);
}

LoaderDialog::~LoaderDialog()
{
	delete ui;
}

void LoaderDialog::assign(Document* document)
{
	std::stringstream ss;
	ss << "Loading " << document->getSavePath().toStdString() << "...";
	setWindowTitle(QString::fromStdString(ss.str()));

	int size = static_cast<int>(document->getContentFiles().size()) + 1;
	if (document->isNewFile())
	{
		size--;
	}

	ui->fileProgressBar->setMinimum(0);
	ui->fileProgressBar->setMaximum(size);
	ui->fileProgressBar->setValue(-1);

	ui->recordProgressBar->setMinimum(0);
	ui->recordProgressBar->setValue(0);

	setFixedSize(390, 120);

	show();
}

void LoaderDialog::nextStage(const QString& name, int records)
{
	ui->fileLabel->setText(name);

	ui->fileProgressBar->setValue(ui->fileProgressBar->value() + 1);

	ui->recordProgressBar->setValue(0);
	ui->recordProgressBar->setMaximum(records > 0 ? records : 1);

	totalRecords = records;
}

void LoaderDialog::nextRecord(int records)
{
	if (records <= totalRecords)
	{
		ui->recordProgressBar->setValue(records);

		std::stringstream ss;
		ss << records << "/" << totalRecords;

		ui->recordLabel->setText(QString::fromStdString(ss.str()));
	}
}

void LoaderView::add(Document* document)
{
	LoaderDialog* dialog = new LoaderDialog();
	dialog->assign(document);

	documents.insert(document, dialog);
}

void LoaderView::loadingStopped(Document* document, bool completed, const QString& error)
{

}

void LoaderView::nextStage(Document* document, const QString& name, int totalRecords)
{
	auto it = documents.find(document);

	if (it != documents.end())
	{
		it.value()->nextStage(name, totalRecords);
	}
}

void LoaderView::nextRecord(Document* document, int records)
{
	auto it = documents.find(document);

	if (it != documents.end())
	{
		it.value()->nextRecord(records);
	}
}
