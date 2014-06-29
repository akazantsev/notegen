#include <QtWidgets>

#include "doubleadjuster.h"
#include "doublespinbox.h"

DoubleAdjuster::DoubleAdjuster(QWidget *parent) :
    QWidget(parent)
{
    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);

    spinBox = new DoubleSpinBox;
    spinBox->setRange(0, 100);

    connect(slider, SIGNAL(valueChanged(int)),
            spinBox, SLOT(setPercentage(int)));
    connect(spinBox, SIGNAL(percentageChanged(int)),
            slider, SLOT(setValue(int)));
    connect(spinBox, SIGNAL(valueChanged(double)),
            this, SIGNAL(valueChanged(double)));

    auto mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(slider);
    mainLayout->addWidget(spinBox);
    setLayout(mainLayout);

    setRange(0.0, 1.0);
    setValue(0.28);
}

void DoubleAdjuster::setRange(double min, double max)
{
    spinBox->setRange(min, max);
}

void DoubleAdjuster::setValue(double value)
{
    spinBox->setValue(value);
}

void DoubleAdjuster::setSuffix(const QString &suffix)
{
    spinBox->setSuffix(suffix);
}

