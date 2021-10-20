#pragma once
#include <QObject>

enum SelectType
{
    SELECT,
	LINE,
	RECTANGLE,
	CURVE,
	TEXT,
	CIRCLE,
	HEXAGON,
	//insert here..
	numValue
};

QObject* getRootWidget(QObject* w);
