#pragma once
#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QTableWidget>

class ModelManagerView : public QWidget {
    Q_OBJECT
public:
    explicit ModelManagerView(QWidget *parent = nullptr);

private slots:
    void onModelTypeChanged(int id);
    void onCreateModel();
    void onEditModel(int row);
    void onDeleteModel(int row);
    void onViewModel(int row);

private:
    QButtonGroup *modelTypeGroup;
    QRadioButton *interferenceRadio;
    QRadioButton *detectionRadio;
    QRadioButton *antiJammingRadio;
    QRadioButton *targetRadio;
    QPushButton *createButton;
    QTableWidget *modelTable;
    void loadModels();
    void setupTable();
    int currentModelType; // 0:干扰机 1:探测 2:抗干扰 3:目标
}; 