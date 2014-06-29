#ifndef DOTTEMPLATE_H
#define DOTTEMPLATE_H

#include "abstracttemplatemodel.h"

class QObject;
class QPainter;

class DotTemplate : public AbstractTemplateModel
{
    Q_OBJECT

public:
    DotTemplate(QObject *parent = nullptr);

    double pagePenWidth() const;
    double dotSize() const;

    void setPagePenColor(QColor color);
    QColor pagePenColor() const;

public slots:
    void setPagePenWidth(double width);
    void setDotSize(double size);

protected:
    virtual void paintPage(QPainter *painter, const QRectF &rect) override;

private:
    double penWidthMM;
    double m_dotSize;
    QPen pagePen;
};

#endif // DOTTEMPLATE_H
