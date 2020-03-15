#include "loader.hpp"
#include "../../model/doc/document.hpp"
#include "../../../ui/ui_loaderdialog.h"

#include <sstream>

LoaderDialog::LoaderDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::loaderdialog)
{
    aborted = false;
    ui->setupUi(this);
}

LoaderDialog::~LoaderDialog()
{
    delete ui;
}

void LoaderDialog::assign(Document* document)
{
    this->document = document;

    std::stringstream ss;
    ss << "Loading " << document->getSavePath().toStdString();
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

    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(cancel()));

    setFixedSize(383, 162);

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

void LoaderDialog::abort(const QString& err)
{
    aborted = true;
    error = err;
}

void LoaderDialog::cancel()
{
    if (!aborted)
    {
        emit cancel(document);
    }
    else
    {
        emit close(document);
    }

    reject();
}

void LoaderView::add(Document* document)
{
    LoaderDialog* dialog = new LoaderDialog();
    dialog->assign(document);

    connect(dialog, SIGNAL(cancel(Document*)),
        this, SIGNAL(cancel(Document*)));

    connect(dialog, SIGNAL(close(Document*)),
        this, SIGNAL(close(Document*)));

    documents.insert(document, dialog);
}

void LoaderView::loadingStopped(Document* document, bool completed, const QString& error)
{
    auto it = documents.begin();

    for (; it != documents.end(); ++it)
    {
        if (it.key() == document)
        {
            break;
        }
    }

    if (it == documents.end())
    {
        return;
    }

    if (completed || error.isEmpty())
    {
        delete it.value();
        documents.erase(it);
    }
    else
    {
        it.value()->abort(error);
        documents.erase(it);
    }
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
