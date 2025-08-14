#include "DetectionPerformanceView.h"
#include "ModelSelectionDialog.h"
#include "SingleEvaluationController.h"
#include <QMessageBox>
#include <iostream>
#include <cmath>

// 在包含头文件后声明元类型
// Q_DECLARE_METATYPE(RadarModel)
// Q_DECLARE_METATYPE(JammerModel)
// Q_DECLARE_METATYPE(TargetModel)
// Q_DECLARE_METATYPE(RcsData)

DetectionPerformanceView::DetectionPerformanceView(QWidget *parent)
    : QWidget(parent), radarDialog(nullptr), jammerDialog(nullptr), targetDialog(nullptr),
      currentRadar(nullptr), currentJammer(nullptr), currentTarget(nullptr), currentRcs(nullptr)
{
    setupUI();
}

DetectionPerformanceView::~DetectionPerformanceView() {
    delete radarDialog;
    delete jammerDialog;
    delete targetDialog;
    delete currentRadar;
    delete currentJammer;
    delete currentTarget;
    delete currentRcs;
}

void DetectionPerformanceView::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // 创建标签页
    tabWidget = new QTabWidget(this);
    singleEvaluationTab = new QWidget();
    
    // 单机评估页面布局
    QVBoxLayout *singleLayout = new QVBoxLayout(singleEvaluationTab);
    
    // 条件选择
    QGroupBox *conditionGroup = new QGroupBox("评估条件", this);
    QHBoxLayout *conditionLayout = new QHBoxLayout;
    conditionComboBox = new QComboBox(this);
    conditionComboBox->addItem("无干扰");
    conditionComboBox->addItem("有干扰");
    conditionComboBox->addItem("抗干扰");
    conditionLayout->addWidget(new QLabel("干扰情况:"));
    conditionLayout->addWidget(conditionComboBox);
    conditionGroup->setLayout(conditionLayout);
    
    // 模型选择
    QGroupBox *modelGroup = new QGroupBox("模型选择", this);
    QGridLayout *modelLayout = new QGridLayout;
    
    selectRadarButton = new QPushButton("选择雷达模型", this);
    selectJammerButton = new QPushButton("选择干扰模型", this);
    selectTargetButton = new QPushButton("选择目标模型", this);
    evaluateButton = new QPushButton("评估", this);
    
    radarLabel = new QLabel("未选择", this);
    jammerLabel = new QLabel("未选择", this);
    targetLabel = new QLabel("未选择", this);
    rcsLabel = new QLabel("未选择RCS", this);
    
    QPushButton *radarDetailButton = new QPushButton("查看", this);
    QPushButton *jammerDetailButton = new QPushButton("查看", this);
    QPushButton *targetDetailButton = new QPushButton("查看", this);
    
    modelLayout->addWidget(new QLabel("雷达模型:"), 0, 0);
    modelLayout->addWidget(radarLabel, 0, 1);
    modelLayout->addWidget(selectRadarButton, 0, 2);
    modelLayout->addWidget(radarDetailButton, 0, 3);
    
    modelLayout->addWidget(new QLabel("干扰模型:"), 1, 0);
    modelLayout->addWidget(jammerLabel, 1, 1);
    modelLayout->addWidget(selectJammerButton, 1, 2);
    modelLayout->addWidget(jammerDetailButton, 1, 3);
    
    modelLayout->addWidget(new QLabel("目标模型:"), 2, 0);
    modelLayout->addWidget(targetLabel, 2, 1);
    modelLayout->addWidget(rcsLabel, 2, 2);
    modelLayout->addWidget(selectTargetButton, 2, 3);
    modelLayout->addWidget(targetDetailButton, 2, 4);
    
    modelLayout->addWidget(evaluateButton, 3, 0, 1, 5);
    modelGroup->setLayout(modelLayout);
    
    // 结果展示
    QGroupBox *resultGroup = new QGroupBox("评估结果", this);
    QVBoxLayout *resultLayout = new QVBoxLayout;
    resultLabel = new QLabel("结果将显示在这里", this);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLayout->addWidget(resultLabel);
    resultGroup->setLayout(resultLayout);
    
    // 添加到单机评估页
    singleLayout->addWidget(conditionGroup);
    singleLayout->addWidget(modelGroup);
    singleLayout->addWidget(resultGroup);
    
    // 添加标签页
    tabWidget->addTab(singleEvaluationTab, "单机评估");
    tabWidget->addTab(new QWidget(), "编队评估"); // 编队评估暂未实现
    
    mainLayout->addWidget(tabWidget);
    
    // 连接信号槽
    connect(conditionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DetectionPerformanceView::onConditionChanged);
    connect(selectRadarButton, &QPushButton::clicked, this, &DetectionPerformanceView::onSelectRadar);
    connect(selectJammerButton, &QPushButton::clicked, this, &DetectionPerformanceView::onSelectJammer);
    connect(selectTargetButton, &QPushButton::clicked, this, &DetectionPerformanceView::onSelectTarget);
    connect(evaluateButton, &QPushButton::clicked, this, &DetectionPerformanceView::onEvaluate);
    connect(radarDetailButton, &QPushButton::clicked, this, &DetectionPerformanceView::showRadarDetails);
    connect(jammerDetailButton, &QPushButton::clicked, this, &DetectionPerformanceView::showJammerDetails);
    connect(targetDetailButton, &QPushButton::clicked, this, &DetectionPerformanceView::showTargetDetails);
    
    // 初始化状态
    onConditionChanged(0);
}

