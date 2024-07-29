#pragma once

#include "FloatingElementPage.g.h"

namespace winrt::CppWinUIGallery::implementation
{
    struct FloatingElementPage : FloatingElementPageT<FloatingElementPage>
    {
        FloatingElementPage()
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
    struct FloatingElementPage : FloatingElementPageT<FloatingElementPage, implementation::FloatingElementPage>
    {
    };
}
