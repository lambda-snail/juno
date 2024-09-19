#include "relationalproxydelegate.h"

#include "categories/categorymodel.h"
#include "expenses/categoryfiltermodel.h"

namespace LambdaSnail::Juno::delegates
{
    LSRelationalProxyDelegate::LSRelationalProxyDelegate(QObject *parent) : QSqlRelationalDelegate(parent) { }

    QWidget* LSRelationalProxyDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        if(QAbstractProxyModel const* proxy = qobject_cast<QAbstractProxyModel const*>(index.model()))
        {
            QModelIndex mappedIndex = proxy->mapToSource(index);
            return QSqlRelationalDelegate::createEditor(aParent, option, mappedIndex);
        }

        return QSqlRelationalDelegate::createEditor(aParent, option, index);

    }

    void LSRelationalProxyDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex &index) const
    {
        if(auto const* proxy = qobject_cast<QAbstractProxyModel const*>(index.model()))
        {
            auto* underlyingModel = proxy->sourceModel();
            auto const mappedIndex = proxy->mapToSource(index);
            setModelData(editor, underlyingModel, mappedIndex);
        }

        QSqlRelationalDelegate::setModelData(editor, model, index);
    }

    void LSRelationalProxyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        if(QAbstractProxyModel const* proxy = qobject_cast<QAbstractProxyModel const*>(index.model()))
        {
            QModelIndex mappedIndex = proxy->mapToSource(index);
            QSqlRelationalDelegate::setEditorData(editor, mappedIndex);
            return;
        }

        QSqlRelationalDelegate::setEditorData(editor, index);
    }
}
