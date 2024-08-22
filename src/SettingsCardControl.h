// BgLabelControl.h
#pragma once
#include "SettingsCardControl.g.h"

namespace winrt::CppWinUIGallery::implementation
{
    struct SettingsCardControl : SettingsCardControlT<SettingsCardControl>
    {
        SettingsCardControl() { DefaultStyleKey(winrt::box_value(L"CppWinUIGallery.SettingsCardControl")); }

        Microsoft::UI::Xaml::FrameworkElement Label(); // Getter
        void Label(Microsoft::UI::Xaml::FrameworkElement const& value); // Setter
        

        static Microsoft::UI::Xaml::DependencyProperty LabelProperty();

        static void OnLabelChanged(Microsoft::UI::Xaml::DependencyObject const&, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&);

    private:
        static Microsoft::UI::Xaml::DependencyProperty m_labelProperty;
    };
}
namespace winrt::CppWinUIGallery::factory_implementation
{
    struct SettingsCardControl : SettingsCardControlT<SettingsCardControl, implementation::SettingsCardControl>
    {
    };
}