void DetectionPerformanceView::onConditionChanged(int index) {
    // 无干扰时禁用干扰模型选择
    selectJammerButton->setEnabled(index != 0);
    jammerLabel->setEnabled(index != 0);
    
    if (index == 0) {
        delete currentJammer;
        currentJammer = nullptr;
        jammerLabel->setText("未选择");
    }
    
    updateModelDisplay();
}

void DetectionPerformanceView::onSelectRadar() {
    if (!radarDialog) {
        radarDialog = new ModelSelectionDialog(this);
        radarDialog->setModels(SingleEvaluationController::getAllRadarModels());
        connect(radarDialog, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
            // 删除旧对象，创建新对象
            delete currentRadar;
            currentRadar = new RadarModel(model.value<RadarModel>());
            updateModelDisplay();
        });
    }
    radarDialog->show();
}

void DetectionPerformanceView::onSelectJammer() {
    if (!jammerDialog) {
        jammerDialog = new ModelSelectionDialog(this);
        jammerDialog->setModels(SingleEvaluationController::getAllJammerModels());
        connect(jammerDialog, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
            delete currentJammer;
            currentJammer = new JammerModel(model.value<JammerModel>());
            updateModelDisplay();
        });
    }
    jammerDialog->show();
}

// void DetectionPerformanceView::onSelectTarget() {
//     if (!targetDialog) {
//         targetDialog = new ModelSelectionDialog(this);
//         targetDialog->setModels(SingleEvaluationController::getAllTargetModels(), true);
//         connect(targetDialog, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
//             delete currentTarget;
//             currentTarget = new TargetModel(model.value<TargetModel>());
            
//             // 清空之前的RCS选择
//             delete currentRcs;
//             currentRcs = nullptr;
//             rcsLabel->setText("未选择RCS");
            
