#pragma once

#include "AutoSuggestPage.g.h"

namespace winrt::CppWinUIGallery::implementation
{
    struct AutoSuggestPage : AutoSuggestPageT<AutoSuggestPage>
    {
    private:
        std::vector<std::string> ElementsList = {
        "Apple", "Banana", "Orange", "Grape", "Mango",
        "Pineapple", "Strawberry", "Blueberry", "Raspberry", "Blackberry",
        "Cherry", "Watermelon", "Cantaloupe", "Honeydew", "Kiwi",
        "Papaya", "Pomegranate", "Peach", "Plum", "Apricot",
        "Nectarine", "Fig", "Date", "Grapefruit", "Lemon",
        "Lime", "Avocado", "Coconut", "Lychee", "Guava",
        "Passion Fruit", "Dragon Fruit", "Jackfruit", "Durian", "Persimmon",
        "Cranberry", "Mulberry", "Gooseberry", "Starfruit", "Tamarind",
        "Kumquat", "Clementine", "Tangerine", "Blood Orange", "Quince",
        "Medlar", "Soursop", "Mangosteen", "Rambutan", "Longan"
        };


    public:
        AutoSuggestPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        bool isSubstring(const std::string& mainString, const std::string& subString);
        void SearchBox_TextChanged(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
        void SearchBox_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::KeyRoutedEventArgs const& e);
        void SearchBox_GotFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SearchBox_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::CppWinUIGallery::factory_implementation
{
    struct AutoSuggestPage : AutoSuggestPageT<AutoSuggestPage, implementation::AutoSuggestPage>
    {
    };
}
