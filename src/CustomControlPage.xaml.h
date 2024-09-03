#pragma once

#include "CustomControlPage.g.h"

namespace winrt::CppWinUIGallery::implementation
{
struct CustomControlPage : CustomControlPageT<CustomControlPage>
{
    CustomControlPage()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    int32_t MyProperty();
    void MyProperty(int32_t value);

    void ShowHideButton_Click(winrt::Windows::Foundation::IInspectable const &sender,
                              winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
    void ShowCppButton_Click(winrt::Windows::Foundation::IInspectable const &sender,
                             winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
    void ShowIdlButton_Click(winrt::Windows::Foundation::IInspectable const &sender,
                             winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
    void ShowHeaderButton_Click(winrt::Windows::Foundation::IInspectable const &sender,
                                winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e);
};
} // namespace winrt::CppWinUIGallery::implementation

namespace winrt::CppWinUIGallery::factory_implementation
{
struct CustomControlPage : CustomControlPageT<CustomControlPage, implementation::CustomControlPage>
{
};
} // namespace winrt::CppWinUIGallery::factory_implementation
