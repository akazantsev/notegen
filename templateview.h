#ifndef TEMPLATEVIEW_H
#define TEMPLATEVIEW_H

#include <QWidget>

class AbstractTemplateModel;

class TemplateView : public QWidget
{
    Q_OBJECT

public:
    TemplateView(QWidget *parent = 0);

    QSize sizeHint() const;
    void setModel(AbstractTemplateModel *m);

protected:
    void paintEvent(QPaintEvent * event);

private:
    AbstractTemplateModel *model;
};

#endif // TEMPLATEVIEW_H
