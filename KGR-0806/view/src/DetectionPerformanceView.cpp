#include "../DetectionPerformanceView.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>

DetectionPerformanceView::DetectionPerformanceView(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 评估条件
    QGroupBox *conditionBox = new QGroupBox("评估条件", this);
    conditionBox->setLayout(new QVBoxLayout);
    conditionBox->layout()->addWidget(new QLabel("无干扰、干扰、抗干扰三种条件下的探测效能"));

    // 评估方式
    QGroupBox *modeBox = new QGroupBox("评估方式", this);
    modeBox->setLayout(new QVBoxLayout);
    modeBox->layout()->addWidget(new QLabel("单机评估、编队评估"));

    // 评估指标
    QGroupBox *indexBox = new QGroupBox("评估指标", this);
    indexBox->setLayout(new QVBoxLayout);
    indexBox->layout()->addWidget(new QLabel("探测距离、目标航迹连续性、探测中断原因等"));

    mainLayout->addWidget(conditionBox);
    mainLayout->addWidget(modeBox);
    mainLayout->addWidget(indexBox);

    setLayout(mainLayout);
} 