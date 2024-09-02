#pragma once

#include <QString>

namespace LambdaSnail::Juno::application
{
    /**
     * Class that holds some central definitions to avoid hard coded strings throughout the code base.
     */
    class ApplicationContext
    {
    public:
        static QString const ApplicationName;
        static QString const ApplicationName_LowerCase;
        static QString const OrganizationName;

        static QString const DbLocationSettingsKey;
        static QString const DbFileName;
    };
}
