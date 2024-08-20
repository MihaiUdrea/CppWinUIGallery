#include "pch.h"
#include "SettingsPage.xaml.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
    int32_t SettingsPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void SettingsPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void SettingsPage::AppThemeCard_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto Icon = AppThemeCard().GetTemplateChild(L"Icon").as<Controls::FontIcon>();
        auto Title = AppThemeCard().GetTemplateChild(L"Title").as<Controls::TextBlock>();
        auto Description = AppThemeCard().GetTemplateChild(L"Description").as<Controls::TextBlock>();

        Icon.Glyph(L"\uE790");
        Title.Text(L"App theme");
        Description.Text(L"Select which app theme to display");

        auto cardComboBox = AppThemeCard().GetTemplateChild(L"cardComboBox").as<Controls::ComboBox>();
        //cardComboBox.Items().Append(Controls::IComboBoxItem{Tag(L"myItem")});
    }
    
}



