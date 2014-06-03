#include "watershedmarkerdialog.h"
#include "ui_watershedmarkerdialog.h"

WatershedMarkerDialog::WatershedMarkerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WatershedMarkerDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Tool);
    brushMenu = new QMenu(this);
    brushMenu->addAction(tr("Marker"), this, SLOT(onBrushPencil()));
    brushMenu->addAction(tr("Eraser"), this, SLOT(onBrushEraser()));
    ui->brushModeButton->setMenu(brushMenu);
    m_colour = QColor(255, 255, 255);
    ui->drawer->setDrawMode(QImageInteractiveDrawer::PENCIL);

    connect(ui->previewButton, &QPushButton::clicked, this, &WatershedMarkerDialog::onPreviewButtonClicked);
    connect(ui->undoButton, &QPushButton::clicked, this, &WatershedMarkerDialog::onUndoButtonClicked);
    connect(ui->redoButton, &QPushButton::clicked, this, &WatershedMarkerDialog::onRedoButtonClicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &WatershedMarkerDialog::onResetButtonClicked);
    connect(ui->drawer, &QImageInteractiveDrawer::mouseReleased, this, &WatershedMarkerDialog::onMarkFinished);
    connect(&markSpace, &CAIGA::WorkSpace::workStarted, this, &WatershedMarkerDialog::onWorkStarted);
    connect(&markSpace, &CAIGA::WorkSpace::workFinished, this, &WatershedMarkerDialog::onWorkFinished);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &WatershedMarkerDialog::handleAccepted);
    connect(ui->autoButton, &QPushButton::clicked, this, &WatershedMarkerDialog::onAutoClicked);
}

WatershedMarkerDialog::~WatershedMarkerDialog()
{
    delete ui;
}

void WatershedMarkerDialog::setPenColour(const QColor &c)
{
    m_colour = c;
    ui->drawer->setPenColour(m_colour);
}

void WatershedMarkerDialog::setOriginalMat(const Mat *const src, const Mat *previousMarks)
{
    //use an empty zeros Mat as following works' src
    //while following works' dst will be a mask containing seeds drawed by user or machine
    Mat marks = previousMarks == NULL ? Mat(src->rows, src->cols, CV_8UC1, Scalar(0)) : *previousMarks;
    CAIGA::WorkBase rawBase(src, &marks);
    markSpace.reset(&rawBase);
    QSize s(src->cols, src->rows);
    ui->drawer->setMinimumSize(s);
    ui->drawer->setMaximumSize(s);
}

void WatershedMarkerDialog::onAutoClicked()
{
    this->onWorkStarted();
    cv::Mat autoGenerated = markSpace.first()->src->clone();
    cv::Mat temp;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7));
    cv::erode(autoGenerated, autoGenerated, element);//erode to remove small white spots
    /*
     * dilate to remove small black spots, but our grains are black.
     * so we use erode above to remove white spots instead of dialte.
     */
    //cv::dilate(temp, *dst, element);

    //open and close to highlight the objects
    element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(17, 17));
    cv::morphologyEx(autoGenerated, temp, cv::MORPH_OPEN, element);
    cv::morphologyEx(temp, autoGenerated, cv::MORPH_CLOSE, element);

    //create binary image
    cv::adaptiveThreshold(autoGenerated, temp, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY_INV, 105, 0);

    //erode twice to seperate regions
    cv::erode(temp, temp, element, cv::Point(-1, -1), 2);

    //add this auto work to markSpace
    cv::bitwise_or(temp, *markSpace.last()->dst, autoGenerated);//combine the previous work and this one
    CAIGA::WorkBase *autoWork = new CAIGA::WorkBase(markSpace.last()->dst, &autoGenerated);
    markSpace.append(autoWork);//markSpace will take control of the memory management of autoWork

    this->onWorkFinished();
    ui->previewButton->setEnabled(true);
    ui->undoButton->setEnabled(true);
    ui->resetButton->setEnabled(true);
}

void WatershedMarkerDialog::onMarkFinished(const QVector<QPointF> &pv)
{
    if (ui->drawer->getDrawMode() == QImageInteractiveDrawer::PENCIL) {
        markSpace.newPencilWork(pv, true);
    }
    else {
        markSpace.newEraserWork(pv, false);
    }
    ui->resetButton->setEnabled(true);
    ui->undoButton->setEnabled(true);
    ui->redoButton->setEnabled(false);
    ui->previewButton->setEnabled(true);
}

void WatershedMarkerDialog::onResetButtonClicked()
{
    markSpace.reset();
    ui->undoButton->setEnabled(false);
    ui->previewButton->setEnabled(false);
    ui->redoButton->setEnabled(false);
    ui->resetButton->setEnabled(false);
    emit reseted();
}

void WatershedMarkerDialog::onUndoButtonClicked()
{
    markSpace.undo();
    ui->redoButton->setEnabled(true);
    if (markSpace.count() < 2) {
        ui->undoButton->setEnabled(false);
    }
    ui->resetButton->setEnabled(true);
}

void WatershedMarkerDialog::onRedoButtonClicked()
{
    markSpace.redo();
    if (markSpace.countUndone() < 1) {
        ui->redoButton->setEnabled(false);
    }
    ui->resetButton->setEnabled(true);
    ui->undoButton->setEnabled(true);
    ui->previewButton->setEnabled(true);
}

void WatershedMarkerDialog::updateMarkers()
{
    cv::cvtColor(*markSpace.first()->src, rawMat, CV_GRAY2BGR);
    cv::Mat *mask = markSpace.getLastMatrix();//remember the markSpace contains only the drawing
    rawMat.setTo(Scalar(m_colour.blue(), m_colour.green(), m_colour.red()), *mask);//BGR in openCV
    ui->drawer->setImage(CAIGA::Image::convertMat2QImage(rawMat));//we cook our own display image
}

void WatershedMarkerDialog::onPreviewStarted()
{
    ui->buttonBox->setEnabled(false);
    ui->previewButton->setEnabled(false);
}

void WatershedMarkerDialog::onPreviewFinished()
{
    ui->buttonBox->setEnabled(true);
    ui->previewButton->setEnabled(true);
}

void WatershedMarkerDialog::onWorkStarted()
{
    ui->buttonBox->setEnabled(false);
}

void WatershedMarkerDialog::onWorkFinished()
{
    ui->buttonBox->setEnabled(true);
    this->updateMarkers();
}

void WatershedMarkerDialog::onBrushPencil()
{
    ui->brushModeButton->setText(tr("Marker"));
    ui->drawer->setDrawMode(QImageInteractiveDrawer::PENCIL);
    ui->drawer->setPenColour(m_colour);
}

void WatershedMarkerDialog::onBrushEraser()
{
    ui->brushModeButton->setText(tr("Eraser"));
    ui->drawer->setDrawMode(QImageInteractiveDrawer::ERASER);
    ui->drawer->setPenColour(QColor(Qt::black));
}
