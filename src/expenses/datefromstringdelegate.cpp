#include "datefromstringdelegate.h"

#include <QDateEdit>

namespace LS = LambdaSnail::Juno::expenses;

static constexpr auto const* format = "yyyy-MM-dd"; // TODO: Store format in settings

QWidget *LS::LSDateFromStringDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                                  const QModelIndex &index) const
{
    QDateEdit* editor = new QDateEdit(parent);
    editor->setCalendarPopup(true);
    editor->setDisplayFormat(format);
    return editor;
}

void LS::LSDateFromStringDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    static_cast<QDateEdit*>(editor)->setDate(index.data().value<QDate>());
}

void LS::LSDateFromStringDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                              const QModelIndex &index) const
{
    model->setData(index, QVariant::fromValue(static_cast<QDateEdit*>(editor)->date().toString(format)));
}

void LS::LSDateFromStringDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                                      const QModelIndex &index) const
{
    int32_t const cellHeight = option.rect.height();
    int32_t const editorHeight = editor->sizeHint().height();
    int32_t const height = std::max(cellHeight, editorHeight);

    QSize size = option.rect.size();
    size.setHeight(height);

    editor->setGeometry(QRect(option.rect.topLeft() - QPoint(0, (height - cellHeight) / 2), size));
}
