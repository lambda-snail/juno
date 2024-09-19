#pragma once

#include <QComboBox>
#include <QPushButton>
#include <QToolBar>

#include "QtAwesome.h"

#include "categoryfiltermodel.h"

namespace LambdaSnail::Juno::expenses
{
    struct ToolbarItems
    {
        QPushButton *NewExpenseButton;
        QPushButton *DeleteExpenseButton;

        QComboBox *CategoryFilterBox;
        QPushButton *ClearFilterButton;
    };

    class LSExpenseToolBarFactory
    {
    public:
        LSExpenseToolBarFactory() = delete;

        template<typename TView>
        [[nodiscard]]
        static inline std::unique_ptr<ToolbarItems> setUpToolbar(QWidget *widgetParent,
                                                                 LSCategoryFilterModel *categoryFilterModel,
                                                                 QAbstractProxyModel *categoryModel,
                                                                 int32_t categoryFilterColumn,
                                                                 TView *view,
                                                                 QToolBar *toolBar,
                                                                 fa::QtAwesome *qtAwesome)
        {
            auto toolbarItems = std::make_unique<ToolbarItems>();

            // New Expense
            toolbarItems->NewExpenseButton = new QPushButton(widgetParent);
            toolbarItems->NewExpenseButton->setIcon(qtAwesome->icon(fa::fa_solid, fa::fa_square_plus));

            // Delete Expense
            toolbarItems->DeleteExpenseButton = new QPushButton(widgetParent);
            toolbarItems->DeleteExpenseButton->setIcon(qtAwesome->icon(fa::fa_solid, fa::fa_trash_can));
            toolbarItems->DeleteExpenseButton->setEnabled(false);

            // Category Filter
            toolbarItems->CategoryFilterBox = new QComboBox(widgetParent);
            toolbarItems->CategoryFilterBox->setModel(categoryModel);
            toolbarItems->CategoryFilterBox->setModelColumn(categoryFilterColumn);
            toolbarItems->CategoryFilterBox->setEditable(false);

            toolbarItems->ClearFilterButton = new QPushButton(widgetParent);
            toolbarItems->ClearFilterButton->setIcon(qtAwesome->icon(fa::fa_solid, fa::fa_filter_circle_xmark));

            // Build the toolbar
            toolBar->addWidget(toolbarItems->NewExpenseButton);
            toolBar->addWidget(toolbarItems->DeleteExpenseButton);
            toolBar->addSeparator();
            toolBar->addWidget(toolbarItems->CategoryFilterBox);
            toolBar->addWidget(toolbarItems->ClearFilterButton);

            QWidget::connect(toolbarItems->NewExpenseButton, &QPushButton::pressed, widgetParent,
                             [categoryFilterModel]()
                             {
                                 categoryFilterModel->insertRow(0);
                             });

            QWidget::connect(toolbarItems->DeleteExpenseButton, &QPushButton::pressed, widgetParent,
                             [view, categoryFilterModel]()
                             {
                                 QItemSelection const selection = view->selectionModel()->selection();
                                 for (auto const &range: selection)
                                 {
                                     categoryFilterModel->removeRows(range.top(), range.height());
                                     for (auto const &row: range.indexes())
                                     {
                                         constexpr bool hasHideRow = requires
                                         {
                                             view->hideRow(row.row());
                                         };

                                         // "temporary" hack to make it work for both QTableView and QListView
                                         //if constexpr ( view->hideRow(); )
                                         if constexpr (hasHideRow)
                                         {
                                             view->hideRow(row.row());
                                         } else
                                         {
                                             view->setRowHidden(row.row(), true);
                                         }
                                     }
                                 }

                                 categoryFilterModel->sourceModel()->submit();
                                 //m_statusBar->showMessage(tr("Expenses deleted!"), 4000);
                             });

            QWidget::connect(toolbarItems->CategoryFilterBox, &QComboBox::currentTextChanged, widgetParent,
                             [categoryFilterModel](QString const &text)
                             {
                                 categoryFilterModel->setFilterCategory(text);
                             });

            QWidget::connect(toolbarItems->ClearFilterButton, &QPushButton::pressed, widgetParent,
                             [categoryFilterModel]()
                             {
                                 categoryFilterModel->setInactive();
                             });

            QWidget::connect(view->selectionModel(), &QItemSelectionModel::selectionChanged, widgetParent,
                             [deleteExpenses = toolbarItems->DeleteExpenseButton, view]()
                             {
                                 deleteExpenses->setEnabled(view->selectionModel()->hasSelection());
                             });

            return toolbarItems;
        }
    };
}
