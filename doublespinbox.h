#ifndef DOUBLESPINBOX_H
#define DOUBLESPINBOX_H

#include <QDoubleSpinBox>

class DoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit DoubleSpinBox(QWidget *parent = 0);

signals:
    void percentageChanged(int per);

public slots:
    void setPercentage(int per);

private slots:
    void convertToPercentage(double value);

private:
    int m_percentage;
};

#endif // DOUBLESPINBOX_H
