#pragma once

#include <qchart.h>
#include <qchartview.h>
#include <qvbarmodelmapper.h>
#include <QWidget>

class QAbstractItemModel;

namespace LambdaSnail::Juno::charts
{
    QT_BEGIN_NAMESPACE

    namespace Ui
    {
        class LSExpenseChartsWidget;
    }

    QT_END_NAMESPACE

    class LSExpenseChartsWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit LSExpenseChartsWidget(QAbstractItemModel* expensesProxyModel, QWidget *parent = nullptr);

        ~LSExpenseChartsWidget() override;

    private:
        Ui::LSExpenseChartsWidget* ui;
        QAbstractItemModel* m_expensesProxyModel;
        QChart* m_expenseChart;
        QVBarModelMapper* m_barModelMapper;
        QChartView* m_chartView;
    };
}
