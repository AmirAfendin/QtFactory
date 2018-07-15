#ifndef MEMBERMODEL_H
#define MEMBERMODEL_H

#include <QAbstractListModel>

class MemberModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum StructRoles {
        Member = Qt::UserRole
    };

    MemberModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    QStringList getMemberList();

public slots:
    void addMember();
    void removeMember(int index);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QStringList m_members;
};

#endif // MEMBERMODEL_H
