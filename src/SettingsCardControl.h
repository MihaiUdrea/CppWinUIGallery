// BgLabelControl.h
#pragma once
#include "SettingsCardControl.g.h"

namespace winrt::CppWinUIGallery::implementation
{
    struct SettingsCardControl : SettingsCardControlT<SettingsCardControl>
    {
        SettingsCardControl() { DefaultStyleKey(winrt::box_value(L"CppWinUIGallery.SettingsCardControl")); }

        Microsoft::UI::Xaml::FrameworkElement Label() // Getter
        {
            return winrt::unbox_value<Microsoft::UI::Xaml::FrameworkElement>(GetValue(m_labelProperty));
        }

        void Label(Microsoft::UI::Xaml::FrameworkElement const& value) // Setter
        {
            SetValue(m_labelProperty, winrt::box_value(value));
        }

        static Microsoft::UI::Xaml::DependencyProperty LabelProperty() { return m_labelProperty; }

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