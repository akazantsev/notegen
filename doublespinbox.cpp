#include "doublespinbox.h"

DoubleSpinBox::DoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent), m_percentage(0)
{
    setSingleStep(0.25);

    connect(this, SIGNAL(valueChanged(double)),
            SLOT(convertToPercentage(double)));
}

void DoubleSpinBox::setPercentage(int percentage)
{
    if (m_percentage == percentage)
        return;

    m_percentage = percentage;
    setValue((maximum() - minimum()) * (m_percentage / 100.0) + minimum());
}

void DoubleSpinBox::convertToPercentage(double value)
{
    const int newPercentage = value / (maximum() - minimum()) * 100;

    if (m_percentage == newPercentage)
        return;

    m_percentage = newPercentage;
    emit percentageChanged(m_percentage);
}
