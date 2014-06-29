#include <QtWidgets>

#include "templateview.h"
#include "abstracttemplatemodel.h"

TemplateView::TemplateView(QWidget *parent) :
    QWidget(parent)
{
    model = nullptr;
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize TemplateView::sizeHint() const
{
    return QSize(720, 1024);
}

void TemplateView::setModel(AbstractTemplateModel *m)
{
    Q_ASSERT(m != nullptr);

    model = m;
    model->setView(this);
}

void TemplateView::paintEvent(QPaintEvent *)
{
    Q_ASSERT(model != nullptr);

    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());

    model->render(&painter);
}
