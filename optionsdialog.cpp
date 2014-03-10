#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

    setWindowIcon(QIcon::fromTheme("configure"));
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}
