#include "LSCategoryPickerDelegate.h"

#include <qabstractproxymodel.h>
#include <QComboBox>

#include "categories/categorymodel.h"

namespace LambdaSnail::Juno::shared {
    LSDelegateBase::LSDelegateBase(QObject *parent) : QStyledItemDelegate(parent) { }

    void LSDelegateBase::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        int32_t const cellHeight = option.rect.height();
        int32_t const editorHeight = editor->sizeHint().height();
        int32_t const height = std::max(cellHeight, editorHeight);

        QSize size = option.rect.size();
        size.setHeight(height);

        editor->setGeometry(QRect(option.rect.topLeft() - QPoint(0, (height - cellHeight) / 2), size));
    }





    LSCategoryPickerDelegate::LSCategoryPickerDelegate(QAbstractProxyModel* categoryModel, QObject *parent) :
        LSDelegateBase(parent),
        m_categoryModel(categoryModel)
    {
        m_comboBox = new QComboBox();
        m_comboBox->setModel(m_categoryModel);
        m_comboBox->setModelColumn(static_cast<int>(categories::LSCategoryModel::Columns::category));
        m_comboBox->setEditable(false);
    }

    QWidget * LSCategoryPickerDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                                     const QModelIndex &index) const
    {
        return m_comboBox;
    }

    void LSCategoryPickerDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        //static_cast<QComboBox*>(editor)->setDate(index.data().value<QDate>());
        QComboBox* comboBox = qobject_cast<QComboBox*>(editor);// static_cast<QComboBox*>(editor);
        comboBox->setCurrentIndex(index.column());
    }

    void LSCategoryPickerDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        QComboBox const* comboBox = qobject_cast<QComboBox*>(editor);
        QModelIndex const selectedCategoryIndex = m_categoryModel->index(comboBox->currentIndex(), static_cast<int>(categories::LSCategoryModel::Columns::id));
        int32_t const categoryId = m_categoryModel->data(selectedCategoryIndex, Qt::DisplayRole).toInt();

        model->setData(index, categoryId);

        // int32_t row = m_categoryModel->mapToSource(index).row();
        // QModelIndex idColumn = m_categoryModel->index(row, static_cast<int>(categories::LSCategoryModel::Columns::id));
        // QModelIndex categoryColumn = m_categoryModel->index(row, static_cast<int>(categories::LSCategoryModel::Columns::category));

        // QModelIndex idColumn = m_categoryModel->index(index.row(), static_cast<int>(categories::LSCategoryModel::Columns::id));
        // QModelIndex categoryColumn = m_categoryModel->index(index.row(), static_cast<int>(categories::LSCategoryModel::Columns::category));
        //
        //
        // model->setData(selectedCategoryId, );
        //
        // model->setData(index, QVariant::fromValue(static_cast<QDateEdit*>(editor)->date().toString(format)));
    }
}
