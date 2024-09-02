#include "pch.h"
#include "ButtonPage.xaml.h"
#if __has_include("ButtonPage.g.cpp")
#include "ButtonPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
    int32_t ButtonPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ButtonPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    
    void ButtonPage::BackButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {

    }


    void ButtonPage::ShowHideButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowHideButton();
        auto textBox = SourceCodeTextBox();
        auto stackPanel = ShowHideStackPanel_xaml();
        Controls::ScrollViewer scrollviewer;

        for (auto el : stackPanel.Children())
        {
            if (auto s = el.try_as<Controls::ScrollViewer>())
                scrollviewer = s;   // capture stackpanel's scrollviewer for actual height of the visible text box
        }

        if (textBox.Visibility() == Visibility::Collapsed)
        {
            // Hide C++ code if visible
           /* if (cppTextBox.Visibility() == Visibility::Visible)
            {
                cppTextBox.Visibility(Visibility::Collapsed);
                cppButton.Content(box_value(L"Show C++"));
            }*/

            // Show XAML source code
            hstring xamlSourceCode = LR"( <Button x:Name="BackButton"
                Click="BackButton_Click"
                Style="{StaticResource NavigationBackButtonNormalStyle}"
                Foreground="{StaticResource BackButtonDisabledForegroundThemeBrush}"
                HorizontalAlignment="Center"
                VerticalAlignment="Top"
                Margin="0, 250, 0, 50"
                IsEnabled="True"/>})";
            textBox.Text(xamlSourceCode);
            textBox.Visibility(Visibility::Visible);
            button.Content(box_value(L"Hide XAML"));
            auto myMargin = stackPanel.Margin();
            myMargin.Bottom = 0;                        // Get the margin value and update the buttom parameter
            stackPanel.Margin(myMargin);
        }
        else
        {
            textBox.Visibility(Visibility::Collapsed);
            button.Content(box_value(L"Show XAML"));
            auto myMargin = stackPanel.Margin();
            myMargin.Bottom = -1 * scrollviewer.ActualHeight();
            stackPanel.Margin(myMargin);
        }
    }



    void ButtonPage::ShowCppButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto button = ShowCppButton(); // Make sure the button is named correctly
        auto textBox = CppCodeTextBox();
        auto stackPanel = ShowHideStackPanel_cpp();
        Controls::ScrollViewer scrollviewer;

        for (auto el : stackPanel.Children())
        {
            if (auto s = el.try_as<Controls::ScrollViewer>())
                scrollviewer = s;   // capture stackpanel's scrollviewer for actual height of the visible text box
        }

        if (textBox.Visibility() == Visibility::Collapsed)
        {
            // Hide XAML code if visible
           /* if (xamlTextBox.Visibility() == Visibility::Visible)
            {
                xamlTextBox.Visibility(Visibility::Collapsed);
                xamlButton.Content(box_value(L"Show XAML"));
            }*/

            // Show C++ source code
            hstring cppSourceCode = LR"(void MainWindow::TitleBar_BackButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        if (ContentFrame().CanGoBack())
            ContentFrame().GoBack();
        if (!ContentFrame().CanGoBack()) {
            TitleBar_BackButton().Foreground(Media::SolidColorBrush(Microsoft::UI::Colors::Gray()));
            TitleBar_BackButton().IsEnabled(false);
        }
            
    }
    void MainWindow::NavView_ItemInvoked(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args)
    {
        auto myTag = args.InvokedItemContainer().Tag();

        if (auto hstr = myTag.try_as<hstring>()) {
            //OutputDebugString(L"is a hstring!");
            //The try_as<winrt::hstring>() method tries to cast the IInspectable object (in this case the tag) to a winrt::hstring. If successful, it returns a winrt::hstring object.

            //winrt::CppWinUIGallery::HomePage l;
            const hstring FILEPATH = myTag.as<hstring>();
            ContentFrame().Navigate(Windows::UI::Xaml::Interop::TypeName{FILEPATH});
            if (ContentFrame().CanGoBack())
            {
                TitleBar_BackButton().Foreground(Media::SolidColorBrush(Microsoft::UI::Colors::White()));
                TitleBar_BackButton().IsEnabled(true);
            }
        }
    })";
            textBox.Text(cppSourceCode);
            textBox.Visibility(Visibility::Visible);
            button.Content(box_value(L"Hide C++"));
            auto myMargin = stackPanel.Margin();
            myMargin.Bottom = 0;                        // Get the margin value and update the buttom parameter
            stackPanel.Margin(myMargin);
        }
        else
        {
            textBox.Visibility(Visibility::Collapsed);
            button.Content(box_value(L"Show C++"));
            auto myMargin = stackPanel.Margin();
            myMargin.Bottom = -1 * scrollviewer.ActualHeight();
            stackPanel.Margin(myMargin);
        }
    }

}



