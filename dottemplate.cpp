#include <cmath>
using std::fmod;

#include <QtWidgets>

#include "dottemplate.h"

DotTemplate::DotTemplate(QObject *parent) :
    AbstractTemplateModel(parent)
{
    penWidthMM = 0.25;
    m_dotSize = 0.25;
    pagePen.setColor(Qt::lightGray);
}

void DotTemplate::setPagePenWidth(double width)
{
    penWidthMM = width;
    update();
}


double DotTemplate::pagePenWidth() const
{
    return penWidthMM;
}

void DotTemplate::setDotSize(double size)
{
    m_dotSize = size;
    update();
}

double DotTemplate::dotSize() const
{
    return m_dotSize;
}

void DotTemplate::setPagePenColor(QColor color)
{
    pagePen.setColor(color);
    update();
}

QColor DotTemplate::pagePenColor() const
{
    return pagePen.color();
}

void DotTemplate::paintPage(QPainter *painter, const QRectF &rect)
{
    const double step = mm(5);
    const double size = mm(m_dotSize);
    const double shiftX = (fmod(rect.width(), step) + step - size) / 2;
    const double shiftY = (fmod(rect.height(), step) + step - size) / 2;

    pagePen.setWidthF(mm(pagePenWidth()));
    painter->setPen(pagePen);
    painter->drawRect(rect);

    QRect point(0, 0, size, size);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::lightGray);

    const double fillWidth = rect.x() + rect.width() - shiftX;
    const double fillHeight = rect.y() + rect.height() - shiftY;
    for (double y = rect.y() + shiftY; y < fillHeight; y += step)
    {
        for (double x = rect.x() + shiftX; x < fillWidth; x += step)
        {
            point.moveTo(x, y);
            painter->drawEllipse(point);
        }
    }
}
