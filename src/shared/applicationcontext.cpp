#include "applicationcontext.h"

namespace LambdaSnail::Juno::application
{
    QString const ApplicationContext::ApplicationName = "Juno";
    QString const ApplicationContext::ApplicationName_LowerCase = ApplicationName.toLower();
    QString const ApplicationContext::OrganizationName = "LambdaSnail";

    QString const ApplicationContext::DbLocationSettingsKey = "/data/folder";
    QString const ApplicationContext::DbFileName = "juno.db";

    QString const ApplicationContext::LocaleDateFormatKey = "/locale/dateformat";
}
