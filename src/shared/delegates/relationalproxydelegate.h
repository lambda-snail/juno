#pragma once
#include <QSqlRelationalDelegate>

namespace LambdaSnail::Juno::delegates
{
    /**
     * Subclass of QSqlRelationalDelegate that can be used with a proxy model.
     */
    class LSRelationalProxyDelegate : public QSqlRelationalDelegate
    {
    public:
        explicit LSRelationalProxyDelegate(QObject* parent);

        QWidget *createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
        void setEditorData(QWidget *editor, const QModelIndex &index) const;
    };
}