//             updateModelDisplay();
//         });
//         connect(targetDialog, &ModelSelectionDialog::rcsSelected, [this](const RcsData& rcs) {
//             delete currentRcs;
//             currentRcs = new RcsData(rcs);
//             rcsLabel->setText(QString("方位角: %1°, 俯仰角: %2°, RCS: %3 m²")
//                               .arg(rcs.azimuth).arg(rcs.elevation).arg(rcs.rcs_value));
//         });
//     }
//     targetDialog->show();
// }
// 修改 onSelectTarget 函数
void DetectionPerformanceView::onSelectTarget() {
    if (!targetDialog) {
        targetDialog = new ModelSelectionDialog(this);
        targetDialog->setModels(SingleEvaluationController::getAllTargetModels(), true);
        connect(targetDialog, &ModelSelectionDialog::modelSelected, [this](const QVariant& model) {
            // 更新目标模型
            delete currentTarget;
            currentTarget = new TargetModel(model.value<TargetModel>());
            
            // 清空之前的RCS选择
            delete currentRcs;
            currentRcs = nullptr;
            rcsLabel->setText("未选择RCS");
            
            updateModelDisplay();
        });
        connect(targetDialog, &ModelSelectionDialog::rcsSelected, [this](const RcsData& rcs) {
            // 更新RCS数据
            delete currentRcs;
            currentRcs = new RcsData(rcs);
            rcsLabel->setText(QString("方位角: %1°, 俯仰角: %2°, RCS: %3 m²")
                              .arg(rcs.azimuth).arg(rcs.elevation).arg(rcs.rcs_value));
        });
    }
    targetDialog->show();
}

void DetectionPerformanceView::onEvaluate() {
    // 验证输入
    if (!currentRadar) {
        QMessageBox::warning(this, "错误", "请选择雷达模型");
        return;
    }
    if (conditionComboBox->currentIndex() != 0 && !currentJammer) {
        QMessageBox::warning(this, "错误", "请选择干扰模型");
        return;
    }
    if (!currentTarget || !currentRcs) {
        QMessageBox::warning(this, "错误", "请选择目标模型和RCS数据");
        return;
    }
    
    // 计算探测距离
    // try {
    //     JammerModel defaultJammer; // 默认干扰模型对象
    //     if (conditionComboBox->currentIndex() == 0) {
    //         // 无干扰时，使用一个默认的干扰模型对象，但实际上不会用到干扰模型数据
    //         defaultJammer = JammerModel();
    //     }
        
    //     double distance = SingleEvaluationController::calculateDistance(
    //         conditionComboBox->currentIndex(),
    //         *currentRadar,
    //         (conditionComboBox->currentIndex() == 0) ? defaultJammer : *currentJammer,
    //         *currentRcs
    //     );
        
    //     resultLabel->setText(QString("探测距离: %1 米").arg(distance, 0, 'f', 2));
    // } catch (const std::exception& e) {
    //     resultLabel->setText("计算失败: " + QString(e.what()));
    // } catch (...) {
    //     resultLabel->setText("计算失败: 未知错误");
    // }
    // 计算距离
    double distance = 0.0;
    if (currentTarget && currentRadar) {
        distance = calculateSpatialDistance(
            currentRadar->longitude, currentRadar->latitude, currentRadar->altitude,
            currentTarget->longitude, currentTarget->latitude, currentTarget->altitude
        );
    }
     // 计算探测距离
    try {
        JammerModel defaultJammer;
        if (conditionComboBox->currentIndex() == 0) {
            defaultJammer = JammerModel();
        }
        
        // 调用修改后的函数，传入计算的距离
        double resultDistance = SingleEvaluationController::calculateDistance(
            conditionComboBox->currentIndex(),
            *currentRadar,
            (conditionComboBox->currentIndex() == 0) ? defaultJammer : *currentJammer,
            *currentRcs,
            distance  // 添加距离参数
        );
        
        resultLabel->setText(QString("探测距离: %1 米").arg(resultDistance, 0, 'f', 2));
    } catch (const std::exception& e) {
        // ... 错误处理不变 ...
        resultLabel->setText("计算失败: " + QString(e.what()));
    }
}

void DetectionPerformanceView::updateModelDisplay() {
    radarLabel->setText(currentRadar ? QString::fromStdString(currentRadar->name) : "未选择");
    jammerLabel->setText(currentJammer ? QString::fromStdString(currentJammer->name) : "未选择");
    targetLabel->setText(currentTarget ? QString::fromStdString(currentTarget->name) : "未选择");
}

