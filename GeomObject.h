#pragma once
#include <QtWidgets>
class GeomObject
{
private:
	int objectType;
	QVector<QPoint> body;
	QColor fillColor;
	QColor outlineColor;
	int zValue;
	int pointCount;
	int layer;
	int isFilled;
public:
	GeomObject() {
		objectType = 0;
		body.resize(0);
		fillColor = Qt::black;
		outlineColor = Qt::black;
		zValue = 0;
		pointCount = 0;
		layer = 0;
		isFilled = 0;

	}
	GeomObject(int type, QVector<QPoint> points, QColor color1, QColor color2, int z, int count, int lay, int filled) {
		objectType = type; 
		body = points; 
		fillColor = color1;
		outlineColor = color2; 
		zValue = z; 
		pointCount = count;
		layer = lay;
		isFilled = filled;
	}
	int getZ();
	int getPointCount();
	QVector<QPoint> getBody();
	QColor getOutline();
	QColor getFill();
	int getObjectType();
	int getLayer();
	int getisFilled();
	void setZ(int zVal);
	void setBody(QVector<QPoint> pointsN);
	void setFill(QColor color);
	void setOutline(QColor color);
	void setIsFill();
};

