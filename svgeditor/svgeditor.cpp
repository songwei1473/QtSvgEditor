#include <QFileDialog>
#include <QGraphicsDropShadowEffect>
#include <QColorDialog>
#include <QDebug>
#include <QSvgGenerator>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include "svgeditor.h"

SvgEditor::SvgEditor(QWidget *parent)
    : QMainWindow(parent)
    , m_SvgView(nullptr)
{
    ui.setupUi(this);

    setWindowFlags(Qt::Window|Qt::WindowTitleHint|Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    setFixedSize(this->width(), this->height());

    initMainWindow();
	setCentralWidget(ui.layoutWidget);

    m_fillColor.setAlpha(0);
    ui.menu_2->menuAction()->setVisible(false);
    ui.menu_3->menuAction()->setVisible(false);
    ui.label_2->setVisible(false);
    ui.scaleSvgSlider->setVisible(false);
}

void SvgEditor::onOpenFileTriggered()
{
	QString svgFilePath = QFileDialog::getOpenFileName(
		this,
        "选择SVG文件",
		".",
        "SVG文件(*.svg)");
    CreateSvgView();
    showSvgFileItem(svgFilePath);
}

void SvgEditor::onSaveFileTriggered()
{
    qDebug()<<"SvgEditor::onSaveFileTriggered()";

    QString saveFilePath = QFileDialog::getSaveFileName(this, "保存SVG到文件",
        NULL, "SVG文件(*.svg)");

    if (saveFilePath.isEmpty())
    {
        return;
    }

//![configure SVG generator]
    QSvgGenerator generator;
    generator.setFileName(saveFilePath);
    generator.setSize(QSize(m_SvgView->width(), m_SvgView->height()));
    generator.setViewBox(QRect(0, 0, m_SvgView->width(), m_SvgView->height()));
//    generator.setTitle("SVG Generator Example Drawing");
//    generator.setDescription("An SVG drawing created by the SVG Generator "
//                                "Example provided with Qt.");
//![configure SVG generator]
//![begin painting]
    QPainter painter;
    painter.begin(&generator);
//![begin painting]
    m_SvgView->render(&painter);
//![end painting]
    painter.end();
//![end painting]
}

void SvgEditor::onExitAppTriggered()
{
    qApp->quit();
}

void SvgEditor::initSvgView()
{
    QGraphicsDropShadowEffect* eff = new QGraphicsDropShadowEffect(ui.svgWidget);
	eff->setOffset(0, 0);
	eff->setColor(QColor(0, 0, 0, 90));
	eff->setBlurRadius(10);
    ui.svgWidget->setGraphicsEffect(eff);
}

void SvgEditor::initLeftToolBar()
{
	QBrush brush(QColor(255, 255, 255));
	ui.mainToolBar->setBackgroundRole(QPalette::ColorRole::Background);

	QPalette toolbarPal;
	toolbarPal.setBrush(QPalette::ColorRole::Background, brush);
	ui.mainToolBar->setPalette(toolbarPal);

	QGraphicsDropShadowEffect* eff = new QGraphicsDropShadowEffect(ui.mainToolBar);
	eff->setOffset(0, 0);
	eff->setColor(QColor(0, 0, 0, 90));
	eff->setBlurRadius(10);
	ui.mainToolBar->setGraphicsEffect(eff);
}

void SvgEditor::initRightSettingBar()
{
	return;
}

void SvgEditor::showSvgFileItem(const QString& file)
{
	if (!QFile::exists(file))
    {
		return;
    }

    QScopedPointer<QGraphicsSvgItem> svgItem(new QGraphicsSvgItem(file));
    if (!svgItem->renderer()->isValid())
    {
        return;
    }

    m_SvgView->scene()->clear();
    m_SvgView->resetTransform();

    m_svgItem = svgItem.take();
    //m_svgItem->setFlags(QGraphicsItem::ItemClipsToShape);
    //m_svgItem->setCacheMode(QGraphicsItem::NoCache);
    m_svgItem->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

    m_SvgView->scene()->addItem(m_svgItem);
    m_SvgView->show();
}

void SvgEditor::CreateSvgView()
{
    if (!m_SvgView)
	{
        m_SvgView = new SvgView(new SvgScene(), ui.svgWidget);
        m_SvgView->scene()->setSceneRect(0, 0, ui.svgWidget->width(), ui.svgWidget->height());
        m_SvgView->scene()->setParent(m_SvgView);
	}
    QGraphicsScene* scene = m_SvgView->scene();
	scene->clear();
	scene->setBackgroundBrush(QBrush(QColor(Qt::white)));
    m_SvgView->setEnabled(true);
    m_SvgView->setFixedSize(ui.svgWidget->width(), ui.svgWidget->height());
    ui.svgWidth->setText(QString::number(ui.svgWidget->width()));
    ui.svgHeight->setText(QString::number(ui.svgWidget->height()));
    m_SvgView->show();
}

void SvgEditor::resetToCenter(QWidget* w)
{
    //QPoint point = w->mapToParent(QPoint(w->x(), w->y()));
	QWidget* parent = w->parentWidget();
	int x = parent->width() / 2 - w->width() / 2;
	int y = parent->height() / 2 - w->height() / 2;
	w->move(x, y);
}

void SvgEditor::onNewFileTriggered()
{
    CreateSvgView();
}

void SvgEditor::onActionLineTriggered()
{
    if (m_SvgView)
    {
        m_SvgView->setDrawType(SelectType::LINE);
    }
}

void SvgEditor::onActionRectTriggered()
{
    if (m_SvgView)
    {
        m_SvgView->setDrawType(SelectType::RECTANGLE);
    }
}

void SvgEditor::onActionSelectTriggered()
{
    if(m_SvgView)
    {
        m_SvgView->setDrawType(SelectType::SELECT);
    }
}

void SvgEditor::onActionCurveTriggered()
{
    if (m_SvgView)
    {
        m_SvgView->setDrawType(SelectType::CURVE);
    }
}

void SvgEditor::onActionTextTriggered()
{
    if (m_SvgView)
    {
        m_SvgView->setDrawType(SelectType::TEXT);
    }
}

void SvgEditor::onActionHexagonTriggered()
{
    if (m_SvgView)
    {
        m_SvgView->setDrawType(SelectType::HEXAGON);
    }
}

void SvgEditor::onActionCircleTriggered()
{
    if (m_SvgView)
    {
        m_SvgView->setDrawType(SelectType::CIRCLE);
    }
}

void SvgEditor::onSvgWidthTextEdited(QString val)
{
    if (m_SvgView)
	{
        m_SvgView->setFixedWidth(val.toInt());
        resetToCenter(m_SvgView);
	}
}

void SvgEditor::onSvgHeightTextEdited(QString val)
{
    if (m_SvgView)
	{
        m_SvgView->setFixedHeight(val.toInt());
        resetToCenter(m_SvgView);
	}
}

void SvgEditor::onScaleSvgValueChanged(int scaleRate)
{
    qDebug()<<"SvgEditor::onScaleSvgValueChanged scaleRate:"<<scaleRate;
    if (m_SvgView)
	{
        m_SvgView->scale(scaleRate / 10.0, scaleRate / 10.0);
	}
}

void SvgEditor::onScaleSvgValueReleased()
{
    ui.scaleSvgSlider->setSliderPosition(10);
}

void SvgEditor::onChangeSvgBgClicked()
{
    if (m_SvgView)
	{
		QColor color = QColorDialog::getColor(Qt::white, this, "选择画布背景色");
        m_SvgView->scene()->setBackgroundBrush(QBrush(color));
        QPalette palette(color);
        ui.changeSvgBgButton->setPalette(palette);
	}
}

void SvgEditor::onFillColorButtonClicked()
{
    m_fillColor = QColorDialog::getColor(Qt::white, this, "选择填充颜色");
    QPalette palette(m_fillColor);
    ui.fillColorButton->setPalette(palette);
}

void SvgEditor::initMainWindow()
{
	QBrush brush(QColor(205, 201, 201));
    QPalette palette;
    palette.setBrush(QPalette::ColorRole::Window, brush);
    setPalette(palette);
    initSvgView();
	initLeftToolBar();
	initRightSettingBar();
}
