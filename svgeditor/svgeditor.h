#pragma once
#include <QMainWindow>
#include "svgview.h"
#include "ui_svgeditor.h"
#include <QGraphicsSvgItem>

class SvgEditor : public QMainWindow
{
    Q_OBJECT

public:
    SvgEditor(QWidget *parent = Q_NULLPTR);
    QColor getFillColor() { return m_fillColor; }

public slots:
	void onOpenFileTriggered();
	void onNewFileTriggered();
    void onSaveFileTriggered();
    void onExitAppTriggered();
	void onActionLineTriggered();
	void onActionRectTriggered();
	void onActionSelectTriggered();
	void onActionCurveTriggered();
	void onActionTextTriggered();
	void onActionHexagonTriggered();
	void onActionCircleTriggered();
    void onSvgWidthTextEdited(QString val);
    void onSvgHeightTextEdited(QString val);
    void onScaleSvgValueChanged(int);
    void onScaleSvgValueReleased();
    void onChangeSvgBgClicked();
    void onFillColorButtonClicked();

private:
    void initMainWindow();
    void initSvgView();
	void initLeftToolBar();
	void initRightSettingBar();
    void showSvgFileItem(const QString& file);
    void CreateSvgView();
	void resetToCenter(QWidget* w);

private:
    Ui::SvgEditorClass ui;
    SvgView* m_SvgView;
    QColor m_fillColor;
    QGraphicsSvgItem *m_svgItem;
};
