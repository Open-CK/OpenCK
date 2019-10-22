#include "loader.hpp"
#include "../../../ui/ui_loaderdialog.h"

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