void DetectionPerformanceView::showRadarDetails() {
    if (currentRadar) {
        QString details = QString("雷达模型: %1\n"
                                 "波长: %2 m\n"
                                 "发射功率: %3 KW\n"
                                 "信号带宽: %4 MHz\n"
                                 "天线增益: %5 dB\n"
                                 "系统损耗因子: %6\n"
                                 "位置: (%7, %8, %9)")
                         .arg(QString::fromStdString(currentRadar->name))
                         .arg(currentRadar->wavelength)
                         .arg(currentRadar->power)
                         .arg(currentRadar->bandwidth)
                         .arg(currentRadar->gain)
                         .arg(currentRadar->loss_factor)
                         .arg(currentRadar->longitude)
                         .arg(currentRadar->latitude)
                         .arg(currentRadar->altitude);
        QMessageBox::information(this, "雷达模型详情", details);
    }
}

void DetectionPerformanceView::showJammerDetails() {
    if (currentJammer) {
        QString details = QString("干扰机模型: %1\n"
                                 "干扰样式: %2\n"
                                 "干扰功率: %3 W\n"
                                 "干扰带宽: %4 MHz\n"
                                 "干扰增益: %5 dB\n"
                                 "位置: (%6, %7, %8)")
                         .arg(QString::fromStdString(currentJammer->name))
                         .arg(QString::fromStdString(currentJammer->jamming_type))
                         .arg(currentJammer->power)
                         .arg(currentJammer->bandwidth)
                         .arg(currentJammer->gain)
                         .arg(currentJammer->longitude)
                         .arg(currentJammer->latitude)
                         .arg(currentJammer->altitude);
        QMessageBox::information(this, "干扰机模型详情", details);
    }
}

void DetectionPerformanceView::showTargetDetails() {
    if (currentTarget) {
        QString details = QString("目标模型: %1\n"
                                 "目标类型: %2\n"
                                 "位置: (%3, %4, %5)")
                         .arg(QString::fromStdString(currentTarget->name))
                         .arg(QString::fromStdString(currentTarget->target_type))
                         .arg(currentTarget->longitude)
                         .arg(currentTarget->latitude)
                         .arg(currentTarget->altitude);
                         
        
        if (currentRcs) {
            details += QString("\n当前RCS数据:\n"
                              "方位角: %1°\n"
                              "俯仰角: %2°\n"
                              "RCS值: %3 m²")
                      .arg(currentRcs->azimuth)
                      .arg(currentRcs->elevation)
                      .arg(currentRcs->rcs_value);
        } else {
            details += "\n未选择RCS数据";
        }
        // 如果雷达模型已选择，显示距离
        if (currentRadar) {
            double distance = calculateSpatialDistance(
                currentRadar->longitude, currentRadar->latitude, currentRadar->altitude,
                currentTarget->longitude, currentTarget->latitude, currentTarget->altitude
            );
            details += QString("\n与雷达距离: %1 米").arg(distance, 0, 'f', 2);
        }
        
        QMessageBox::information(this, "目标模型详情", details);
    }
}

double DetectionPerformanceView::calculateSpatialDistance(
    double lon1, double lat1, double alt1, 
    double lon2, double lat2, double alt2) 
{
    // 地球半径（米）
    const double R = 6371000.0;
    
    // 将经纬度转换为弧度
    double lat1Rad = lat1 * M_PI / 180.0;
    double lon1Rad = lon1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double lon2Rad = lon2 * M_PI / 180.0;
    
    // 计算差值
    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;
    
    // Haversine公式计算球面距离
    double a = sin(dLat/2) * sin(dLat/2) +
               cos(lat1Rad) * cos(lat2Rad) * 
               sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double distance = R * c;
    
    // 考虑高度差（直角坐标）
    double dAlt = alt2 - alt1;
    return sqrt(distance * distance + dAlt * dAlt);
}