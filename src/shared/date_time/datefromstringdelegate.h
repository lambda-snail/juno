#pragma once

#include <QSettings>
#include <QStyledItemDelegate>

namespace LambdaSnail::Juno::shared
{
    /**
     * Adds a date edit widget to columns that store dates as strings. This ensures that there will always be a valid date
     * in the column. Useful for sql models hat don't work with a model class.
     */
    class LSDateFromStringDelegate : public QStyledItemDelegate
    {
        Q_OBJECT

    public:
        LSDateFromStringDelegate(QSettings* settings, QObject* parent = nullptr);

        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
        void setEditorData(QWidget *editor, const QModelIndex &index) const override;
        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
        void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    private:
        QSettings* m_settings;
    };
}
