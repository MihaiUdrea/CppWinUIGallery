#include "pch.h"
#include "PhotoGallery.xaml.h"
#if __has_include("PhotoGallery.g.cpp")
#include "PhotoGallery.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media::Imaging;


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CppWinUIGallery::implementation
{
	int32_t PhotoGallery::MyProperty()
	{
		throw hresult_not_implemented();
	}

	void PhotoGallery::MyProperty(int32_t /* value */)
	{
		throw hresult_not_implemented();
	}
	void PhotoGallery::ThemeButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		// Toggle the visibility of the ListView based on the current button content
		auto button = sender.as<Button>();

		if (button != nullptr)
		{

			auto listView = itemListView();

			if (listView != nullptr)
			{
				if (button.Content().as<winrt::hstring>() == L"Hide details")
				{
					// Show the ListView
					ThemeExampleGrid().RequestedTheme(ElementTheme::Dark);
					listView.Visibility(Visibility::Collapsed);
					button.Content(box_value(L"Show details")); // Change button text to "Hide"

				}
				else if (button.Content().as<winrt::hstring>() == L"Show details")
				{
					// Hide the ListView
					ThemeExampleGrid().RequestedTheme(ElementTheme::Light);
					listView.Visibility(Visibility::Visible);
					button.Content(box_value(L"Hide details")); // Change button text to "Show"
				}
			}
		}
	}


	/* void PhotoGallery::myButton_Click(IInspectable const&, RoutedEventArgs const&)
	{
	myButton().Content(box_value(L"Clicked"));
	}*/
}