#include "expensechartswidget.h"
#include "ui_expensechartswidget.h"

#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QChart>
#include <QChartView>
#include <QLegendMarker>
#include <QValueAxis>
#include <QVBarModelMapper>

#include "aggregateexpensemodel.h"
#include "categories/categorymodel.h"
#include "expenses/expensemodel.h"

namespace LambdaSnail::Juno::charts
{
    LSExpenseChartsWidget::LSExpenseChartsWidget(QAbstractItemModel *expensesProxyModel, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::LSExpenseChartsWidget),
        m_expensesProxyModel(expensesProxyModel)
    {
        ui->setupUi(this);

        createChart();
    }

    void LSExpenseChartsWidget::createChart()
    {
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
        m_expenseChart->legend()->hide();
        m_expenseChart->setTitle("Expenses by Category");

        m_chartView = new QChartView(m_expenseChart, this);
        m_chartView->setRenderHint(QPainter::Antialiasing);


        QStringList categories;
        for(int i = 0; i < m_expensesProxyModel->rowCount(); ++i)
        {
            QVariant const category = m_expensesProxyModel->data(m_expensesProxyModel->index(i, static_cast<int32_t>(categories::LSCategoryModel::Columns::category)), static_cast<int32_t>(expenses::LSAggregateExpenseModel::Roles::CategoryRole));
            categories.append(category.toString());
        }

        auto axisX = new QBarCategoryAxis;
        axisX->append(categories);
        m_expenseChart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        auto axisY = new QValueAxis;
        m_expenseChart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);



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
