#pragma once
#include "SettingsCardControl.g.h"

namespace winrt::CppWinUIGallery::implementation
{
    struct SettingsCardControl : SettingsCardControlT<SettingsCardControl>
    {
        SettingsCardControl() { DefaultStyleKey(winrt::box_value(L"CppWinUIGallery.SettingsCardControl")); }

        // RightSideContent

        Microsoft::UI::Xaml::FrameworkElement RightSideContent(); // Getter
        void RightSideContent(Microsoft::UI::Xaml::FrameworkElement const& value); // Setter
        
        static Microsoft::UI::Xaml::DependencyProperty RightSideContentProperty();

        static void OnRightSideContentChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&);

        
        // Title

        hstring Title(); // Getter
        void Title(hstring const& value); // Setter

        static Microsoft::UI::Xaml::DependencyProperty TitleProperty();
        static void OnTitleChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&);

        // Subtitle

        hstring Subtitle(); // Getter
        void Subtitle(hstring const& value); // Setter

        static Microsoft::UI::Xaml::DependencyProperty SubtitleProperty();
        static void OnSubtitleChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&);

        // Icon

        hstring Icon(); // Getter
        void Icon(hstring const& value); // Setter

        static Microsoft::UI::Xaml::DependencyProperty IconProperty();
        static void OnIconChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const&);

    private:
        static Microsoft::UI::Xaml::DependencyProperty m_RightSideContentProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_TitleProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_SubTitleProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_IconProperty;

    };
}
namespace winrt::CppWinUIGallery::factory_implementation
{
    struct SettingsCardControl : SettingsCardControlT<SettingsCardControl, implementation::SettingsCardControl>
    {
    };
}