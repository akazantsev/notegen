#ifndef DOUBLEADJUSTER_H
#define DOUBLEADJUSTER_H

#include <QWidget>

class QSlider;
class DoubleSpinBox;

class DoubleAdjuster : public QWidget
{
    Q_OBJECT
public:
    explicit DoubleAdjuster(QWidget *parent = 0);

    void setRange(double min, double max);
    void setValue(double value);
    void setSuffix(const QString &suffix);

signals:
    void valueChanged(double value);

private:
    QSlider *slider;
    DoubleSpinBox *spinBox;
};

#endif // DOUBLEADJUSTER_H
