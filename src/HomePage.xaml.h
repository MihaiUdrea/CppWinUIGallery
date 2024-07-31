#pragma once

#include "HomePage.g.h"
#include "winrt/Microsoft.UI.Xaml.Controls.h"

namespace winrt::CppWinUIGallery::implementation
{
    struct HomePage : HomePageT<HomePage>
    {
        HomePage() = default;
        virtual ~HomePage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };

}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}
