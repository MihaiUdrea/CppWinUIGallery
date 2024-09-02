#pragma once

#include "ButtonPage.g.h"

namespace winrt::CppWinUIGallery::implementation
{
    struct ButtonPage : ButtonPageT<ButtonPage>
    {
        ButtonPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        
        void SourceCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CppCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct ButtonPage : ButtonPageT<ButtonPage, implementation::ButtonPage>
    {
    };
}
