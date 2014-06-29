#ifndef ABSTRACTTEMPLATEMODEL_H
#define ABSTRACTTEMPLATEMODEL_H

#include <QtCore>
#include <QPen>

class QPainter;
class QPaintDevice;
class TemplateView;

class AbstractTemplateModel : public QObject
{
    Q_OBJECT

public:
    AbstractTemplateModel(QObject *parent = nullptr);
    virtual ~AbstractTemplateModel();

    void render(QPainter *painter);

    double cutPenWidth() const;

    void setCutPenColor(QColor color);
    QColor cutPenColor() const;

    void setView(TemplateView *v);

public slots:
    void setCutPenWidth(double width);

protected:
    int width() const;
    int height() const;
    int dpi() const;
    int mm(double m) const;
    void update() const;

    virtual void paintPage(QPainter *painter, const QRectF &rect) = 0;

private:
    double penWidthMM;
    QPen cutHerePen;
    QPaintDevice *device;
    TemplateView *view;
};

#endif // ABSTRACTTEMPLATEMODEL_H
