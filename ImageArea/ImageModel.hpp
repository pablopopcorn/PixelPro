#pragma once

#include <QtWidgets>

#include "ImageColorPaletteModel.hpp"

class ImageModel
{
public:
	ImageModel();
	~ImageModel();

	bool newEmpty(unsigned int width, unsigned int height);
	//bool openFromPixmap(const QPixmap &pixmap, ColorPaletteModel *colorPaletteModel);
	unsigned char getDataAt(unsigned int x, unsigned int y);
	void setDataAt(unsigned int x, unsigned y, unsigned char colorIndex);
	void setDataToSelectedColorAt(unsigned int x, unsigned y);
	QColor &getColorAt(unsigned int x, unsigned int y);
	ImageColorPaletteModel *getImageColorPaletteModel();

	inline unsigned int getWidth() { return width; }
	inline unsigned int getHeight() { return height; }

private:
	unsigned char *data;
	unsigned int width, height;

	ImageColorPaletteModel *imageColorPaletteModel;
};