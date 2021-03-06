#include <assert.h>

#include "ColorPaletteRollOut.hpp"
#include "../../ImageArea/ImageArea.hpp"

ColorPaletteRollOut::ColorPaletteRollOut()
{
	colorPaletteSwatchArea = new ColorPaletteSwatchArea();

	QPushButton *editButton = new QPushButton(tr("Edit"));
	connect(editButton, SIGNAL(clicked()), this, SLOT(editColor()));

	QPushButton *sortButton = new QPushButton(tr("Sort"));
	//connect(sortButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QPushButton *swapValuesButton = new QPushButton(tr("Swap Values"));
	//connect(swapValuesButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QPushButton *swapIndexButton = new QPushButton(tr("Swap Index"));
	//connect(swapIndexButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QPushButton *importButton = new QPushButton(tr("Import"));
	connect(importButton, SIGNAL(clicked()), this, SLOT(importColorPalette()));

	QPushButton *exportButton = new QPushButton(tr("Export"));
	connect(exportButton, SIGNAL(clicked()), this, SLOT(exportColorPalette()));

	QHBoxLayout *firstButtonRow = new QHBoxLayout();
	firstButtonRow->setMargin(0);
	firstButtonRow->addWidget(editButton);
	firstButtonRow->addWidget(sortButton);

	QHBoxLayout *secondButtonRow = new QHBoxLayout();
	secondButtonRow->setMargin(0);
	secondButtonRow->addWidget(swapValuesButton);
	secondButtonRow->addWidget(swapIndexButton);

	QHBoxLayout *thirdButtonRow = new QHBoxLayout();
	thirdButtonRow->setMargin(0);
	thirdButtonRow->addWidget(importButton);
	thirdButtonRow->addWidget(exportButton);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->setMargin(0);
	layout->addWidget(colorPaletteSwatchArea);
	layout->addLayout(firstButtonRow);
	layout->addLayout(secondButtonRow);
	layout->addLayout(thirdButtonRow);
	setLayout(layout);

	colorDialog = new QColorDialog(this);
	colorDialog->setOption(QColorDialog::NoButtons);
}

ColorPaletteRollOut::~ColorPaletteRollOut()
{
	assert(colorDialog);
	delete colorDialog;
}

ColorPaletteSwatchArea *ColorPaletteRollOut::getColorPaletteSwatchArea()
{
	assert(colorPaletteSwatchArea);
	return colorPaletteSwatchArea;
}

QColorDialog *ColorPaletteRollOut::getColorDialog()
{
	assert(colorDialog);
	return colorDialog;
}

void ColorPaletteRollOut::editColor()
{
	Image *currentImage = ImageArea::getCurrentImage();

	if (!currentImage)
	{
		QMessageBox::critical(nullptr, "Error", "Create a new project or import an image before editing a color in the color palette.");
		return;
	}

	assert(colorDialog);
	colorDialog->setWindowTitle("Edit Color (Index #" + QString::number(currentImage->getSelectedColorIndex()) + ")");
	colorDialog->setCurrentColor(currentImage->getSelectedColor());
	colorDialog->open();
}

void ColorPaletteRollOut::importColorPalette()
{
	Image *currentImage = ImageArea::getCurrentImage();

	if (!currentImage)
	{
		QMessageBox::critical(nullptr, "Error", "Create a new project or import an image before importing a color palette.");
		return;
	}

	QString fileName = QFileDialog::getOpenFileName(this, tr("Import Color Palette"), "", tr("Palette Definition Files (*.pal)"));

	if (fileName.isNull() || fileName.isEmpty())
		return;

	currentImage->importColorPalette(fileName);
}

void ColorPaletteRollOut::exportColorPalette()
{
	QMessageBox::warning(nullptr, "Placeholder", "Export Color Palette");
}
