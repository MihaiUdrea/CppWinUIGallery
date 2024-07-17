#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <cstring>

#include "winrt\Windows.Foundation.Collections.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::NavView_ItemInvoked(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args)
    {
        auto myTag = args.InvokedItemContainer().Tag();

        if (auto hstr = myTag.try_as<hstring>()) {
            //OutputDebugString(L"is a hstring!");
            //The try_as<winrt::hstring>() method tries to cast the IInspectable object (in this case the tag) to a winrt::hstring. If successful, it returns a winrt::hstring object.

            //winrt::CppWinUIGallery::HomePage l;
            if (hstr == L"Home")
                ContentFrame().Navigate(Windows::UI::Xaml::Interop::TypeName{ L"CppWinUIGallery.HomePage" });
//            ContentFrame().Navigate(winrt::xaml_typename<Navigation::HomePage>());

            if (hstr == L"Color")
                OutputDebugString(L"this is color!\n");

            if (hstr == L"Button")
                OutputDebugString(L"this is button!\n");
        }
    }

    void MainWindow::NavView_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        
    }

	void MainWindow::NavViewSearchBox_TextChanged(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args)
	{
        // Since selecting an item will also change the text,
        // only listen to changes caused by user entering text.
        
        if (args.Reason() == winrt::Microsoft::UI::Xaml::Controls::AutoSuggestionBoxTextChangeReason::UserInput) {
            std::vector<std::string> suitableItems;

            std::vector<std::string> splitText;
            auto senderText = to_string(sender.Text());
            //transform(senderText.begin(), senderText.end(), aux.begin(), ::tolower);

            std::string delimiter = " ";
            std::size_t pos = 0;
            while (pos = senderText.find(delimiter) != std::string::npos) {
                splitText.push_back(senderText.substr(0, pos)); // split text by " " character
                senderText.erase(0, pos + delimiter.length());
            }
            // Add the last word
            splitText.push_back(senderText);

            for (const auto& element : navViewElementsList) {
                bool found = false;

                for (const auto& myInput : splitText) {
                    if (element == myInput) {
                        found = true;
                        break;
                    }
                }

                if (found)
                    suitableItems.push_back(element);
            }

            if (suitableItems.size() == 0)
                suitableItems.push_back("No items found!");
            std::vector<winrt::hstring>s;
            auto col = winrt::single_threaded_observable_vector<winrt::hstring>(std::move(s));

            for (const auto& el : suitableItems) {
                col.Append(to_hstring(el));
            }
            sender.ItemsSource(col);
        }

	}

}



