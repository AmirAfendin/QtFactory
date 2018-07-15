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
    if (m_structBuilder.build(TEMPLATE_FILE_STRUCT_H, RESULT_FILE_STRUCT_H))
        qDebug() << tr("Structure builded");
    else
        qDebug() << tr("Failed to build struct");
    generateStruct();
}
