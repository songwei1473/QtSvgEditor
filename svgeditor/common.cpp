#include "common.h"

QObject* getRootWidget(QObject* w)
{
	if (w == nullptr)
    {
		return nullptr;
    }
    QObject* obj = getRootWidget(w->parent());
	if (obj == nullptr)
    {
		return w;
    }
	return obj;
}
