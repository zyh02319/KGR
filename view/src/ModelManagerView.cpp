#include "../ModelManagerView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>

ModelManagerView::ModelManagerView(QWidget *parent)
    : QWidget(parent), currentModelType(0)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 模型类型选择
    QHBoxLayout *typeLayout = new QHBoxLayout;
    modelTypeGroup = new QButtonGroup(this);
    interferenceRadio = new QRadioButton("干扰机模型", this);
    detectionRadio = new QRadioButton("探测模型", this);
    antiJammingRadio = new QRadioButton("抗干扰模型", this);
    targetRadio = new QRadioButton("目标模型", this);
    modelTypeGroup->addButton(interferenceRadio, 0);
    modelTypeGroup->addButton(detectionRadio, 1);
    modelTypeGroup->addButton(antiJammingRadio, 2);
    modelTypeGroup->addButton(targetRadio, 3);
    interferenceRadio->setChecked(true);
    typeLayout->addWidget(interferenceRadio);
    typeLayout->addWidget(detectionRadio);
    typeLayout->addWidget(antiJammingRadio);
    typeLayout->addWidget(targetRadio);
    mainLayout->addLayout(typeLayout);

    // 新建按钮
    createButton = new QPushButton("新建", this);
    connect(createButton, &QPushButton::clicked, this, &ModelManagerView::onCreateModel);
    mainLayout->addWidget(createButton, 0, Qt::AlignLeft);

    // 模型列表
    modelTable = new QTableWidget(this);
    modelTable->setColumnCount(4);
    QStringList headers;
    headers << "模型名称" << "编辑" << "删除" << "查看";
    modelTable->setHorizontalHeaderLabels(headers);
    modelTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    modelTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(modelTable);

    connect(modelTypeGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &ModelManagerView::onModelTypeChanged);

    loadModels();
}

void ModelManagerView::onModelTypeChanged(int id) {
    currentModelType = id;
    loadModels();
}

void ModelManagerView::onCreateModel() {
    // TODO: 弹出新建模型对话框，根据 currentModelType 创建不同类型模型
    QMessageBox::information(this, "新建", "新建当前类型模型");
}

void ModelManagerView::onEditModel(int row) {
    // TODO: 编辑模型逻辑
    QMessageBox::information(this, "编辑", QString("编辑第%1行模型").arg(row));
}

void ModelManagerView::onDeleteModel(int row) {
    // TODO: 删除模型逻辑
    QMessageBox::information(this, "删除", QString("删除第%1行模型").arg(row));
}

void ModelManagerView::onViewModel(int row) {
    // TODO: 查看模型逻辑
    QMessageBox::information(this, "查看", QString("查看第%1行模型").arg(row));
}

void ModelManagerView::loadModels() {
    // TODO: 从数据库加载 currentModelType 类型的所有模型
    // 这里只做演示，实际应从数据库查询
    modelTable->setRowCount(3);
    for (int i = 0; i < 3; ++i) {
        modelTable->setItem(i, 0, new QTableWidgetItem(QString("模型%1").arg(i+1)));
        QPushButton *editBtn = new QPushButton("编辑");
        QPushButton *delBtn = new QPushButton("删除");
        QPushButton *viewBtn = new QPushButton("查看");
        modelTable->setCellWidget(i, 1, editBtn);
        modelTable->setCellWidget(i, 2, delBtn);
        modelTable->setCellWidget(i, 3, viewBtn);
        connect(editBtn, &QPushButton::clicked, [this, i]() { onEditModel(i); });
        connect(delBtn, &QPushButton::clicked, [this, i]() { onDeleteModel(i); });
        connect(viewBtn, &QPushButton::clicked, [this, i]() { onViewModel(i); });
    }
} 