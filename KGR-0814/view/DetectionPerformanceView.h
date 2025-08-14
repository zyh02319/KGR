#pragma once
#include <QWidget>
#include <QTabWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "SingleEvaluationController.h"

class ModelSelectionDialog;

class DetectionPerformanceView : public QWidget {
    Q_OBJECT
public:
    explicit DetectionPerformanceView(QWidget *parent = nullptr);
    ~DetectionPerformanceView();

private slots:
    void onConditionChanged(int index);
    void onSelectRadar();
    void onSelectJammer();
    void onSelectTarget();
    void onEvaluate();
    void showRadarDetails();
    void showJammerDetails();
    void showTargetDetails();

private:
    void setupUI();
    void updateModelDisplay();

    QTabWidget *tabWidget;
    QWidget *singleEvaluationTab;
    
    // 单机评估控件
    QComboBox *conditionComboBox;
    QPushButton *selectRadarButton;
    QPushButton *selectJammerButton;
    QPushButton *selectTargetButton;
    QPushButton *evaluateButton;
    QLabel *radarLabel;
    QLabel *jammerLabel;
    QLabel *targetLabel;
    QLabel *rcsLabel;
    QLabel *resultLabel;
    
    // 当前选中的模型 - 使用指针替代optional
    RadarModel* currentRadar = nullptr;
    JammerModel* currentJammer = nullptr;
    TargetModel* currentTarget = nullptr;
    RcsData* currentRcs = nullptr;
    
    // 对话框
    ModelSelectionDialog *radarDialog;
    ModelSelectionDialog *jammerDialog;
    ModelSelectionDialog *targetDialog;

     // 添加距离计算函数
    double calculateSpatialDistance(
        double lon1, double lat1, double alt1, 
        double lon2, double lat2, double alt2);
};