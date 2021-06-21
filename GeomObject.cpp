#include "GeomObject.h"


int GeomObject::getZ()
{
	return zValue;
}

int GeomObject::getPointCount()
{
	return pointCount;
}

QVector<QPoint> GeomObject::getBody()
{
	return body;
}

QColor GeomObject::getOutline()
{
	return outlineColor;
}

QColor GeomObject::getFill()
{
	return fillColor;
}

int GeomObject::getObjectType()
{
	return objectType;
}

int GeomObject::getLayer()
{
	return layer;
}

int GeomObject::getisFilled()
{
	return isFilled;
}

void GeomObject::setZ(int zVal)
{
	zValue = zVal;
}

void GeomObject::setBody(QVector<QPoint> pointsN)
{
	body = pointsN;
}

void GeomObject::setFill(QColor color)
{
	fillColor = color;
}

void GeomObject::setOutline(QColor color)
{
	outlineColor = color;
}

void GeomObject::setIsFill()
{
	isFilled = 1;
}


