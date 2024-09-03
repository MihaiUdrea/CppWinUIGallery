#include "pch.h"

#include "SettingsCardControl.h"

#include "SettingsCardControl.g.cpp"

namespace winrt::CppWinUIGallery::implementation
{

// RightSideContent

Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::m_RightSideContentProperty =
    Microsoft::UI::Xaml::DependencyProperty::Register(
        L"RightSideContent", winrt::xaml_typename<Microsoft::UI::Xaml::FrameworkElement>(),
        winrt::xaml_typename<CppWinUIGallery::SettingsCardControl>(),
        Microsoft::UI::Xaml::PropertyMetadata{
            winrt::box_value(Microsoft::UI::Xaml::FrameworkElement{nullptr}),
            Microsoft::UI::Xaml::PropertyChangedCallback{&SettingsCardControl::OnRightSideContentChanged}});

Microsoft::UI::Xaml::FrameworkElement SettingsCardControl::RightSideContent() // Getter
{
    return winrt::unbox_value<Microsoft::UI::Xaml::FrameworkElement>(GetValue(m_RightSideContentProperty));
}

void SettingsCardControl::RightSideContent(Microsoft::UI::Xaml::FrameworkElement const &value) // Setter
{
    SetValue(this->m_RightSideContentProperty, winrt::box_value(value));
}

Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::RightSideContentProperty()
{
    return m_RightSideContentProperty;
}

void SettingsCardControl::OnRightSideContentChanged(
    Microsoft::UI::Xaml::DependencyObject const &d,
    Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const & /* e */)
{
    if (CppWinUIGallery::SettingsCardControl theControl{d.try_as<CppWinUIGallery::SettingsCardControl>()})
    {
        // Call members of the projected type via theControl.

        CppWinUIGallery::implementation::SettingsCardControl *ptr{
            winrt::get_self<CppWinUIGallery::implementation::SettingsCardControl>(theControl)};
        // Call members of the implementation type via ptr.
    }
}

// Title

Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::m_TitleProperty =
    Microsoft::UI::Xaml::DependencyProperty::Register(
        L"Title", winrt::xaml_typename<hstring>(), winrt::xaml_typename<CppWinUIGallery::SettingsCardControl>(),
        Microsoft::UI::Xaml::PropertyMetadata{
            winrt::box_value(L"Title"),
            Microsoft::UI::Xaml::PropertyChangedCallback{&SettingsCardControl::OnRightSideContentChanged}});

hstring SettingsCardControl::Title() // Getter
{
    return winrt::unbox_value<hstring>(GetValue(this->m_TitleProperty));
}

void SettingsCardControl::Title(hstring const &value) // Setter
{
    SetValue(this->m_TitleProperty, winrt::box_value(value));
}

Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::TitleProperty()
{
    return m_TitleProperty;
}

void SettingsCardControl::OnTitleChanged(Microsoft::UI::Xaml::DependencyObject const &d,
                                         Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const &)
{
    if (CppWinUIGallery::SettingsCardControl theControl{d.try_as<CppWinUIGallery::SettingsCardControl>()})
    {
        // Call members of the projected type via theControl.

        CppWinUIGallery::implementation::SettingsCardControl *ptr{
            winrt::get_self<CppWinUIGallery::implementation::SettingsCardControl>(theControl)};
        // Call members of the implementation type via ptr.
    }
}

// Subtitle

Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::m_SubTitleProperty =
    Microsoft::UI::Xaml::DependencyProperty::Register(
        L"Subtitle", winrt::xaml_typename<hstring>(), winrt::xaml_typename<CppWinUIGallery::SettingsCardControl>(),
        Microsoft::UI::Xaml::PropertyMetadata{
            winrt::box_value(L"Subtitle"),
            Microsoft::UI::Xaml::PropertyChangedCallback{&SettingsCardControl::OnRightSideContentChanged}});

hstring SettingsCardControl::Subtitle() // Getter
{
    return winrt::unbox_value<hstring>(GetValue(this->m_SubTitleProperty));
}

void SettingsCardControl::Subtitle(hstring const &value) // Setter
{
    SetValue(this->m_SubTitleProperty, winrt::box_value(value));
}

Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::SubtitleProperty()
{
    return m_SubTitleProperty;
}

void SettingsCardControl::OnSubtitleChanged(Microsoft::UI::Xaml::DependencyObject const &d,
                                            Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const &)
{
    if (CppWinUIGallery::SettingsCardControl theControl{d.try_as<CppWinUIGallery::SettingsCardControl>()})
    {
        // Call members of the projected type via theControl.

        CppWinUIGallery::implementation::SettingsCardControl *ptr{
            winrt::get_self<CppWinUIGallery::implementation::SettingsCardControl>(theControl)};
        // Call members of the implementation type via ptr.
    }
}

// Icon

Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::m_IconProperty =
    Microsoft::UI::Xaml::DependencyProperty::Register(
        L"Icon", winrt::xaml_typename<hstring>(), winrt::xaml_typename<CppWinUIGallery::SettingsCardControl>(),
        Microsoft::UI::Xaml::PropertyMetadata{
            winrt::box_value(L"\uE700"),
            Microsoft::UI::Xaml::PropertyChangedCallback{&SettingsCardControl::OnRightSideContentChanged}});

hstring SettingsCardControl::Icon() // Getter
{
    return winrt::unbox_value<hstring>(GetValue(this->m_IconProperty));
}

void SettingsCardControl::Icon(hstring const &value) // Setter
{
    SetValue(this->m_IconProperty, winrt::box_value(value));
}

Microsoft::UI::Xaml::DependencyProperty SettingsCardControl::IconProperty()
{
    return m_IconProperty;
}

void SettingsCardControl::OnIconChanged(Microsoft::UI::Xaml::DependencyObject const &d,
                                        Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const &)
{
    if (CppWinUIGallery::SettingsCardControl theControl{d.try_as<CppWinUIGallery::SettingsCardControl>()})
    {
        // Call members of the projected type via theControl.

        CppWinUIGallery::implementation::SettingsCardControl *ptr{
            winrt::get_self<CppWinUIGallery::implementation::SettingsCardControl>(theControl)};
        // Call members of the implementation type via ptr.
    }
}
} // namespace winrt::CppWinUIGallery::implementation
