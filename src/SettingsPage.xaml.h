#pragma once

#include "SettingsPage.g.h"
#include "MainWindow.g.h"


namespace winrt::CppWinUIGallery::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
        SettingsPage();
        

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void OnNavigatedTo(winrt::Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e);
       
        void AppThemeComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);

    private:
        winrt::Windows::Foundation::IInspectable mRoot;
        winrt::Microsoft::UI::Windowing::AppWindowTitleBar mTitleBar{nullptr};
    };
}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
