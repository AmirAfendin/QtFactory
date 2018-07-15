#include "membermodel.h"

MemberModel::MemberModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_members << "QString name" << "QString surname" << "QString steet" << "QDate birthDay" << "int amoutOfCash" << "QUrl socialNetworkLink" << "bool isMarried" << "";
}

int MemberModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_members.count();
}

QVariant MemberModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if (row < 0 || row >= m_members.count())
        return QVariant();

    switch (role) {
    case Member:
        return m_members.at(row);
    }

    return QVariant();
}

bool MemberModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    if (row < 0 || row >= m_members.count())
        return false;

    switch (role) {
    case Member:
        m_members[row] = value.toString();
        break;
    default:
        return false;
    }

    emit dataChanged(createIndex(row, 0, nullptr), createIndex(row, 0, nullptr));
    return true;
}

QStringList MemberModel::getMemberList()
{
    QStringList memberList = m_members;
    memberList.removeLast();
    return memberList;
}

void MemberModel::addMember()
{
    beginInsertRows(QModelIndex(), m_members.count(), m_members.count());
    m_members << "";
    endInsertRows();
}

void MemberModel::removeMember(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_members.removeAt(index);
    endRemoveRows();
}

QHash<int, QByteArray> MemberModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Member] = "member";
    return roles;
}
