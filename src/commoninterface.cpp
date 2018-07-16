#include "commoninterface.h"
#include <QFile>
#include <QDebug>

CommonInterface::CommonInterface(QObject *parent) : QObject(parent)
{
    m_memberModel = new MemberModel(this);
    m_structName = "";
    m_structName = "Interval";
}

void CommonInterface::buildSources()
{
    bool success = m_structBuilder.build(TEMPLATE_FILE_STRUCT_H, RESULT_FILE_STRUCT_H,
                                         m_structName, m_memberModel->getMemberList());
    if (success) {
        qDebug() << tr("Structure builded");
    } else {
        qDebug() << tr("Failed to build struct");
        return;
    }

    success = m_modelBuilder.build(TEMPLATE_FILE_MODEL_H, RESULT_FILE_MODEL_H);
}
