#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif


#include "winrt\Windows.Foundation.Collections.h"

//#include <algorithm>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.



namespace winrt::CppWinUIGallery::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        ExtendsContentIntoTitleBar(true);
        AppWindow().TitleBar().PreferredHeightOption(Microsoft::UI::Windowing::TitleBarHeightOption::Standard);
         
        // Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().SetPreferredMinSize(Windows::Foundation::Size(500, 300));

    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

   

    void MainWindow::AppTitleBar_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {   

        if (ExtendsContentIntoTitleBar() == true) {
            // Set the initial interactive regions.
            SetRegionsForCustomTitleBar();
        }
    }

    void MainWindow::AppTitleBar_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e)
    {

        if (ExtendsContentIntoTitleBar() == true) {
            // Set the interactive regions for app size modification.
            SetRegionsForCustomTitleBar();
        }
        
    }

    void MainWindow::SetRegionsForCustomTitleBar()
    {
        double scaleAdjustment = AppTitleBar().XamlRoot().RasterizationScale();
        auto m_AppWindow = this->AppWindow();
        

        AppTitleBar().Margin(ThicknessHelper::FromLengths(0, 0, m_AppWindow.TitleBar().RightInset(), 0));
        AppTitleBar().Width(m_AppWindow.ClientSize().Width - m_AppWindow.TitleBar().RightInset());

       
    }

    void MainWindow::TitleBar_BackButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        if (ContentFrame().CanGoBack())
            ContentFrame().GoBack();
        if (!ContentFrame().CanGoBack()) {
            TitleBar_BackButton().Foreground(Media::SolidColorBrush(Microsoft::UI::Colors::Gray()));
            TitleBar_BackButton().IsEnabled(false);
        }
            
    }

    void MainWindow::ContentFrame_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        ContentFrame().Navigate(Windows::UI::Xaml::Interop::TypeName{NavHomePage().Tag().as<hstring>()});
        NavView().SelectedItem(NavHomePage());
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
    }

    void MainWindow::NavView_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        for (auto item : NavView().MenuItems())
        {
            if (auto navItem = item.try_as<Controls::NavigationViewItem>())
            {
                
                auto text = navItem.Content().as<hstring>();
                auto str = to_string(text);
                navViewElementsList.push_back(str);
            }
        }

        for (auto el : navViewElementsList)
            navViewVisibleElements.insert(el);
    }

    bool MainWindow::isSubstring(const std::string& mainString, const std::string& subString) {
        // using find method to check if subString is
        // a substring of mainString

        if (mainString.find(subString) != std::string::npos)
            return true;
        return false;
    }


	void MainWindow::NavViewSearchBox_TextChanged(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args)
	{
        // Since selecting an item will also change the text,
        // only listen to changes caused by user entering text.

        //Controls::ControlTemplate myTemplate;
        //myTemplate.TargetType(Windows::UI::Xaml::Interop::TypeName{ L"AutoSuggestBox" });

        
        
        if (args.Reason() == winrt::Microsoft::UI::Xaml::Controls::AutoSuggestionBoxTextChangeReason::UserInput) {
            std::vector<std::string> suitableItems;

            std::vector<std::string> splitText;
            auto senderText = to_string(sender.Text());

            // Convert sender text to lowercase
            std::transform(senderText.begin(), senderText.end(), senderText.begin(), ::tolower);

            std::string delimiter = " ";
            std::size_t pos = 0;
            while ((pos = senderText.find(delimiter)) != std::string::npos) {
                splitText.push_back(senderText.substr(0, pos)); // split text by " " character
                senderText.erase(0, pos + delimiter.length());
            }
            // Add the last word
            splitText.push_back(senderText);

            for (auto element : navViewElementsList) {
                bool found = false;
                
                std::string lowerElement;
                lowerElement.resize(element.size());
                std::transform(element.begin(), element.end(), lowerElement.begin(), ::tolower);

                for (auto myInput : splitText) {
                    // Convert user input to lowercase for non-case sensitive search
                    // std::transform(myInput.begin(), myInput.end(), myInput.begin(), ::tolower);

                    if (isSubstring(lowerElement, myInput)) {
                        found = true;
                        break;
                    }
                }

                if (found)
                    suitableItems.push_back(element);
            }

            navViewVisibleElements.clear();

            for (auto item : suitableItems) {
                navViewVisibleElements.insert(item);
            }

            for (auto item : NavView().MenuItems()) {
                // Try to cast the item to a NavigationViewItem                

                if (auto navItem = item.try_as<Controls::NavigationViewItem>())
                {
                    navItem.Visibility(Visibility::Visible);
                    auto text = to_string(navItem.Content().as<hstring>());
                    if (auto search = navViewVisibleElements.find(text); search != navViewVisibleElements.end()) {
                        // item is visible
                        navItem.Visibility(Visibility::Visible);
                    }
                    else
                        navItem.Visibility(Visibility::Collapsed);
                }
            }

            //if (suitableItems.size() == 0)
            //    suitableItems.push_back("No items found!");
            //std::vector<winrt::hstring>s;
            //auto col = winrt::single_threaded_observable_vector<winrt::hstring>(std::move(s));
            //
            //for (const auto& el : suitableItems) {
            //    col.Append(to_hstring(el));
            //}
            //sender.ItemsSource(col);
        }

	}

    

}









