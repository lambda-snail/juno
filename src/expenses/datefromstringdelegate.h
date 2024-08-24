#pragma once

#include <QStyledItemDelegate>

namespace LambdaSnail::Juno::expenses
{
    /**
     * Adds a date edit widget to columns that store dates as strings. This ensures that there will always be a valid date
     * in the column. Useful for sql models hat don't work with a model class.
     */
    class DateFromStringDelegate : public QStyledItemDelegate
    {
        Q_OBJECT

    public:
        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
        void setEditorData(QWidget *editor, const QModelIndex &index) const override;
        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
        void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    };
}
