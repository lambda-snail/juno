#pragma once
#include <QLineEdit>
#include <QStyledItemDelegate>

class QAbstractProxyModel;
class QComboBox;

namespace LambdaSnail::Juno::shared
{
    class LSDelegateBase : public QStyledItemDelegate
    {
        Q_OBJECT
    public:
        explicit LSDelegateBase(QObject * object);

        void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    };

    class LSCategoryPickerDelegate : public LSDelegateBase
    {
        Q_OBJECT

    public:
        explicit LSCategoryPickerDelegate(QAbstractProxyModel* categoryModel, QObject* parent = nullptr);

        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
        void setEditorData(QWidget *editor, const QModelIndex &index) const override;
        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    private:
        QAbstractProxyModel* m_categoryModel;
        QComboBox* m_comboBox;
    };
}
