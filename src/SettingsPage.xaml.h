#pragma once

#include "SettingsPage.g.h"

namespace winrt::CppWinUIGallery::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
        SettingsPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

       
    };
}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
