#include <QtWidgets>

#include "abstracttemplatemodel.h"
#include "templateview.h"

AbstractTemplateModel::AbstractTemplateModel(QObject *parent) :
    QObject(parent)
{
    view = nullptr;
    penWidthMM = 0.25;
    cutHerePen.setStyle(Qt::DashLine);
    cutHerePen.setColor(Qt::lightGray);
}

AbstractTemplateModel::~AbstractTemplateModel()
{
}

void AbstractTemplateModel::render(QPainter *painter)
{
    Q_ASSERT(painter != nullptr);

    device = painter->device();
    QMargins paperMargins;
    QMargins pageMargins;

    paperMargins += mm(5);
    pageMargins += mm(5);

    QRect rect = QRect(0, 0, width(), height()).marginsRemoved(paperMargins);
    const QPoint center = rect.center();

    cutHerePen.setWidthF(mm(penWidthMM));
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(cutHerePen);
    painter->setBrush(Qt::NoBrush);
    painter->translate(cutPenWidth() / 2, cutPenWidth() / 2);
    // Horizontal and vertical center line
    painter->drawLine(center.x(), rect.y(),
                      center.x(), rect.y() + rect.height() - cutPenWidth());
    painter->drawLine(rect.x(), center.y(),
                      rect.x() + rect.width() - cutPenWidth(), center.y());
    // Printable area
    painter->drawRect(rect.x(), rect.y(),
                      rect.width() - cutPenWidth(), rect.height() - cutPenWidth());

    QRect page = QRect(rect.topLeft(), center);
    for (int y = rect.y(); y < rect.height() - 1; y += page.height())
    {
        for (int x = rect.x(); x < rect.width() - 1; x += page.width())
        {
            page.moveTo(x, y);

            painter->save();
            paintPage(painter, page.marginsRemoved(pageMargins));
            painter->restore();
        }
    }

    painter->restore();
}

void AbstractTemplateModel::setCutPenWidth(double width)
{
    penWidthMM = width;
    update();
}

double AbstractTemplateModel::cutPenWidth() const
{
    return penWidthMM;
}

void AbstractTemplateModel::setCutPenColor(QColor color)
{
    cutHerePen.setColor(color);
    update();
}

QColor AbstractTemplateModel::cutPenColor() const
{
    return cutHerePen.color();
}

void AbstractTemplateModel::setView(TemplateView *v)
{
    view = v;
}

// Private members
int AbstractTemplateModel::width() const
{
    return device->width();
}

int AbstractTemplateModel::height() const
{
    return device->height();
}

int AbstractTemplateModel::dpi() const
{
    return device->logicalDpiX();
}

int AbstractTemplateModel::mm(double m) const
{
    return m * (dpi() / 25.4);
}

void AbstractTemplateModel::update() const
{
    if(view)
    {
        view->update();
    }
}
