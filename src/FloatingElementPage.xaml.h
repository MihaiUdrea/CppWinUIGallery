#pragma once

#include "FloatingElementPage.g.h"
#include <winrt/Microsoft.UI.Xaml.Media.h> // For Storyboard
#include <winrt/Microsoft.UI.Xaml.Controls.h> // For Controls
#include <winrt/Microsoft.UI.Xaml.h> // For XAML types

namespace winrt::CppWinUIGallery::implementation
{
    struct FloatingElementPage : FloatingElementPageT<FloatingElementPage>
    {
        FloatingElementPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ScrollViewer_ViewChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs const& e);
        void CheckTargetElementVisibility();

    private:

        bool m_isInfoBarVisible{ false }; // Added member variable to track InfoBar visibility
    public:
        void DoubleAnimation_Completed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e);
    };
}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct FloatingElementPage : FloatingElementPageT<FloatingElementPage, implementation::FloatingElementPage>
    {
    };
}
