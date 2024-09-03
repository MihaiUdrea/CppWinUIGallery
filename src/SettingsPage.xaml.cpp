#include "SettingsPage.xaml.h"
#include "pch.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

#include "App.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
inline SettingsPage::SettingsPage()
{
    // Xaml objects should not call InitializeComponent during construction.
    // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
}
int32_t SettingsPage::MyProperty()
{
    throw hresult_not_implemented();
}

void SettingsPage::MyProperty(int32_t /* value */)
{
    throw hresult_not_implemented();
}

void SettingsPage::OnNavigatedTo(winrt::Microsoft::UI::Xaml::Navigation::NavigationEventArgs const &e)
{
    auto v = e.Parameter();
    auto pp = e.Parameter().as<winrt::Windows::Foundation::Collections::IVector<IInspectable>>();
    auto grid = pp.GetAt(0).as<Controls::Grid>();
    auto appwnd = pp.GetAt(1).as<Microsoft::UI::Windowing::AppWindowTitleBar>();

    for (auto el : pp)
    {
        auto p = winrt::get_class_name(el);
        p;
    }
    //.as<single_threaded_observable_vector<IInspectable>>();
    auto p = winrt::get_class_name(v);
    p;

    mRoot = grid;
    mTitleBar = appwnd;
}

void SettingsPage::AppThemeComboBox_Loaded(winrt::Windows::Foundation::IInspectable const &sender,
                                           winrt::Microsoft::UI::Xaml::RoutedEventArgs const &e)
{
    if (auto grid = mRoot.try_as<Controls::Grid>())
    {
        auto currentTheme = grid.RequestedTheme();
        if (currentTheme == ElementTheme::Default)
            AppThemeComboBox().SelectedIndex(0);
        else if (currentTheme == ElementTheme::Dark)
            AppThemeComboBox().SelectedIndex(1);
        else if (currentTheme == ElementTheme::Light)
            AppThemeComboBox().SelectedIndex(2);
    }
}

void SettingsPage::AppThemeComboBox_SelectionChanged(
    winrt::Windows::Foundation::IInspectable const &sender,
    winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const &e)
{
    auto selectedItem = sender.as<Controls::ComboBox>().SelectedItem().as<Controls::ComboBoxItem>();
    auto tag = selectedItem.Tag().as<hstring>();
    if (tag != L"Default")
    {
        if (tag == L"Dark") // Dark mode
        {

            if (auto grid = mRoot.try_as<Controls::Grid>())
            {
                grid.RequestedTheme(ElementTheme::Dark);

                mTitleBar.ButtonForegroundColor(Microsoft::UI::Colors::White());
                mTitleBar.ButtonHoverForegroundColor(Microsoft::UI::Colors::White());
                mTitleBar.ButtonHoverBackgroundColor(Windows::UI::Color{100, 90, 90, 90});
            }
        }
        else if (tag == L"Light") // Light mode
        {
            if (auto grid = mRoot.try_as<Controls::Grid>())
            {
                grid.RequestedTheme(ElementTheme::Light);

                mTitleBar.ButtonForegroundColor(Microsoft::UI::Colors::Black());
                mTitleBar.ButtonHoverForegroundColor(Microsoft::UI::Colors::Black());
                mTitleBar.ButtonHoverBackgroundColor(Windows::UI::Color{100, 191, 191, 191});
            }
        }
    }
    else
    {
        if (auto grid = mRoot.try_as<Controls::Grid>())
        {
            auto currentTheme = winrt::Microsoft::UI::Xaml::Application::Current().RequestedTheme();
            if (currentTheme == ApplicationTheme::Dark)
            {
                grid.RequestedTheme(ElementTheme::Dark);

                mTitleBar.ButtonForegroundColor(Microsoft::UI::Colors::White());
                mTitleBar.ButtonHoverForegroundColor(Microsoft::UI::Colors::White());
                mTitleBar.ButtonHoverBackgroundColor(Windows::UI::Color{100, 90, 90, 90});
            }
            else
            {
                grid.RequestedTheme(ElementTheme::Light);

                mTitleBar.ButtonForegroundColor(Microsoft::UI::Colors::Black());
                mTitleBar.ButtonHoverForegroundColor(Microsoft::UI::Colors::Black());
                mTitleBar.ButtonHoverBackgroundColor(Windows::UI::Color{100, 191, 191, 191});
            }
        }
    }
}

} // namespace winrt::CppWinUIGallery::implementation
