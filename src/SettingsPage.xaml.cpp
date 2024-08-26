#include "pch.h"
#include "SettingsPage.xaml.h"
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

    void SettingsPage::OnNavigatedTo(winrt::Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {

        this->mroot = e.Parameter();
        
    }


    void SettingsPage::AppThemeComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
    {   
        auto selectedItem = sender.as<Controls::ComboBox>().SelectedItem().as<Controls::ComboBoxItem>();
        auto tag = selectedItem.Tag().as<hstring>();
            if (tag != L"Default")
            {
                if (tag == L"Dark") // Dark mode
                {
                    
                    
                    if (auto grid = mroot.try_as<Controls::Grid>())
                    {
                        grid.RequestedTheme(ElementTheme::Dark);
                    }

                    //Application::Current().RequestedTheme(ApplicationTheme::Dark);
                    /*MainWindow().AppWindow().TitleBar().ButtonForegroundColor(Microsoft::UI::Colors::White());
                    MainWindow().AppWindow().TitleBar().ButtonHoverForegroundColor(Microsoft::UI::Colors::Blue());
                    MainWindow().AppWindow().TitleBar().ButtonHoverBackgroundColor(Windows::UI::Color{ 100, 90, 90 , 90 });
                    OutputDebugString(L"DARK MODE");*/

                }
                else if (tag == L"Light")  // Light mode
                {
                    if (auto grid = mroot.try_as<Controls::Grid>())
                    {
                        grid.RequestedTheme(ElementTheme::Light);
                        auto titleBar = grid.FindName(L"AppTitleBar").as<Controls::Grid>();
                        auto textBlock = titleBar.FindName(L"TitleBarTextBlock").as<Controls::TextBlock>();
                        //textBlock.Foreground(Media::SolidColorBrush(Windows::UI::Colors::Black()));
                    }
                }
            }
            else
            {
                if (auto grid = mroot.try_as<Controls::Grid>())
                {
                    grid.RequestedTheme(ElementTheme::Default);
                }
            }
    }

    
}




