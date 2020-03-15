#include "viewmediator.hpp"

#include <QFileDialog>

ViewMediator::ViewMediator(DocumentMediator& docMed) : 
	docMed(docMed)
{   
    w.reset(new MainWindow());

    connect(w.get(), &MainWindow::actionData_triggered, this, &ViewMediator::showDataDialog);
    connect(w.get(), &MainWindow::actionSave_triggered, this, &ViewMediator::showSaveDialog);

	connect(&docMed, SIGNAL(loadRequest(Document*)), &loader, SLOT(add(Document*)));
	
	connect(&docMed, SIGNAL(loadingStopped(Document*, bool, const QString&)), 
		&loader, SLOT(loadingStopped(Document*, bool, const QString&)));

	connect(&docMed, SIGNAL(nextStage(Document*, const QString&, int)),
		&loader, SLOT(nextStage(Document*, const QString&, int)));

	connect(&docMed, SIGNAL(nextRecord(Document*, int)),
		&loader, SLOT(nextRecord(Document*, int)));

	connect(&docMed, SIGNAL(loadMessage(Document*, const QString&)),
		&loader, SLOT(loadMessage(Document*, const QString&)));

    w->show();
}

ViewMediator::~ViewMediator()
{
}

void ViewMediator::setUpDataDialog(const QString& path)
{
    dataPath = path;
    dataDlg.reset(new DataDialog());
    dataDlg->setWindowFlags(dataDlg->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    dataDlg->setUp(path);

    connect(dataDlg.get(), &DataDialog::addDocument, this, &ViewMediator::dataDialogAccepted);
}

void ViewMediator::showDataDialog()
{
    dataDlg->exec();
}

void ViewMediator::dataDialogAccepted(const QStringList& files, const QString& savePath, bool isNew)
{
	emit addDocument(files, savePath, isNew);
}

void ViewMediator::showSaveDialog()
{
    QFileDialog saveDialog;
    saveDialog.setAcceptMode(QFileDialog::AcceptSave);
    saveDialog.setModal(true);
    saveDialog.setDirectory(dataPath);

    emit saveDocument(saveDialog.getSaveFileName(
        nullptr, "Save Plugin File", "", "Elder Scrolls Plugin fies (*.esp)")
    );
}
