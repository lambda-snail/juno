#include "expensechartswidget.h"
#include "ui_expensechartswidget.h"

#include <QBarSeries>
#include <QChart>
#include <QChartView>
#include <QVBarModelMapper>

#include "expenses/expensemodel.h"

namespace LambdaSnail::Juno::charts
{
    LSExpenseChartsWidget::LSExpenseChartsWidget(QAbstractItemModel *expensesProxyModel, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::LSExpenseChartsWidget),
        m_expensesProxyModel(expensesProxyModel)
    {
        ui->setupUi(this);

        m_expenseChart = new QChart();
        m_expenseChart->setParent(ui->mainChartFrame);
        m_expenseChart->setAnimationOptions(QChart::AllAnimations);

        auto series = new QBarSeries(this);

        int first = 0;
        int count = 3;
        m_barModelMapper = new QVBarModelMapper(this);
        m_barModelMapper->setFirstBarSetColumn(1);
        m_barModelMapper->setLastBarSetColumn(1);
        m_barModelMapper->setFirstRow(first);
        m_barModelMapper->setRowCount(count);
        m_barModelMapper->setSeries(series);
        m_barModelMapper->setModel(m_expensesProxyModel);

        m_expenseChart->addSeries(series);

        m_chartView = new QChartView(m_expenseChart, this);
        m_chartView->setRenderHint(QPainter::Antialiasing);

        auto frameLayout = new QHBoxLayout(ui->mainChartFrame);
        frameLayout->addWidget(m_chartView);
        ui->mainChartFrame->setLayout(frameLayout);
    }

    LSExpenseChartsWidget::~LSExpenseChartsWidget()
    {
        delete ui;
        delete m_expenseChart;
    }
}
