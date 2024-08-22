// BgLabelControl.cpp
#include "pch.h"
#include "SettingsCardControl.h"
#include "SettingsCardControl.g.cpp"

namespace winrt::CppWinUIGallery::implementation
{
    Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::m_labelProperty =
        Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Label",
            winrt::xaml_typename<winrt::hstring>(),
            winrt::xaml_typename<CppWinUIGallery::SettingsCardControl>(),
            Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(Microsoft::UI::Xaml::FrameworkElement{nullptr}), Microsoft::UI::Xaml::PropertyChangedCallback{&SettingsCardControl::OnLabelChanged}}
    );

    Microsoft::UI::Xaml::FrameworkElement  SettingsCardControl::Label() // Getter
    {
        return winrt::unbox_value<Microsoft::UI::Xaml::FrameworkElement>(GetValue(m_labelProperty));
    }

    void SettingsCardControl::Label(Microsoft::UI::Xaml::FrameworkElement const& value) // Setter
    {
        SetValue(this->m_labelProperty, winrt::box_value(value));
    }

    Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::LabelProperty() { return m_labelProperty; }

    void SettingsCardControl::OnLabelChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& /* e */)
    {
        if (CppWinUIGallery::SettingsCardControl theControl{ d.try_as<CppWinUIGallery::SettingsCardControl>() })
        {
            // Call members of the projected type via theControl.

            CppWinUIGallery::implementation::SettingsCardControl* ptr{ winrt::get_self<CppWinUIGallery::implementation::SettingsCardControl>(theControl) };
            // Call members of the implementation type via ptr.
        }
    }


}