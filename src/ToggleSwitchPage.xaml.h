#pragma once

#include "ToggleSwitchPage.g.h"

namespace winrt::CppWinUIGallery::implementation
{
struct ToggleSwitchPage : ToggleSwitchPageT<ToggleSwitchPage>
{
    ToggleSwitchPage()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    int32_t MyProperty();
    void MyProperty(int32_t value);

    void SubscriptionToggleSwitch_Toggled(winrt::Windows::Foundation::IInspectable const &sender,
                                          winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
    void ShowSourceCode_Click(winrt::Windows::Foundation::IInspectable const &sender,
                              winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
    void ShowCppCode_Click(winrt::Windows::Foundation::IInspectable const &sender,
                           winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
    void SourceCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                  winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
    void CppCodeTextBox_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                               winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
};
} // namespace winrt::CppWinUIGallery::implementation

namespace winrt::CppWinUIGallery::factory_implementation
{
struct ToggleSwitchPage : ToggleSwitchPageT<ToggleSwitchPage, implementation::ToggleSwitchPage>
{
};
} // namespace winrt::CppWinUIGallery::factory_implementation
