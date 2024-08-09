#pragma once

#include "LottieIcon.g.h"
#include "winrt/Microsoft.UI.Xaml.h"
namespace winrt::CppWinUIGallery::implementation
{
    struct LottieIcon : LottieIconT<LottieIcon>
    {
        LottieIcon()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ShowSourceCode_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    };

}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct LottieIcon : LottieIconT<LottieIcon, implementation::LottieIcon>
    {
    };
}
