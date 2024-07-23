#include "pch.h"
#include "AutoSuggestPage.xaml.h"
#if __has_include("AutoSuggestPage.g.cpp")
#include "AutoSuggestPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
    int32_t AutoSuggestPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AutoSuggestPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }


    bool AutoSuggestPage::isSubstring(const std::string& mainString, const std::string& subString)
    {
        // using find method to check if subString is
        // a substring of mainString

        if (mainString.find(subString) != std::string::npos)
            return true;
        return false;
    }


    void AutoSuggestPage::SearchBox_TextChanged(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args)
    {
        // Since selecting an item will also change the text,
        // only listen to changes caused by user entering text.

        //Controls::ControlTemplate myTemplate;
        //myTemplate.TargetType(Windows::UI::Xaml::Interop::TypeName{ L"AutoSuggestBox" });




        if (args.Reason() == winrt::Microsoft::UI::Xaml::Controls::AutoSuggestionBoxTextChangeReason::UserInput) {
            std::vector<std::string> suitableItems;

            std::vector<std::string> splitText;
            auto senderText = to_string(sender.Text());

            auto mySearchBox = this->FindName(L"SearchBox").as<Controls::AutoSuggestBox>();
            auto overlayIcon = mySearchBox.GetTemplateChild(L"searchIconOverlay").as<Controls::TextBlock>();

            if (senderText == "") {
                overlayIcon.Visibility(Visibility::Visible);
                isTextBoxEmpty = true;
            }
            else 
            {
                overlayIcon.Visibility(Visibility::Collapsed);
                isTextBoxEmpty = false;
            }
                


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

            for (auto element : ElementsList) {
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



            if (suitableItems.size() == 0)
                suitableItems.push_back("No items found!");
            std::vector<winrt::hstring>s;
            auto col = winrt::single_threaded_observable_vector<winrt::hstring>(std::move(s));

            for (const auto& el : suitableItems) {
                col.Append(to_hstring(el));
            }
            sender.ItemsSource(col);

            if (col.Size() == ElementsList.size())
                isTextBoxEmpty = false;
        }
    }


    void AutoSuggestPage::SearchBox_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& e)
    {
        auto mySearchBox = this->FindName(L"SearchBox").as<Controls::AutoSuggestBox>();
        auto overlayIcon = mySearchBox.GetTemplateChild(L"searchIconOverlay").as<Controls::TextBlock>();

        overlayIcon.Visibility(Visibility::Collapsed);  // Responsive


    }
 

    void AutoSuggestPage::SearchBox_GotFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto mySearchBox = sender.as<Controls::AutoSuggestBox>();
        auto overlayIcon = mySearchBox.GetTemplateChild(L"searchIconOverlay").as<Controls::TextBlock>();

        if (!isTextBoxEmpty)      //             ICON OVERLAY BUG: After being in out of focus with an element selected inside the search box, when being selected back on focus the Text atribute behaves like if it contains an empty string
            overlayIcon.Visibility(Visibility::Collapsed);
    }


    void AutoSuggestPage::SearchBox_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto mySearchBox = this->FindName(L"SearchBox").as<Controls::AutoSuggestBox>();
        auto overlayIcon = mySearchBox.GetTemplateChild(L"searchIconOverlay").as<Controls::TextBlock>();


        overlayIcon.Visibility(Visibility::Visible);
    }
}









