#include "relationalproxydelegate.h"

#include "categories/categorymodel.h"
#include "expenses/categoryfiltermodel.h"

namespace LambdaSnail::Juno::delegates {
    // template<typename TFunc, typename TRet, typename ...TArgs>
    // TRet callMethod(QModelIndex index, TArgs ...args)
    // {
    //     if(QAbstractProxyModel const* proxy = qobject_cast<QAbstractProxyModel const*>(index.model()))
    //     {
    //         QModelIndex mappedIndex = proxy->mapToSource(index);
    //         return TFunc(args..., mappedIndex);
    //     }
    //
    //     return TFunc(args..., index);
    // }

    LSRelationalProxyDelegate::LSRelationalProxyDelegate(QObject *parent) : QSqlRelationalDelegate(parent) { }

    QWidget* LSRelationalProxyDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        if(QAbstractProxyModel const* proxy = qobject_cast<QAbstractProxyModel const*>(index.model()))
        {
            QModelIndex mappedIndex = proxy->mapToSource(index);
            return QSqlRelationalDelegate::createEditor(aParent, option, mappedIndex);
        }

        //return callMethod<QWidget*(*)(QWidget*,QStyleOptionViewItem&,QModelIndex&), QWidget*>(index, aParent, option);

        return QSqlRelationalDelegate::createEditor(aParent, option, index);

    }

    // https://wiki.qt.io/QSqlRelationalDelegate-subclass-for-QSqlRelationalTableModel
    void LSRelationalProxyDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex &index) const
    {
        if(QAbstractProxyModel const* proxy = qobject_cast<QAbstractProxyModel const*>(index.model()))
        {
            auto* categoryFilterModel = qobject_cast<expenses::LSCategoryFilterModel const*>(proxy);
            auto mappedIndex = categoryFilterModel->mapToSource(index);

            if(auto* sqlModel = qobject_cast<QSqlRelationalTableModel*>(proxy->sourceModel()))
            {
                QSqlTableModel const* relationalModel = sqlModel->relationModel(index.column());
                if(relationalModel)
                {
                    auto const* comboBox = qobject_cast<QComboBox const*>(editor);
                    int currentItem = comboBox->currentIndex();
                    int relatedValueIndex = relationalModel->fieldIndex(sqlModel->relation(index.column()).displayColumn());
                    int relatedIdIndex = relationalModel->fieldIndex(sqlModel->relation(index.column()).indexColumn());

                    auto relatedColumnValue = relationalModel->data(relationalModel->index(currentItem, relatedValueIndex), Qt::DisplayRole);
                    sqlModel->setData(mappedIndex, relatedColumnValue, Qt::DisplayRole);
                    auto relatedColumnId = relationalModel->data(relationalModel->index(currentItem, relatedIdIndex), Qt::EditRole);
                    sqlModel->setData(mappedIndex, relatedColumnId, Qt::EditRole);
                    return;
                }
            }
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
        //callMethod<void(QWidget*,QModelIndex&), void>(index, editor);
    }
}
