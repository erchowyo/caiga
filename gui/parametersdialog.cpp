#include "parametersdialog.h"
#include "ui_parametersdialog.h"

ParametersDialog::ParametersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParametersDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Tool);
    connect(ui->kSizeSlider, &QSlider::valueChanged, this, &ParametersDialog::onSliderValueChanged);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ParametersDialog::onAcceptButtonPressed);
}

ParametersDialog::~ParametersDialog()
{
    delete ui;
}

void ParametersDialog::onSliderValueChanged(int s)
{
    ui->kSizeLabel->setText(kSizeText + "(" + QString::number(s * 2 - 1) + ")");
}

void ParametersDialog::setSigColourText(const QString &c)
{
    ui->sigmaColourLabel->setText(c);
}

void ParametersDialog::setSigSpaceText(const QString &s)
{
    ui->sigmaSpaceLabel->setText(s);
}

void ParametersDialog::setkSizeText(const QString &k)
{
    kSizeText = k;
    this->onSliderValueChanged(ui->kSizeSlider->value());
}

void ParametersDialog::setMode(int mode)
{
    switch (mode) {
    case 1://adaptiveThreshold(binaryzation)
        this->setkSizeText("Block Size");
        ui->sigmaSpace->setMinimum(-999);
        ui->sigmaSpaceLabel->setText("Constant C");
        ui->sigmaColour->setVisible(false);
        ui->sigmaColourLabel->setVisible(false);
        break;
    case 2:
        this->setkSizeText("Aperture Size");
        ui->kSizeSlider->setValue(2);
        ui->kSizeSlider->setMinimum(2);
        ui->kSizeSlider->setMaximum(4);
        ui->sigmaSpaceLabel->setText("High Threshold");
        ui->sigmaSpace->setValue(400);
        ui->sigmaColourLabel->setText("Low Threshold");
        ui->sigmaColour->setValue(150);
        ui->checkBox->setText("L2 Gradient");
        break;
    default://adaptiveBilateralFilter
        this->setkSizeText("Kernel Size");
        ui->checkBox->setVisible(false);
        break;
    }
}

void ParametersDialog::onAcceptButtonPressed()
{
    emit parametersAccepted(ui->kSizeSlider->value() * 2 - 1, ui->sigmaSpace->value(), ui->sigmaColour->value(), ui->checkBox->isChecked());
}